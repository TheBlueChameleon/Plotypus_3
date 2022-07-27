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
        for (size_t i = 0u; i < getArity(); ++i)
        {
            fetchData(lineBuffer, i, missingXColumn);
            for (const auto datapoint : lineBuffer)
            {
                hFile << datapoint << columnSeparatorDat;
            }
            hFile << std::endl;
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

    void DataView2D::writeUsingSpecification(std::ostream& hFile) const
    {
        // *INDENT-OFF*
        if (isFunction()) {return;}
        // *INDENT-ON*

        bool firstValue = true;

        hFile << "using ";
        for (auto i = 0u; i < columnAssignments.size(); ++i)
        {

            if (columnAssignments[i] != COLUMN_UNUSED)
            {
                // *INDENT-OFF*
                if (firstValue) {firstValue = false;}
                else            {hFile << ":";}
                // *INDENT-ON*

                hFile << generateColumnFormat(columnFormats[i], columnAssignments[i], columnAssignments);
            }
        }
        hFile << " ";
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

    size_t DataView2D::getLineStyle() const
    {
        return lineStyle;
    }

    void DataView2D::setLineStyle(size_t newLineStyle)
    {
        lineStyle = newLineStyle;
    }

    bool DataView2D::isFunction() const
    {
        return !func.empty();
    }

    size_t DataView2D::getColumnID(const ColumnTypes columnType) const
    {
        switch (columnType)
        {
            // *INDENT-OFF*
            case ColumnTypes::Column1: return 1;
            case ColumnTypes::Column2: return 2;
            case ColumnTypes::Column3: return 3;
            case ColumnTypes::Column4: return 4;
            case ColumnTypes::Column5: return 5;
            case ColumnTypes::Column6: return 6;

            case ColumnTypes::X: return 1;
            case ColumnTypes::Y: return 2;
            case ColumnTypes::Y2:
                if (styleID == PlotStyle2D::FilledCurves)   {return 3;}
                else                                        {return COLUMN_UNSUPPORTED;}
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
                        return COLUMN_UNSUPPORTED;
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
                        return COLUMN_UNSUPPORTED;
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
                        return COLUMN_UNSUPPORTED;
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
                        return COLUMN_UNSUPPORTED;
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
                        return COLUMN_UNSUPPORTED;
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
                        return COLUMN_UNSUPPORTED;
                }

            case ColumnTypes::Pointsize:
                // *INDENT-OFF*
                if (styleID == PlotStyle2D::Points) {return 3;}
                else                                {return COLUMN_UNSUPPORTED;}

            case ColumnTypes::Pointtype:
                if (styleID == PlotStyle2D::Points) {return 4;}
                else                                {return COLUMN_UNSUPPORTED;}

            case ColumnTypes::Color:
                if (styleID == PlotStyle2D::Points) {return 5;}
                else                                {return COLUMN_UNSUPPORTED;}

            case ColumnTypes::Boxwidth:
                if (styleID == PlotStyle2D::Boxes || styleID == PlotStyle2D::HBoxes)    {return 3;}
                else                                                                    {return COLUMN_UNSUPPORTED;}

            case ColumnTypes::Length:
                if (styleID == PlotStyle2D::Arrows) {return 3;}
                else                                {return COLUMN_UNSUPPORTED;}

            case ColumnTypes::Angle:
                if (styleID == PlotStyle2D::Arrows) {return 4;}
                else                                {return COLUMN_UNSUPPORTED;}
                // *INDENT-ON*

            case ColumnTypes::Z:
            case ColumnTypes::DeltaZ:
                return COLUMN_UNSUPPORTED;
        }

        return COLUMN_UNSUPPORTED;
    }

    // ====================================================================== //

    void DataView2D::writeTxtData(std::ostream& hFile) const
    {
        // *INDENT-OFF*
        if      (isDummy())     {hFile << "(external input from " << std::quoted(dataFilename) << ")"  << std::endl; return;}
        else if (isFunction())  {hFile << "(function " << std::quoted(func) << ", title " << std::quoted(title) << ")"  << std::endl; return;}
        else if (!isComplete()) {throw UnsupportedOperationError("Unsupported column type or non-consecutive list of columns detected");}
        // *INDENT-ON*
        else
        {
            const auto isUnusedColumn = [] (const size_t assignment)
            {
                return assignment == COLUMN_UNUSED;
            };

            bool missingXColumn = (columnAssignments[0] == COLUMN_UNUSED);
            auto lineLength     = getConsecutiveEntriesCount(columnAssignments, isUnusedColumn);

            std::vector<double> lineBuffer(lineLength);

            for (const auto& headline : columnHeadlines)
            {
                hFile << headline << columnSeparatorTxt;
            }
            hFile << std::endl;

            hFile << std::setprecision(numberPrecision);
            for (size_t i = 0u; i < getArity(); ++i)
            {
                fetchData(lineBuffer, i, missingXColumn);
                for (const auto datapoint : lineBuffer)
                {
                    hFile << datapoint << columnSeparatorTxt;
                }
                hFile << std::endl;
            }
        }
    }

    void DataView2D::writeDatData() const
    {
        // *INDENT-OFF*
        if (isDummy())      {return;}
        if (isFunction())   {return;}
        if (!isComplete())  {throw UnsupportedOperationError("Unsupported column type or non-consecutive list of columns detected");}

        const auto isUnusedColumn = [] (const size_t assignment) {return assignment == COLUMN_UNUSED;};

        bool missingXColumn = (columnAssignments[0] == COLUMN_UNUSED);
        auto lineLength     = getConsecutiveEntriesCount(columnAssignments, isUnusedColumn);

        std::vector<double> lineBuffer(lineLength);
        std::fstream hFile = openOrThrow(dataFilename);

        if (binaryDataOutput)   {writeDatDataBin(hFile, lineBuffer, missingXColumn);}
        else                    {writeDatDataAsc(hFile, lineBuffer, missingXColumn);}
        // *INDENT-ON*
    }

    void DataView2D::writeScriptData(std::ostream& hFile, const StylesCollection& stylesColloction) const
    {
        // *INDENT-OFF*
        if (isFunction()) {hFile << func << " ";}
        else
        {
            hFile << std::quoted(dataFilename) << " ";
            if (binaryDataOutput) {hFile << "binary format=\"%float64\" ";}
        }
        writeUsingSpecification(hFile);

        if (!options.empty()) {hFile << options << " ";}
        hFile << optionalQuotedTextString("title", title);

        hFile << "with " << style << " ";
        hFile << optionalStyleString("linestyle", lineStyle);

        stylesColloction.writePointStyleCode(hFile, pointStyle);
        // *INDENT-ON*
    }
}
