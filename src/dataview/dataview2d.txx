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
    void DataView2D<T>::writeDatDataAsc(std::ostream& hFile) const
    {

    }

    template<class T>
    void DataView2D<T>::writeDatDataBin(std::ostream& hFile) const
    {

    }

    // ====================================================================== //

    template<class T>
    DataView2D<T>::DataView2D(const std::string& label, const PlotStyle2D style, const std::string& dataColumnFormat) :
        DataView(label, style, dataColumnFormat)
    {}

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
//        if (
//            dataX.empty() &&
//            dataY.empty() &&
//            dataErrorX.empty() &&
//            dataErrorY.empty() &&
//            selectorX == nullptr &&
//            selectorY == nullptr &&
//            selectorErrorX == nullptr &&
//            selectorErrorY == nullptr
//        )
//        {
//            return true;
//        }
//        else
//        {
//            return false;
//        }
        return true;
    }

    template<class T>
    bool DataView2D<T>::isComplete() const
    {
        // *INDENT-OFF*
        if (isDummy()) {return true;}

//        if (func.empty()) {
//            const auto sizeX = dataX.size();
//            const auto sizeY = dataY.size();
//            const auto sizeEX = dataErrorX.size();
//            const auto sizeEY = dataErrorY.size();

//            if (!sizeY)                         {return false;}
//            if (sizeX  && (sizeX  != sizeY))    {return false;}
//            if (sizeEX && (sizeEX != sizeY))    {return false;}
//            if (sizeEY && (sizeEY != sizeY))    {return false;}
//            if (!selectorY)                     {return false;}
//        }
        // *INDENT-ON*

        return true;
    }

    template<class T>
    size_t DataView2D<T>::getColumnID(const ColumnTypes columnType) const
    {
        switch (columnType)
        {
            case ColumnTypes::column1:
                return 1;
            case ColumnTypes::column2:
                return 2;
            case ColumnTypes::column3:
                return 3;
            case ColumnTypes::column4:
                return 4;
            case ColumnTypes::column5:
                return 5;
            case ColumnTypes::column6:
                return 6;

            case ColumnTypes::X:
                return 1;
            case ColumnTypes::Y:

            case ColumnTypes::DeltaX:
            case ColumnTypes::DeltaY:
            case ColumnTypes::XLow:
            case ColumnTypes::XHigh:
            case ColumnTypes::YLow:
            case ColumnTypes::YHigh:
            case ColumnTypes::Pointsize:
            case ColumnTypes::Pointtype:
            case ColumnTypes::Color:

            case ColumnTypes::Boxwidth:

            case ColumnTypes::Length:
            case ColumnTypes::Angle:
                break;

            case ColumnTypes::Z:
            case ColumnTypes::DeltaZ:
                throw UnsupportedOperationError("Not supported for 2D plots");
        }
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
