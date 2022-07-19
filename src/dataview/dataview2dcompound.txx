#include <iomanip>
#include <string>

#include "dataview2dcompound.h"

namespace Plotypus
{
    template<class T>
    void DataView2DCompound<T>::clearNonFunctionMembers()
    {
        data = std::span<T>();
    }

    template<class T>
    void DataView2DCompound<T>::fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const
    {
        // *INDENT-OFF*
        const T& datapoint = data[recordID];
        for (auto i : columnAssignments) {
            if (i == UNUSED_COLUMN) {continue;}         // ignore unused columns
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
        DataView2D(style, label)
    {}

    template<class T>
    DataView2DCompound<T>::DataView2DCompound(const std::string& style, const std::string& label) :
        DataView2D(style, label)
    {}

    // ====================================================================== //

    template<class T>
    void DataView2DCompound<T>::reset()
    {
        DataView2D::reset();

        data      = std::span<T>();
        selectors = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    }

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
    const std::array<DataSelector<T>, 6>& DataView2DCompound<T>::getSelectors() const
    {
        return selectors;
    }

    template<class T>
    void DataView2DCompound<T>::setSelectors(const std::array<DataSelector<T>, 6>& newSelectors)
    {
        selectors = newSelectors;
        for (size_t i = 1u; const auto& selector : selectors)
        {
            if (selector)
            {
                columnAssignments[i-1] = i;
            }
            ++i;
        }
    }

    template<class T>
    void DataView2DCompound<T>::setSelector(const ColumnTypes column, const DataSelector<T>& selector)
    {
        const auto columnID = getColumnID(column);

        if (columnID == UNSUPPORTED_COLUMN)
        {
            std::string errMsg = "Column type ";
            errMsg += "\"" + getColumnIDName(column) + "\"";
            errMsg += " not supported for plot type ";
            errMsg += "\"" + getPlotStyleName(styleID) + "\"";

            throw UnsupportedOperationError( errMsg );
        }

        selectors        [columnID - 1] = selector;
        columnAssignments[columnID - 1] = columnID;
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
        if (!selectors[1])  {return false;}      // require at least Y data
        // *INDENT-ON*

        bool result;
        switch (styleID)
        {
            case PlotStyle2D::Dots:
                return checkColumnListComplete(selectors, 2, 2, nullptr);
            case PlotStyle2D::Points:
                return checkColumnListComplete(selectors, 2, 5, nullptr);
            case PlotStyle2D::XErrorBars:
                return checkColumnListComplete(selectors, 3, 4, nullptr);
            case PlotStyle2D::YErrorBars:
                return checkColumnListComplete(selectors, 3, 4, nullptr);
            case PlotStyle2D::XYErrorBars:
                result = checkColumnListComplete(selectors, 4, 6, nullptr);
                if (result && selectors[5])
                {
                    result &= static_cast<bool>(selectors[4]);
                }
                return result;
            case PlotStyle2D::Lines:
                return checkColumnListComplete(selectors, 2, 2, nullptr);
            case PlotStyle2D::LinesPoints:
                return checkColumnListComplete(selectors, 2, 2, nullptr);
            case PlotStyle2D::FilledCurves:
                return checkColumnListComplete(selectors, 2, 3, nullptr);
            case PlotStyle2D::XErrorLines:
                return checkColumnListComplete(selectors, 3, 4, nullptr);
            case PlotStyle2D::YErrorLines:
                return checkColumnListComplete(selectors, 3, 4, nullptr);
            case PlotStyle2D::XYErrorLines:
                result = checkColumnListComplete(selectors, 4, 6, nullptr);
                if (result && selectors[5])
                {
                    result &= static_cast<bool>(selectors[4]);
                }
                return result;
            case PlotStyle2D::Steps:
                return checkColumnListComplete(selectors, 2, 2, nullptr);
            case PlotStyle2D::FSteps:
                return checkColumnListComplete(selectors, 2, 2, nullptr);
            case PlotStyle2D::FillSteps:
                return checkColumnListComplete(selectors, 2, 2, nullptr);
            case PlotStyle2D::Boxes:
                return checkColumnListComplete(selectors, 2, 3, nullptr);
            case PlotStyle2D::HBoxes:
                return checkColumnListComplete(selectors, 2, 3, nullptr);
            case PlotStyle2D::BoxErrorBars:
                return checkColumnListComplete(selectors, 5, 5, nullptr);
            case PlotStyle2D::BoxxyError:
                result = checkColumnListComplete(selectors, 4, 6, nullptr);
                if (result && selectors[5])
                {
                    result &= static_cast<bool>(selectors[4]);
                }
                return result;
            case PlotStyle2D::Arrows:
                return checkColumnListComplete(selectors, 4, 4, nullptr);
            case PlotStyle2D::Vectors:
                return checkColumnListComplete(selectors, 4, 4, nullptr);
            case PlotStyle2D::Custom:
                return checkColumnListComplete(selectors, 1, 6, nullptr, true);
        }

        return false;
    }
}
