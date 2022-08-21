#ifndef DATAVIEW2DCOMPOUND_TXX
#define DATAVIEW2DCOMPOUND_TXX

#include "dataview2dcompound.h"

namespace Plotypus
{
    template<class T>
    void DataView2DCompound<T>::clearNonFunctionMembers()
    {
        data = std::span<T>();
        selectors = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    }

    template<class T>
    void DataView2DCompound<T>::fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const
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
    DataView2DCompound<T>::DataView2DCompound(const PlotStyle2D style, const std::string& label) :
        DataViewDefault(style, label)
    {}

    template<class T>
    DataView2DCompound<T>::DataView2DCompound(const std::string& style, const std::string& label) :
        DataViewDefault(style, label)
    {}

    // ====================================================================== //

    template<class T>
    size_t DataView2DCompound<T>::getArity() const
    {
        return data.size();
    }

    template<class T>
    const std::span<T>& DataView2DCompound<T>::getData() const
    {
        return data;
    }

    template<class T>
    void DataView2DCompound<T>::setData(const std::span<T>& newDataSource)
    {
        data = newDataSource;
    }

    template<class T>
    void DataView2DCompound<T>::setData(const T* newDataSource, size_t N)
    {
        data = std::span<T>(newDataSource, newDataSource + N);
    }

    template<class T>
    const std::array<DataSelector_t<T>, 6>& DataView2DCompound<T>::getSelectors() const
    {
        return selectors;
    }

    template<class T>
    void DataView2DCompound<T>::setSelectors(const std::array<DataSelector_t<T>, 6>& newSelectors)
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
    void DataView2DCompound<T>::setSelector(const ColumnType column, const DataSelector_t<T>& selector)
    {
        const auto columnID = getColumnID(column);

        if (columnID == COLUMN_UNSUPPORTED)
        {
            std::string errMsg = "Column type ";
            errMsg += "\"" + getColumnIDName(column) + "\"";
            errMsg += " not supported for plot type ";
            errMsg += "\"" + getPlotStyleName(styleID) + "\"";

            throw UnsupportedOperationError( errMsg );
        }

        selectors        [columnID - 1] = selector;
        columnAssignments[columnID - 1] = columnID;
        columnHeadlines  [columnID - 1] = getColumnIDName(column);
    }

    template<class T>
    bool DataView2DCompound<T>::isDummy() const
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
    bool DataView2DCompound<T>::isComplete() const
    {
        // *INDENT-OFF*
        if (isDummy())      {return true;}
        if (data.empty())   {return false;}

        const auto isNullSelector = [] (const DataSelector_t<T>& selector) {return selector == nullptr;};
        // *INDENT-ON*

        switch (styleID)
        {
            case PlotStyle2D::Dots:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle2D::Points:
                return checkColumnListOccupationIsFrom(selectors, {1, 2, 3, 4, 5}, isNullSelector);
            case PlotStyle2D::XErrorBars:
                return checkColumnListOccupationIsFrom(selectors, {3, 4}, isNullSelector);
            case PlotStyle2D::YErrorBars:
                return checkColumnListOccupationIsFrom(selectors, {3, 4}, isNullSelector);
            case PlotStyle2D::XYErrorBars:
                return checkColumnListOccupationIsFrom(selectors, {4, 6}, isNullSelector);
            case PlotStyle2D::Lines:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle2D::LinesPoints:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle2D::FilledCurves:
                return checkColumnListOccupationIsFrom(selectors, {1, 2, 3}, isNullSelector);
            case PlotStyle2D::XErrorLines:
                return checkColumnListOccupationIsFrom(selectors, {3, 4}, isNullSelector);
            case PlotStyle2D::YErrorLines:
                return checkColumnListOccupationIsFrom(selectors, {3, 4}, isNullSelector);
            case PlotStyle2D::XYErrorLines:
                return checkColumnListOccupationIsFrom(selectors, {4, 6}, isNullSelector);
            case PlotStyle2D::Steps:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle2D::FSteps:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle2D::FillSteps:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle2D::Impulses:
                return checkColumnListOccupationIsFrom(selectors, {1, 2}, isNullSelector);
            case PlotStyle2D::Boxes:
                return checkColumnListOccupationIsFrom(selectors, {1, 2, 3}, isNullSelector);
            case PlotStyle2D::HBoxes:
                return checkColumnListOccupationIsFrom(selectors, {1, 2, 3}, isNullSelector);
            case PlotStyle2D::BoxErrorBars:
                return checkColumnListOccupationIsFrom(selectors, {3, 4, 5}, isNullSelector);
            case PlotStyle2D::BoxxyError:
                return checkColumnListOccupationIsFrom(selectors, {4, 6}, isNullSelector);
            case PlotStyle2D::Arrows:
                return checkColumnListOccupationIsFrom(selectors, {4}, isNullSelector);
            case PlotStyle2D::Vectors:
                return checkColumnListOccupationIsFrom(selectors, {4}, isNullSelector);
            case PlotStyle2D::Image:
                return checkColumnListOccupationIsFrom(selectors, {3}, isNullSelector);
            case PlotStyle2D::Custom:
                return checkColumnListOccupationIsFrom(selectors, {1, 2, 3, 4, 5, 6}, isNullSelector);
        }

        return false;
    }
}

#endif // DATAVIEW2DCOMPOUND_TXX
