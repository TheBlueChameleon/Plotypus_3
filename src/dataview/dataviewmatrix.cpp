#include "dataviewmatrix.h"

namespace Plotypus
{
    void DataviewMatrix::clearFunctionMembers()
    {
        func = "";
    }

    // ====================================================================== //

    DataviewMatrix::DataviewMatrix(const DataviewType type, const PlotStyle plotStyleID) :
        Dataview(type, plotStyleID)
    {}

    DataviewMatrix::DataviewMatrix(const DataviewType type, const PlotStyle plotStyleID, const std::string& title) :
        Dataview(type, plotStyleID, title)
    {}

    DataviewMatrix::DataviewMatrix(const DataviewType type, const std::string& plotStyle) :
        Dataview(type, plotStyle)
    {}

    DataviewMatrix::DataviewMatrix(const DataviewType type, const std::string& plotStyle, const std::string& title) :
        Dataview(type, plotStyle, title)
    {}

    // ====================================================================== //

    DataviewMatrix& DataviewMatrix::reset()
    {
        Dataview::reset();

        clearFunctionMembers();
        clearNonFunctionMembers();

        lineStyle.reset();
        pointStyle.reset();

        dataFormat = COLUMN_FORMAT_DEFAULT;

        return *this;
    }

    const std::string& DataviewMatrix::getFunc() const
    {
        return func;
    }

    DataviewMatrix& DataviewMatrix::setFunc(const std::string& newFunc)
    {
        func = newFunc;
        return *this;
    }

    size_t DataviewMatrix::getLineStyle() const
    {
        return lineStyle.value_or(OPTIONAL_SIZE_T_DEFAULT);
    }

    DataviewMatrix& DataviewMatrix::setLineStyle(const size_t newLineStyle)
    {
        lineStyle = newLineStyle;
        return *this;
    }

    DataviewMatrix& DataviewMatrix::clearLineStyle()
    {
        lineStyle.reset();
        return *this;
    }

    size_t DataviewMatrix::getPointStyle() const
    {
        return pointStyle.value_or(OPTIONAL_SIZE_T_DEFAULT);
    }

    DataviewMatrix& DataviewMatrix::setPointStyle(const size_t newPointStyle)
    {
        pointStyle = newPointStyle;
        return *this;
    }

    DataviewMatrix& DataviewMatrix::clearPointStyle()
    {
        pointStyle.reset();
        return *this;
    }

    const std::string& DataviewMatrix::getDataFormat() const
    {
        return dataFormat;
    }

    DataviewMatrix& DataviewMatrix::setDataFormat(const std::string& newDataFormat)
    {
        dataFormat = newDataFormat;
        return *this;
    }

    bool DataviewMatrix::isFunction() const
    {
        return !func.empty();
    }
}
