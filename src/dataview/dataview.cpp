#include "dataview.h"

using namespace Plotypus;

namespace Plotypus
{
    DataView::DataView(const PlotStyle style, const std::string& label) :
        title(label)
    {
        setStyleID(style);
    }

    DataView::DataView(const std::string& style, const std::string& label) :
        title(label), style(style), styleID(PlotStyle::Custom)
    {}

    void DataView::reset()
    {
        styleID                     = PlotStyle::Custom;
        styleFamily                 = PlotStyleFamily::Undefined;
        title                       = "";
        style                       = "lines";
        options                     = "";
        dataFilename                = "";
        numberPrecision             = -1;
        columnSeparatorTxt          = "\t";
        columnSeparatorDat          = "\t";
        binaryDataOutput            = true;
        autoGenerateDataFilename    = true;
    }

    const std::string& DataView::getTitle() const
    {
        return title;
    }

    void DataView::setTitle(const std::string& newTitle)
    {
        title = newTitle;
    }

    const std::string& DataView::getStyle() const
    {
        return style;
    }

    void DataView::setStyle(const std::string& newStyle)
    {
        styleID     = PlotStyle::Custom;
        styleFamily = PlotStyleFamily::Custom;
        style       = newStyle;
    }

    const PlotStyle DataView::getStyleID() const
    {
        return styleID;
    }

    void DataView::setStyleID(const PlotStyle newStyle)
    {
        styleID     = newStyle;
        styleFamily = getPlotStyleFamily(newStyle);
        style       = getPlotStyleName(newStyle);
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
        throwIfInvalidFilename("data output filename", newDataFilename);
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
