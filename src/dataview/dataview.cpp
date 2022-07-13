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

    void DataView::setStyle(const PlotStyle2D& newStyle)
    {
        // *INDENT-OFF*
        switch (newStyle)
        {
            case PlotStyle2D::Lines:        style = "lines"         ; break;
            case PlotStyle2D::Points:       style = "points"        ; break;
            case PlotStyle2D::LinesPoints:  style = "linespoints"   ; break;
            case PlotStyle2D::Dots:         style = "dots"          ; break;
            case PlotStyle2D::FilledCurves: style = "filledcurves"  ; break;
            case PlotStyle2D::Steps:        style = "steps"         ; break;
            case PlotStyle2D::FSteps:       style = "fsteps"        ; break;
            case PlotStyle2D::FillSteps:    style = "fillsteps"     ; break;
            case PlotStyle2D::Boxes:        style = "boxes"         ; break;
            case PlotStyle2D::Arrows:       style = "arrows"        ; break;
        }
        // *INDENT-ON*
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

    const std::string& DataView::getOptions() const
    {
        return options;
    }

    void DataView::setOptions(const std::string& newOptions)
    {
        options = newOptions;
    }

}
