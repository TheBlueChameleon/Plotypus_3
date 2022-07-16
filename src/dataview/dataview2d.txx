#include <iomanip>
#include <iostream>
#include <functional>

#include "../base/util.h"
#include "../definitions/types.h"
#include "../plot/plot.h"

#include "dataview2d.h"

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
    void DataView2D<T>::writeDatDataAsc(std::ostream& hFile) const
    {

    }

    template<class T>
    void DataView2D<T>::writeDatDataBin(std::ostream& hFile) const
    {

    }

    // ====================================================================== //

    template<class T>
    DataView2D<T>::DataView2D(const std::string& label, const std::string& style, const std::string& dataColumnFormat) :
        DataView(label, style, dataColumnFormat)
    {}

    // ====================================================================== //

    template<class T>
    void DataView2D<T>::reset()
    {
        DataView::reset();

        clearFunctionMembers();
        clearNonFunctionMembers();

        lineStyle  = -1;
        pointStyle = -1;
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
    bool DataView2D<T>::isDummy() const
    {
        if (
            dataX.empty() &&
            dataY.empty() &&
            dataErrorX.empty() &&
            dataErrorY.empty() &&
            selectorX == nullptr &&
            selectorY == nullptr &&
            selectorErrorX == nullptr &&
            selectorErrorY == nullptr
        )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template<class T>
    bool DataView2D<T>::isComplete() const
    {
        // *INDENT-OFF*
        if (isDummy()) {return true;}

        if (func.empty()) {
            const auto sizeX = dataX.size();
            const auto sizeY = dataY.size();
            const auto sizeEX = dataErrorX.size();
            const auto sizeEY = dataErrorY.size();

            if (!sizeY)                         {return false;}
            if (sizeX  && (sizeX  != sizeY))    {return false;}
            if (sizeEX && (sizeEX != sizeY))    {return false;}
            if (sizeEY && (sizeEY != sizeY))    {return false;}
            if (!selectorY)                     {return false;}
        }
        // *INDENT-ON*

        return true;
    }

    // ====================================================================== //

    template<class T>
    void DataView2D<T>::writeDatData() const
    {
        std::fstream hFile = openOrThrow(dataFilename);

        // *INDENT-OFF*
        if (binaryDataOutput)   {writeDatDataBin(hFile);}
        else                    {writeDatDataAsc(hFile);}
        // *INDENT-ON*
    }

    template<class T>
    void DataView2D<T>::writeScriptData(std::ostream& hFile) const
    {
        // *INDENT-OFF*
        if (func.empty())   {hFile << std::quoted(dataFilename);}
        else                {hFile << func;}

        hFile << " with " << style;
        if (!label.empty()) {hFile << " title " << std::quoted(label);}

        const auto lineStyleID = lineStyle + 1;
        if (lineStyleID)    {hFile << " linestyle " << std::to_string(lineStyleID);}

        if (pointStyle + 1) {/* stylesCollection from report? */};

        if (!options.empty()) {hFile << " " << options;}
        hFile << " ";
        // *INDENT-ON*
    }
}
