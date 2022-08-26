#ifndef DATAVIEW2DCOMPOUND_TXX
#define DATAVIEW2DCOMPOUND_TXX

#include "dataviewdefaultcompound.h"

namespace Plotypus
{
    template<class T>
    void DataViewDefaultCompound<T>::clearNonFunctionMembers()
    {
        data = std::span<T>();
        selectors = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    }

    template<class T>
    void DataViewDefaultCompound<T>::fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const
    {
        // *INDENT-OFF*
        const T& datapoint = data[recordID];
        for (auto i : columnAssignments) {
            if (i == COLUMN_UNUSED) {continue;}         // ignore unused columns
            --i;                                        // zero based indices

            const auto& selector = selectors[i];        // fetch correct selector
            i -= missingXColumn;                        // correct for maybe missing X column

            buffer[i] = selector(datapoint);
        }
        // *INDENT-ON*
    }

    // ====================================================================== //

    template<class T>
    DataViewDefaultCompound<T>::DataViewDefaultCompound(const PlotStyle style, const std::string& label) :
        DataViewDefault(style, label)
    {}

    template<class T>
    DataViewDefaultCompound<T>::DataViewDefaultCompound(const std::string& style, const std::string& label) :
        DataViewDefault(style, label)
    {}

    // ====================================================================== //

    template<class T>
    size_t DataViewDefaultCompound<T>::getArity() const
    {
        return data.size();
    }

    template<class T>
    const std::span<T>& DataViewDefaultCompound<T>::getData() const
    {
        return data;
    }

    template<class T>
    void DataViewDefaultCompound<T>::setData(const std::span<T>& newDataSource)
    {
        data = newDataSource;
    }

    template<class T>
    void DataViewDefaultCompound<T>::setData(const T* newDataSource, size_t N)
    {
        data = std::span<T>(newDataSource, newDataSource + N);
    }

    template<class T>
    const std::array<DataSelector_t<T>, 6>& DataViewDefaultCompound<T>::getSelectors() const
    {
        return selectors;
    }

    template<class T>
    void DataViewDefaultCompound<T>::setSelectors(const std::array<DataSelector_t<T>, 6>& newSelectors)
    {
        selectors = newSelectors;
        for (size_t i = 0u; const auto& selector : selectors)
        {
            // *INDENT-OFF*
            if (selector) {columnAssignments[i] = ++i;}         // columnAssignments[i] = i + 1 for i in range(size)
            // *INDENT-ON*
        }
    }

    template<class T>
    void DataViewDefaultCompound<T>::setSelector(const ColumnType column, const DataSelector_t<T>& selector)
    {
        auto columnID = getColumnID(column);

        if (columnID == COLUMN_UNSUPPORTED)
        {
            std::string errMsg = "Column type ";
            errMsg += "\"" + getColumnIDName(column) + "\"";
            errMsg += " not supported for plot type ";
            errMsg += "\"" + getPlotStyleName(styleID) + "\"";

            throw UnsupportedOperationError( errMsg );
        }

        // column IDs are 1-based...
        --columnID;
        selectors        [columnID] = selector;
        columnAssignments[columnID] = columnID + 1;
        columnHeadlines  [columnID] = getColumnIDName(column);
    }

    template<class T>
    bool DataViewDefaultCompound<T>::isDummy() const
    {
        bool result = func.empty();
        result &= data.empty();
        for (const auto& selector : selectors)
        {
            result &= static_cast<bool>(selector);
        }
        return result;
    }

    template<class T>
    bool DataViewDefaultCompound<T>::isComplete() const
    {
        // *INDENT-OFF*
        if (isDummy())      {return true;}
        if (data.empty())   {return false;}

        const auto isNullSelector = [] (const DataSelector_t<T>& selector) {return selector == nullptr;};
        // *INDENT-ON*

        switch (styleID)
        {
            case PlotStyle::Dots:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle::Points:
                return checkColumnListOccupationIsFrom(selectors, {1, 2, 3, 4, 5}, isNullSelector);
            case PlotStyle::XErrorBars:
                return checkColumnListOccupationIsFrom(selectors, {3, 4}, isNullSelector);
            case PlotStyle::YErrorBars:
                return checkColumnListOccupationIsFrom(selectors, {3, 4}, isNullSelector);
            case PlotStyle::XYErrorBars:
                return checkColumnListOccupationIsFrom(selectors, {4, 6}, isNullSelector);
            case PlotStyle::Lines:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle::LinesPoints:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle::FilledCurves:
                return checkColumnListOccupationIsFrom(selectors, {1, 2, 3}, isNullSelector);
            case PlotStyle::XErrorLines:
                return checkColumnListOccupationIsFrom(selectors, {3, 4}, isNullSelector);
            case PlotStyle::YErrorLines:
                return checkColumnListOccupationIsFrom(selectors, {3, 4}, isNullSelector);
            case PlotStyle::XYErrorLines:
                return checkColumnListOccupationIsFrom(selectors, {4, 6}, isNullSelector);
            case PlotStyle::Steps:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle::FSteps:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle::FillSteps:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle::Impulses:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle::Boxes:
                return checkColumnListOccupationIsFrom(selectors, {1, 2, 3}, isNullSelector);
            case PlotStyle::HBoxes:
                return checkColumnListOccupationIsFrom(selectors, {1, 2, 3}, isNullSelector);
            case PlotStyle::BoxErrorBars:
                return checkColumnListOccupationIsFrom(selectors, {3, 4, 5}, isNullSelector);
            case PlotStyle::BoxxyError:
                return checkColumnListOccupationIsFrom(selectors, {4, 6}, isNullSelector);
            case PlotStyle::Arrows:
                return checkColumnListOccupationIsFrom(selectors, {4}, isNullSelector);
            case PlotStyle::Vectors:
                return checkColumnListOccupationIsFrom(selectors, {4}, isNullSelector);
            case PlotStyle::Image:
                return checkColumnListOccupationIsFrom(selectors, {3}, isNullSelector);
            case PlotStyle::Custom:
                return checkColumnListOccupationIsFrom(selectors, {1, 2, 3, 4, 5, 6}, isNullSelector);
        }

        return false;
    }
}

#endif // DATAVIEW2DCOMPOUND_TXX
