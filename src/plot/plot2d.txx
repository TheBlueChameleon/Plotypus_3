#include "../base/localMacros.h"

#include "plot2d.h"

using namespace Plotypus;

namespace Plotypus
{
    template<class T>
    Plot2D<T>::Plot2D(const std::string& title) :
        Plot(title)
    {
        type = PlotType::Plot2D;
    }

    template<class T>
    void Plot2D<T>::reset()
    {
        Plot::reset();

        dataViews.clear();
    }

    template<class T>
    const std::vector<DataView2D<T> >& Plot2D<T>::getDataViews() const
    {
        return dataViews;
    }

    template<class T>
    void Plot2D<T>::setDataViews(const std::vector<DataView2D<T> >& newDataViews)
    {
        dataViews = newDataViews;
    }

    template<class T>
    DataView2D<T>& Plot2D<T>::dataView(const size_t i)
    {
        CHECK_INDEX(i, dataViews, "dataView index");
        return dataViews[i];
    }

    template<class T>
    size_t Plot2D<T>::addDataView(const DataView2D<T>& dataView)
    {
        dataViews.push_back(dataView);
        return dataViews.size() - 1;
    }

    template<class T>
    void Plot2D<T>::writePdfFooter(std::ofstream& hFile, int pageNum)
    {
        hFile << "plot [][] 1/0 t\"\"" << std::endl;
    }
}
