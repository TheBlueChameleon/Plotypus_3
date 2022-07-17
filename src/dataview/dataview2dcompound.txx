#include "dataview2dcompound.h"

namespace Plotypus
{
    template<class T>
    void DataView2DCompound<T>::clearNonFunctionMembers()
    {
        data = std::span<T>();
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
    const std::array<DataSelector<T>, 6>& DataView2DCompound<T>::getSelectors() const
    {
        return selectors;
    }

    template<class T>
    void DataView2DCompound<T>::setSelectors(const std::vector<DataSelector<T>>& newSelectors)
    {
        selectors = newSelectors;
    }

    template<class T>
    bool DataView2DCompound<T>::isDummy() const
    {
        return ((data.size() + selectors.size()) == 0) && func.empty();
    }

    template<class T>
    bool DataView2DCompound<T>::isComplete() const
    {
        // *INDENT-OFF*
        if (isDummy())      {return true;}
        if (data.empty())   {return false;}
        if (selectors[1])   {return true;}      // require at least Y data
        // *INDENT-ON*

        bool result;
        switch (styleID)
        {
            case PlotStyle2D::Dots:
                return checkColumnList(selectors, 2, 2, nullptr);
            case PlotStyle2D::Points:
                return checkColumnList(selectors, 2, 5, nullptr);
            case PlotStyle2D::XErrorBars:
                return checkColumnList(selectors, 3, 4, nullptr);
            case PlotStyle2D::YErrorBars:
                return checkColumnList(selectors, 3, 4, nullptr);
            case PlotStyle2D::XYErrorBars:
                result = checkColumnList(selectors, 4, 6, nullptr);
                if (result && selectors[5])
                {
                    result &= static_cast<bool>(selectors[4]);
                }
                return result;
            case PlotStyle2D::Lines:
                return checkColumnList(selectors, 2, 2, nullptr);
            case PlotStyle2D::LinesPoints:
                return checkColumnList(selectors, 2, 2, nullptr);
            case PlotStyle2D::FilledCurves:
                return checkColumnList(selectors, 2, 3, nullptr);
            case PlotStyle2D::XErrorLines:
                return checkColumnList(selectors, 3, 4, nullptr);
            case PlotStyle2D::YErrorLines:
                return checkColumnList(selectors, 3, 4, nullptr);
            case PlotStyle2D::XYErrorLines:
                result = checkColumnList(selectors, 4, 6, nullptr);
                if (result && selectors[5])
                {
                    result &= static_cast<bool>(selectors[4]);
                }
                return result;
            case PlotStyle2D::Steps:
                return checkColumnList(selectors, 2, 2, nullptr);
            case PlotStyle2D::FSteps:
                return checkColumnList(selectors, 2, 2, nullptr);
            case PlotStyle2D::FillSteps:
                return checkColumnList(selectors, 2, 2, nullptr);
            case PlotStyle2D::Boxes:
                return checkColumnList(selectors, 2, 3, nullptr);
            case PlotStyle2D::HBoxes:
                return checkColumnList(selectors, 2, 3, nullptr);
            case PlotStyle2D::BoxErrorBars:
                return checkColumnList(selectors, 5, 5, nullptr);
            case PlotStyle2D::BoxxyError:
                result = checkColumnList(selectors, 4, 6, nullptr);
                if (result && selectors[5])
                {
                    result &= static_cast<bool>(selectors[4]);
                }
                return result;
            case PlotStyle2D::Arrows:
                return checkColumnList(selectors, 4, 4, nullptr);
            case PlotStyle2D::Vectors:
                return checkColumnList(selectors, 4, 4, nullptr);
            case PlotStyle2D::Custom:
                return checkColumnList(selectors, 1, 6, nullptr, true);
        }

        return false;
    }

    template<class T>
    void DataView2DCompound<T>::fetchData(std::vector<double>& buffer, size_t recordID) const {}
}
