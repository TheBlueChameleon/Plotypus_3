#ifndef PLOT_WITH_AXES_TXX
#define PLOT_WITH_AXES_TXX

namespace Plotypus
{
    template<class T>
    DataViewDefaultCompound<T>& PlotOrthogonalAxes::addDataViewCompound(DataViewDefaultCompound<T>* dataView)
    {
        dataViews.push_back(dataView);
        return *dataView;
    }

    template<class T>
    DataViewDefaultCompound<T>& PlotOrthogonalAxes::addDataViewCompound(const PlotStyle style, const std::string& label)
    {
        DataViewDefaultCompound<T>* dataView = new DataViewDefaultCompound<T>(style, label);
        return addDataViewCompound(dataView);
    }

    template<class T>
    DataViewDefaultCompound<T>& PlotOrthogonalAxes::addDataViewCompound(const std::span<T>& data, const DataSelector_t<T>& selectorY, const PlotStyle style, const std::string& label)
    {
        DataViewDefaultCompound<T>* dataView = new DataViewDefaultCompound<T>(style, label);

        dataView->setData(data);
        dataView->setSelector(ColumnType::Y, selectorY);

        return addDataViewCompound(dataView);
    }

    template<class T>
    DataViewDefaultCompound<T>& PlotOrthogonalAxes::addDataViewCompound(T* data, const size_t N, const DataSelector_t<T>& selectorY, const PlotStyle style, const std::string& label)
    {
        DataViewDefaultCompound<T>* dataView = new DataViewDefaultCompound<T>(style, label);

        dataView->setData(data, N);
        dataView->setSelector(ColumnType::Y, selectorY);

        return addDataViewCompound(dataView);
    }

    template<class T>
    DataViewDefaultCompound<T>& PlotOrthogonalAxes::addDataViewCompound(const std::string& func, const PlotStyle style, const std::string& label)
    {
        DataViewDefaultCompound<T>* dataView = new DataViewDefaultCompound<T>(style, label);

        dataView->setFunc(func);

        return addDataViewCompound(dataView);
    }
}

#endif // PLOT_WITH_AXES_TXX
