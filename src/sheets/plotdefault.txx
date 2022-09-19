#ifndef PLOT_WITH_AXES_TXX
#define PLOT_WITH_AXES_TXX

namespace Plotypus
{
    template<class T>
    DataViewDefaultCompound<T>& PlotDefault::addDataViewCompound(DataViewDefaultCompound<T>* dataView)
    {
        checkAndSetStyleFamily(dataView->getPlotStyleFamily(), allowedStyleFamiles);

        // *INDENT-OFF*
        if      (plotStyleFamily == PlotStyleFamily::Orthogonal2D) {setMode3D(false);}
        else if (plotStyleFamily == PlotStyleFamily::Orthogonal3D) {setMode3D(true) ;}
        // *INDENT-ON*

        return *static_cast<DataViewDefaultCompound<T>*>(DataviewCollection::addDataview(dataView));
    }

    template<class T>
    DataViewDefaultCompound<T>& PlotDefault::addDataViewCompound(const PlotStyle style, const std::string& label)
    {
        DataViewDefaultCompound<T>* dataView = new DataViewDefaultCompound<T>(style, label);
        return addDataViewCompound(dataView);
    }

    template<class T>
    DataViewDefaultCompound<T>& PlotDefault::addDataViewCompound(const std::span<T>& data, const PlotStyle style, const std::string& label)
    {
        DataViewDefaultCompound<T>* dataView = new DataViewDefaultCompound<T>(style, label);

        dataView->setData(data);

        return addDataViewCompound(dataView);
    }

    template<class T>
    DataViewDefaultCompound<T>& PlotDefault::addDataViewCompound(T* data, const size_t N, const PlotStyle style, const std::string& label)
    {
        DataViewDefaultCompound<T>* dataView = new DataViewDefaultCompound<T>(style, label);

        dataView->setData(data, N);

        return addDataViewCompound(dataView);
    }

    template<class T>
    DataViewDefaultCompound<T>& PlotDefault::addDataViewCompound(const std::string& func, const PlotStyle style, const std::string& label)
    {
        DataViewDefaultCompound<T>* dataView = new DataViewDefaultCompound<T>(style, label);

        dataView->setFunc(func);

        return addDataViewCompound(dataView);
    }
}

#endif // PLOT_WITH_AXES_TXX
