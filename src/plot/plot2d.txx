#ifndef PLOT2D_TXX
#define PLOT2D_TXX

namespace Plotypus
{
    template<class T>
    T& Plot2D::dataViewAs(const size_t i)
    {
        return dynamic_cast<T&>(dataView(i));
    }

    template<class T>
    DataView&  Plot2D::addDataViewCompound(DataView2DCompound<T>* dataView)
    {
        dataViews.push_back(dataView);
        return *dataViews.back();
    }

    template<class T>
    DataView& Plot2D::addDataViewCompound(const PlotStyle2D style, const std::string& label)
    {
        DataView2DCompound<T>* dataView = new DataView2DCompound<T>(style, label);
        return addDataViewCompound(dataView);
    }

    template<class T>
    DataView& Plot2D::addDataViewCompound(const std::span<T>& data, const DataSelector<T>& selectorY, const std::string& label)
    {
        DataView2DCompound<T>* dataView = new DataView2DCompound<T>(PlotStyle2D::Lines, label);

        dataView->setData(data);
        dataView->setSelector(ColumnTypes::Y, selectorY);

        return addDataViewCompound(dataView);
    }

    template<class T>
    DataView& Plot2D::addDataViewCompound(const std::string& func, const std::string& label)
    {
        DataView2DCompound<T>* dataView = new DataView2DCompound<T>(PlotStyle2D::Lines, label);

        dataView->setFunc(func);

        return addDataViewCompound(dataView);
    }
}

#endif // PLOT2D_TXX
