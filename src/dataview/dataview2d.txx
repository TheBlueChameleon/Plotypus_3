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
    void DataView2D<T>::clearFunctionMembers()
    {
        func = "";
    }

    template<class T>
    void DataView2D<T>::clearNonFunctionMembers()
    {
        dataX      = std::span<T>();
        dataY      = std::span<T>();
        dataErrorX = std::span<T>();
        dataErrorY = std::span<T>();

        selectorX      = nullptr;
        selectorY      = nullptr;
        selectorErrorX = nullptr;
        selectorErrorY = nullptr;
    }

    template<class T>
    DataView2D<T>::DataView2D(const std::string& label, const std::string& style, const std::string& dataColumnFormat) :
        DataView(label, style, dataColumnFormat)
    {}

    template<class T>
    void DataView2D<T>::reset()
    {
        DataView::reset();

        clearFunctionMembers();
        clearNonFunctionMembers();

        lineStyle = -1;
    }

    template<class T>
    const std::span<const T>& DataView2D<T>::getDataX() const
    {
        return dataX;
    }

    template<class T>
    void DataView2D<T>::setDataX(const std::span<const T>& newData)
    {
        dataX = newData;
        clearFunctionMembers();
    }

    template<class T>
    void DataView2D<T>::setDataX(const T* newData, size_t N)
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
        clearFunctionMembers();
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
        clearFunctionMembers();
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
        clearFunctionMembers();
    }

    template<class T>
    void DataView2D<T>::setDataErrorX(const T* newData, size_t N)
    {
        setDataErrorX( std::span<const T>(newData, newData + N) );
    }

    template<class T>
    const DataSelector<T>& DataView2D<T>::getSelectorX() const
    {
        return selectorX;
    }

    template<class T>
    void DataView2D<T>::setSelectorX(const DataSelector<T>& newSelector)
    {
        selectorX   = newSelector;
        clearFunctionMembers();
    }

    template<class T>
    const DataSelector<T>& DataView2D<T>::getSelectorY() const
    {
        return selectorY;
    }

    template<class T>
    void DataView2D<T>::setSelectorY(const DataSelector<T>& newSelector)
    {
        selectorY   = newSelector;
        clearFunctionMembers();
    }

    template<class T>
    const DataSelector<T>& DataView2D<T>::getSelectorErrorX() const
    {
        return selectorErrorX;
    }


    template<class T>
    void DataView2D<T>::setSelectorErrorX(const DataSelector<T>& newSelectorErrorX)
    {
        selectorErrorX = newSelectorErrorX;
        clearFunctionMembers();
    }

    template<class T>
    const DataSelector<T>& DataView2D<T>::getSelectorErrorY() const
    {
        return selectorErrorY;
    }

    template<class T>
    void DataView2D<T>::setSelectorErrorY(const DataSelector<T>& newSelectorErrorY)
    {
        selectorErrorY = newSelectorErrorY;
        clearFunctionMembers();
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
        clearNonFunctionMembers();
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
            if (!selectorY)                 {return false;}
        }
        // *INDENT-ON*

        return true;
    }

    // ====================================================================== //

    template<class T>
    void DataView2D<T>::writeScriptData(std::ostream& hFile) const
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
