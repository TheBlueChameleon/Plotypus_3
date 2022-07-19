#include <iomanip>
#include <iostream>
#include <functional>

#include "../base/util.h"
#include "../definitions/types.h"
#include "../plot/plot.h"

#include "dataview2d.h"

namespace Plotypus
{
    void DataView2D::clearFunctionMembers()
    {
        func = "";
    }

    void DataView2D::writeDatDataAsc(std::ostream& hFile, std::vector<double>& lineBuffer, bool missingXColumn) const
    {
        const std::string columnSeparatorDat = "\t";

        for (size_t i = 0u; i < getArity(); ++i)
        {
            fetchData(lineBuffer, 0, missingXColumn);
            for (const auto datapoint : lineBuffer)
            {
                hFile << datapoint << columnSeparatorDat;
            }
            hFile << std::endl;
//            hFile.write(
//                reinterpret_cast<char*>(lineBuffer.data()),
//                (lineBuffer.size() - missingXColumn) * sizeof(double)
//            );
        }
    }

    void DataView2D::writeDatDataBin(std::ostream& hFile, std::vector<double>& lineBuffer, bool missingXColumn) const
    {
        for (size_t i = 0u; i < getArity(); ++i)
        {
            fetchData(lineBuffer, i, missingXColumn);
            hFile.write(
                reinterpret_cast<char*>(lineBuffer.data()),
                (lineBuffer.size() - missingXColumn) * sizeof(double)
            );
        }
    }

    // ====================================================================== //

    DataView2D::DataView2D(const PlotStyle2D style, const std::string& label) :
        DataView(style, label)
    {}

    DataView2D::DataView2D(const std::string& style, const std::string& label) :
        DataView(style, label)
    {}

    // ====================================================================== //

    void DataView2D::reset()
    {
        DataView::reset();

        clearFunctionMembers();
        clearNonFunctionMembers();

        lineStyle  = -1;
        pointStyle = -1;

        columnAssignments = {UNUSED_COLUMN, UNUSED_COLUMN, UNUSED_COLUMN, UNUSED_COLUMN, UNUSED_COLUMN, UNUSED_COLUMN};
        autoColumnAssignments = true;
    }

    const std::string& DataView2D::getFunc() const
    {
        return func;
    }

    void DataView2D::setFunc(const std::string& newFunc)
    {
        func        = newFunc;
        clearNonFunctionMembers();
    }

    int DataView2D::getLineStyle() const
    {
        return lineStyle;
    }

    void DataView2D::setLineStyle(int newLineStyle)
    {
        lineStyle = newLineStyle;
    }

    bool DataView2D::getAutoColumnAssignments() const
    {
        return autoColumnAssignments;
    }

    void DataView2D::setAutoColumnAssignments(bool newAutoColumnAssignments)
    {
        autoColumnAssignments = newAutoColumnAssignments;
    }

    size_t& DataView2D::columnAssignment(size_t columnID)
    {
        return columnAssignments.at(columnID);
    }

    bool DataView2D::isFunction() const
    {
        return !func.empty();
    }

    size_t DataView2D::getColumnID(const ColumnTypes columnType) const
    {
        switch (columnType)
        {
            case ColumnTypes::Column1:
                return 1;
            case ColumnTypes::Column2:
                return 2;
            case ColumnTypes::Column3:
                return 3;
            case ColumnTypes::Column4:
                return 4;
            case ColumnTypes::Column5:
                return 5;
            case ColumnTypes::Column6:
                return 6;

            case ColumnTypes::X:
                return 1;
            case ColumnTypes::Y:
                return 2;
            case ColumnTypes::Y2:
            // *INDENT-OFF*
            if (styleID == PlotStyle2D::FilledCurves)   {return 3;}
            else                                        {return UNSUPPORTED_COLUMN;}
            // *INDENT-ON*

            case ColumnTypes::DeltaX:
                switch(styleID)
                {
                    case PlotStyle2D::XErrorBars:
                    case PlotStyle2D::XYErrorBars:
                    case PlotStyle2D::XErrorLines:
                    case PlotStyle2D::XYErrorLines:
                    case PlotStyle2D::BoxxyError:
                    case PlotStyle2D::Vectors:
                        return 3;

                    case PlotStyle2D::BoxErrorBars:
                        return 5;

                    case PlotStyle2D::Dots:
                    case PlotStyle2D::Points:
                    case PlotStyle2D::YErrorBars:
                    case PlotStyle2D::Lines:
                    case PlotStyle2D::LinesPoints:
                    case PlotStyle2D::YErrorLines:
                    case PlotStyle2D::Steps:
                    case PlotStyle2D::FSteps:
                    case PlotStyle2D::FillSteps:
                    case PlotStyle2D::FilledCurves:
                    case PlotStyle2D::Boxes:
                    case PlotStyle2D::HBoxes:
                    case PlotStyle2D::Arrows:
                    case PlotStyle2D::Custom:
                        return UNSUPPORTED_COLUMN;
                }

            case ColumnTypes::DeltaY:
                switch(styleID)
                {
                    case PlotStyle2D::YErrorBars:
                    case PlotStyle2D::YErrorLines:
                    case PlotStyle2D::BoxErrorBars:
                        return 3;

                    case PlotStyle2D::XYErrorBars:
                    case PlotStyle2D::XYErrorLines:
                    case PlotStyle2D::BoxxyError:
                    case PlotStyle2D::Vectors:
                        return 4;

                    case PlotStyle2D::Dots:
                    case PlotStyle2D::Points:
                    case PlotStyle2D::XErrorBars:
                    case PlotStyle2D::Lines:
                    case PlotStyle2D::LinesPoints:
                    case PlotStyle2D::XErrorLines:
                    case PlotStyle2D::Steps:
                    case PlotStyle2D::FSteps:
                    case PlotStyle2D::FillSteps:
                    case PlotStyle2D::FilledCurves:
                    case PlotStyle2D::Boxes:
                    case PlotStyle2D::HBoxes:
                    case PlotStyle2D::Arrows:
                    case PlotStyle2D::Custom:
                        return UNSUPPORTED_COLUMN;
                }

            case ColumnTypes::XLow:
                switch(styleID)
                {
                    case PlotStyle2D::XErrorBars:
                    case PlotStyle2D::XYErrorBars:
                    case PlotStyle2D::XErrorLines:
                    case PlotStyle2D::BoxxyError:
                    case PlotStyle2D::XYErrorLines:
                        return 3;

                    case PlotStyle2D::Dots:
                    case PlotStyle2D::Points:
                    case PlotStyle2D::Lines:
                    case PlotStyle2D::LinesPoints:
                    case PlotStyle2D::YErrorBars:
                    case PlotStyle2D::YErrorLines:
                    case PlotStyle2D::BoxErrorBars:
                    case PlotStyle2D::Steps:
                    case PlotStyle2D::FSteps:
                    case PlotStyle2D::FillSteps:
                    case PlotStyle2D::FilledCurves:
                    case PlotStyle2D::Boxes:
                    case PlotStyle2D::HBoxes:
                    case PlotStyle2D::Arrows:
                    case PlotStyle2D::Vectors:
                    case PlotStyle2D::Custom:
                        return UNSUPPORTED_COLUMN;
                }

            case ColumnTypes::XHigh:
                switch(styleID)
                {
                    case PlotStyle2D::XErrorBars:
                    case PlotStyle2D::XYErrorBars:
                    case PlotStyle2D::XErrorLines:
                    case PlotStyle2D::XYErrorLines:
                    case PlotStyle2D::BoxxyError:
                        return 4;

                    case PlotStyle2D::Dots:
                    case PlotStyle2D::Points:
                    case PlotStyle2D::Lines:
                    case PlotStyle2D::LinesPoints:
                    case PlotStyle2D::YErrorBars:
                    case PlotStyle2D::YErrorLines:
                    case PlotStyle2D::BoxErrorBars:
                    case PlotStyle2D::Steps:
                    case PlotStyle2D::FSteps:
                    case PlotStyle2D::FillSteps:
                    case PlotStyle2D::FilledCurves:
                    case PlotStyle2D::Boxes:
                    case PlotStyle2D::HBoxes:
                    case PlotStyle2D::Arrows:
                    case PlotStyle2D::Vectors:
                    case PlotStyle2D::Custom:
                        return UNSUPPORTED_COLUMN;
                }

            case ColumnTypes::YLow:
                switch(styleID)
                {
                    case PlotStyle2D::YErrorBars:
                    case PlotStyle2D::YErrorLines:
                    case PlotStyle2D::BoxErrorBars:
                        return 3;
                    case PlotStyle2D::XYErrorBars:
                    case PlotStyle2D::XYErrorLines:
                    case PlotStyle2D::BoxxyError:
                        return 5;

                    case PlotStyle2D::Dots:
                    case PlotStyle2D::Points:
                    case PlotStyle2D::Lines:
                    case PlotStyle2D::LinesPoints:
                    case PlotStyle2D::XErrorBars:
                    case PlotStyle2D::XErrorLines:
                    case PlotStyle2D::Steps:
                    case PlotStyle2D::FSteps:
                    case PlotStyle2D::FillSteps:
                    case PlotStyle2D::FilledCurves:
                    case PlotStyle2D::Boxes:
                    case PlotStyle2D::HBoxes:
                    case PlotStyle2D::Arrows:
                    case PlotStyle2D::Vectors:
                    case PlotStyle2D::Custom:
                        return UNSUPPORTED_COLUMN;
                }

            case ColumnTypes::YHigh:
                switch(styleID)
                {
                    case PlotStyle2D::YErrorBars:
                    case PlotStyle2D::YErrorLines:
                    case PlotStyle2D::BoxErrorBars:
                        return 4;
                    case PlotStyle2D::XYErrorBars:
                    case PlotStyle2D::XYErrorLines:
                    case PlotStyle2D::BoxxyError:
                        return 6;

                    case PlotStyle2D::Dots:
                    case PlotStyle2D::Points:
                    case PlotStyle2D::Lines:
                    case PlotStyle2D::LinesPoints:
                    case PlotStyle2D::XErrorBars:
                    case PlotStyle2D::XErrorLines:
                    case PlotStyle2D::Steps:
                    case PlotStyle2D::FSteps:
                    case PlotStyle2D::FillSteps:
                    case PlotStyle2D::FilledCurves:
                    case PlotStyle2D::Boxes:
                    case PlotStyle2D::HBoxes:
                    case PlotStyle2D::Arrows:
                    case PlotStyle2D::Vectors:
                    case PlotStyle2D::Custom:
                        return UNSUPPORTED_COLUMN;
                }

            case ColumnTypes::Pointsize:
                // *INDENT-OFF*
                if (styleID == PlotStyle2D::Points) {return 3;}
                else                                {return UNSUPPORTED_COLUMN;}
                // *INDENT-ON*

            case ColumnTypes::Pointtype:
                // *INDENT-OFF*
                if (styleID == PlotStyle2D::Points) {return 4;}
                else                                {return UNSUPPORTED_COLUMN;}
                // *INDENT-ON*
            case ColumnTypes::Color:
                // *INDENT-OFF*
                if (styleID == PlotStyle2D::Points) {return 5;}
                else                                {return UNSUPPORTED_COLUMN;}
                // *INDENT-ON*

            case ColumnTypes::Boxwidth:
                // *INDENT-OFF*
                if (styleID == PlotStyle2D::Boxes || styleID == PlotStyle2D::HBoxes)    {return 3;}
                else                                                                    {return UNSUPPORTED_COLUMN;}
                // *INDENT-ON*

            case ColumnTypes::Length:
                // *INDENT-OFF*
                if (styleID == PlotStyle2D::Arrows) {return 3;}
                else                                {return UNSUPPORTED_COLUMN;}
                // *INDENT-ON*
            case ColumnTypes::Angle:
                // *INDENT-OFF*
                if (styleID == PlotStyle2D::Arrows) {return 4;}
                else                                {return UNSUPPORTED_COLUMN;}
                // *INDENT-ON*

            case ColumnTypes::Z:
            case ColumnTypes::DeltaZ:
                return UNSUPPORTED_COLUMN;
        }

        return UNSUPPORTED_COLUMN;
    }

    // ====================================================================== //

    void DataView2D::writeDatData() const
    {
        // *INDENT-OFF*
        if (isDummy())      {return;}
        if (isFunction())   {return;}

        bool allowMissingX = (styleID != PlotStyle2D::Custom);
        bool missingXColumn = allowMissingX && (columnAssignments[0] == UNUSED_COLUMN);

        auto lineLength = getConsecutiveCountFromColumnList(columnAssignments, allowMissingX);
        if (!lineLength) {throw UnsupportedOperationError("Unsupported column type or non-consecutive list of columns detected");}

        std::vector<double> lineBuffer(lineLength);
        std::fstream hFile = openOrThrow(dataFilename);

        if (binaryDataOutput)   {writeDatDataBin(hFile, lineBuffer, missingXColumn);}
        else                    {writeDatDataAsc(hFile, lineBuffer, missingXColumn);}
        // *INDENT-ON*
    }

    void DataView2D::writeScriptData(std::ostream& hFile) const
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
