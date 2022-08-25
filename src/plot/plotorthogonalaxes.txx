#ifndef PLOT_WITH_AXES_TXX
#define PLOT_WITH_AXES_TXX

namespace Plotypus
{
    template<class T>
    DataViewDefaultCompound<T>& PlotOrthogonalAxes::addDataViewCompound(DataViewDefaultCompound<T>* dataView)
    {
        checkAndSetStyleFamily(dataView->getStyleFamily(), allowedStyleFamiles);

        // *INDENT-OFF*
        if      (styleFamily == PlotStyleFamily::Orthogonal2D) {mode3D = false;}
        else if (styleFamily == PlotStyleFamily::Orthogonal3D) {mode3D = true;}
        // *INDENT-ON*

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
