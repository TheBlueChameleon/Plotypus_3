#include "dataview.h"

using namespace Plotypus;

namespace Plotypus
{
    DataView::DataView(const std::string& label, const std::string& style, const std::string& dataColumnFormat) :
        label(label), style(style), dataColumnFormat(dataColumnFormat)
    {}

    void DataView::reset()
    {
        label               = "";
        style               = "";
        dataColumnFormat    = "#";
    }

    const std::string& DataView::getLabel() const
    {
        return label;
    }

    void DataView::setLabel(const std::string& newLabel)
    {
        label = newLabel;
    }

    const std::string& DataView::getStyle() const
    {
        return style;
    }

    void DataView::setStyle(const std::string& newStyle)
    {
        style = newStyle;
    }

    const std::string& DataView::getDataColumnFormat() const
    {
        return dataColumnFormat;
    }

    void DataView::setDataColumnFormat(const std::string& newDataColumnFormat)
    {
        dataColumnFormat = newDataColumnFormat;
    }

    void DataView::setDataColumnFormatPositive()
    {
        dataColumnFormat = "($# >= 0 ? $# : 1/0)";
    }
}
