#include "plot2d.h"

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
        checkIndex("dataView index", i, dataViews);
        return dataViews[i];
    }

    template<class T>
    size_t Plot2D<T>::addDataView(const DataView2D<T>& dataView)
    {
        dataViews.push_back(dataView);
        return dataViews.size() - 1;
    }

    template<class T>
    size_t Plot2D<T>::addDataView(const std::span<T> dataY, const DataSelector<T>& selector, const std::string& label)
    {
        DataView2D<T> dataView(label, "lines");

        dataView.setDataY   (dataY);
        dataView.setSelectorY(selector);

        return addDataView(dataView);
    }

    template<class T>
    size_t Plot2D<T>::addDataView(const std::span<double> dataX, const std::span<T> dataY, const DataSelector<T>& selector, const std::string& label)
    {
        DataView2D<T> dataView(label, "lines");

        dataView.setDataX   (dataX);
        dataView.setDataY   (dataY);
        dataView.setSelectorY(selector);

        return addDataView(dataView);
    }

    template<class T>
    size_t Plot2D<T>::addDataView(const std::string& func, const std::string& label)
    {
        DataView2D<T> dataView(label, "lines");

        dataView.setFunc(func);

        return addDataView(dataView);
    }

    // ====================================================================== //
    // writers

    template<class T>
    void Plot2D<T>::preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const
    {
        for (size_t i = 1u; const DataView2D<T>& dataView : dataViews)
        {
            if (dataView.getAutoGenerateDataFilename())
            {
                const auto fullOutputFilename = autoDataFilename + "_" + std::to_string(i) + "." + extension;
                dataView.setDataFilename(fullOutputFilename);
            }
            ++i;
        }
    }

    template<class T>
    void Plot2D<T>::writeDatData() const
    {
        for (const DataView2D<T>& dataView : dataViews)
        {
            dataView.writeDatData();
        }
    }

    template<class T>
    void Plot2D<T>::writeScriptData(std::ostream& hFile) const
    {
        Plot::writeScriptData(hFile);

        hFile << "plot ";
        const auto viewCount = dataViews.size();
        for (size_t i = 0u; const DataView2D<T>& dataView : dataViews)
        {
            dataView.writeScriptData(hFile);
            ++i;
            if (i < viewCount)
            {
                hFile << ", \\\n\t";
            }
        }
        hFile << std::endl;
    }

    template<class T>
    void Plot2D<T>::writeScriptFooter(std::ostream& hFile, int pageNum) const
    {
        hFile << std::endl;
    }
}
