#include <iomanip>
#include <iostream>
#include <functional>

#include "../definitions/types.h"

#include "../plot/plot.h"

#include "dataview2d.h"

using namespace Plotypus;

namespace Plotypus
{
    template<class T>
    DataView2D<T>::DataView2D(const std::string& label, const std::string& style, const std::string& dataColumnFormat) :
        DataView(label, style, dataColumnFormat)
    {}

    template<class T>
    void DataView2D<T>::reset()
    {
        DataView::reset();

        dataY        = std::span<T>();
        selector    = std::function<double (const T)>();
        func        = "";
    }

    template<class T>
    const std::span<const double>& DataView2D<T>::getDataX() const
    {
        return dataX;
    }

    template<class T>
    void DataView2D<T>::setDataX(const std::span<const double>& newData)
    {
        dataX = newData;
        func = "";
    }

    template<class T>
    void DataView2D<T>::setDataX(const double* newData, size_t N)
    {
        setDataX( std::span<const T>(newData, newData + N) );
    }

    template<class T>
    const std::span<const T>& DataView2D<T>::getDataY() const
    {
        return dataY;
    }

    template<class T>
    void DataView2D<T>::setDataY(const std::span<const T>& newData)
    {
        dataY = newData;
        func = "";
    }

    template<class T>
    void DataView2D<T>::setDataY(const T* newData, size_t N)
    {
        setDataY( std::span<const T>(newData, newData + N) );
    }

    template<class T>
    const std::span<const T>& DataView2D<T>::getDataErrorY() const
    {
        return dataErrorY;
    }

    template<class T>
    void DataView2D<T>::setDataErrorY(const std::span<const T>& newDataErrorY)
    {
        dataErrorY = newDataErrorY;
    }

    template<class T>
    void DataView2D<T>::setDataErrorY(const T* newData, size_t N)
    {
        setDataErrorY( std::span<const T>(newData, newData + N) );
    }

    template<class T>
    const std::span<const T>& DataView2D<T>::getDataErrorX() const
    {
        return dataErrorX;
    }

    template<class T>
    inline void DataView2D<T>::setDataErrorX(const std::span<const T>& newDataErrorX)
    {
        dataErrorX = newDataErrorX;
    }

    template<class T>
    void DataView2D<T>::setDataErrorX(const T* newData, size_t N)
    {
        setDataErrorX( std::span<const T>(newData, newData + N) );
    }

    template<class T>
    const DataSelector<T>& DataView2D<T>::getSelector() const
    {
        return selector;
    }

    template<class T>
    void DataView2D<T>::setSelector(const DataSelector<T>& newSelector)
    {
        selector    = newSelector;
        func        = "";
    }

    template<class T>
    const std::string& DataView2D<T>::getFunc() const
    {
        return func;
    }

    template<class T>
    void DataView2D<T>::setFunc(const std::string& newFunc)
    {
        func        = newFunc;
        dataY        = std::span<T>();
        selector    = std::function<double (const T)>();
    }

    template<class T>
    int DataView2D<T>::getLineStyle() const
    {
        return lineStyle;
    }

    template<class T>
    void DataView2D<T>::setLineStyle(int newLineStyle)
    {
        lineStyle = newLineStyle;
    }

    template<class T>
    bool DataView2D<T>::complete() const
    {
        // *INDENT-OFF*
        if (func.empty()) {
            const auto sizeX = dataX.size();
            const auto sizeY = dataY.size();

            if (!sizeY)                     {return false;}
            if (sizeX && (sizeX != sizeY))  {return false;}
            if (!selector)                  {return false;}
        }
        // *INDENT-ON*

        return true;
    }

    // ====================================================================== //

    template<class T>
    void DataView2D<T>::writePdfData(std::ostream& hFile) const
    {
        if (func.empty())
        {
            hFile << .5;
        }
        else
        {
            hFile << func << " with " << style;
            // *INDENT-OFF*
            if (!label.empty()) {hFile << " title " << std::quoted(label);}
            const auto lineStyleID = lineStyle + 1;
            if (lineStyleID)    {hFile << " linestyle " << std::to_string(lineStyleID);}

            if (!options.empty()) {hFile << " " << options;}
            // *INDENT-ON*
        }
        hFile << " ";
    }
}
