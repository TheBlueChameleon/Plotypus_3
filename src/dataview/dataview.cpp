#include "../base/util.h"

#include "dataview.h"

using namespace Plotypus;

namespace Plotypus
{
    DataView::DataView(const PlotStyle2D style, const std::string& label) :
        label(label)
    {
        setStyleID(style);
    }

    DataView::DataView(const std::string& style, const std::string& label) :
        label(label), style(style), styleID(PlotStyle2D::Custom)
    {}

    void DataView::reset()
    {
        styleID                     = PlotStyle2D::Custom;
        label                       = "";
        style                       = "lines";
        options                     = "";
        dataFilename                = "";
        numberPrecision             = 6;
        columnSeparatorTxt          = "\t";
        columnSeparatorDat          = "\t";
        binaryDataOutput            = true;
        autoGenerateDataFilename    = true;
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

    const PlotStyle2D DataView::getStyleID() const
    {
        return styleID;
    }

    void DataView::setStyleID(const PlotStyle2D newStyle)
    {
        styleID = newStyle;

        switch (newStyle)
        {
            case PlotStyle2D::Dots:
                this->style = "dots";
                break;
            case PlotStyle2D::Points:
                this->style = "points";
                break;
            case PlotStyle2D::XErrorBars:
                this->style = "xerrorbars";
                break;
            case PlotStyle2D::YErrorBars:
                this->style = "yerrorbars";
                break;
            case PlotStyle2D::XYErrorBars:
                this->style = "xyerrorbars";
                break;

            case PlotStyle2D::Lines:
                this->style = "lines";
                break;
            case PlotStyle2D::LinesPoints:
                this->style = "linespoints";
                break;
            case PlotStyle2D::FilledCurves:
                this->style = "filledcurves";
                break;
            case PlotStyle2D::XErrorLines:
                this->style = "xerrorlines";
                break;
            case PlotStyle2D::YErrorLines:
                this->style = "yerrorlines";
                break;
            case PlotStyle2D::XYErrorLines:
                this->style = "xyerrorlines";
                break;

            case PlotStyle2D::Steps:
                this->style = "steps";
                break;
            case PlotStyle2D::FSteps:
                this->style = "fsteps";
                break;
            case PlotStyle2D::FillSteps:
                this->style = "fillsteps";
                break;

            case PlotStyle2D::Boxes:
                this->style = "boxes";
                break;
            case PlotStyle2D::HBoxes:
                this->style = "boxxyerror";
                break;
            case PlotStyle2D::BoxErrorBars:
                this->style = "boxerrorbars";
                break;
            case PlotStyle2D::BoxxyError:
                this->style = "boxxyerror";
                break;

            case PlotStyle2D::Arrows:
                this->style = "arrows";
                break;
            case PlotStyle2D::Vectors:
                this->style = "vectors";
                break;

            case PlotStyle2D::Custom:
                this->style = "lines";
                break;
        }
    }

    bool DataView::getBinaryDataOutput() const
    {
        return binaryDataOutput;
    }

    void DataView::setBinaryDataOutput(bool newBinaryDataOutput)
    {
        binaryDataOutput = newBinaryDataOutput;
    }

    const std::string& DataView::getOptions() const
    {
        return options;
    }

    void DataView::setOptions(const std::string& newOptions)
    {
        options = newOptions;
    }

    const std::string& DataView::getDataFilename() const
    {
        return dataFilename;
    }

    void DataView::setDataFilename(const std::string& newDataFilename) const
    {
        checkFilename("data output filename", newDataFilename);
        dataFilename = newDataFilename;
    }

    bool DataView::getAutoGenerateDataFilename() const
    {
        return autoGenerateDataFilename;
    }

    void DataView::setAutoGenerateDataFilename(bool newAutoGenerateDataFilename)
    {
        autoGenerateDataFilename = newAutoGenerateDataFilename;
    }

    int DataView::getNumberPrecision() const
    {
        return numberPrecision;
    }

    void DataView::setNumberPrecision(int newNumberPrecision)
    {
        numberPrecision = newNumberPrecision;
    }

    const std::string& DataView::getColumnSeparatorTxt() const
    {
        return columnSeparatorTxt;
    }

    void DataView::setColumnSeparatorTxt(const std::string& newSeparatorTXT)
    {
        columnSeparatorTxt = newSeparatorTXT;
    }

    const std::string& DataView::getColumnSeparatorDat() const
    {
        return columnSeparatorDat;
    }

    void DataView::setColumnSeparatorDat(const std::string& newSeparatorDAT)
    {
        columnSeparatorDat = newSeparatorDAT;
    }
}
