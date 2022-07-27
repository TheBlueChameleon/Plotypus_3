#include <iostream>
#include <sstream>

#include "util.h"

using namespace Plotypus;

namespace Plotypus
{
    void checkFilename(const std::string& component, const std::string& stringToTest)
    {
        if (stringToTest.find_first_of(invalidFilenameChars) != std::string::npos)
        {
            throw InvalidFilenameError("Attempted to set invalid " + component + ".\n" +
                                       "   value               : '" + stringToTest + "'\n" +
                                       "   forbidden characters: " + invalidFilenameChars
                                      );
        }
    }

    const std::string getColumnIDName(const ColumnTypes columnType)
    {
        switch(columnType)
        {
            case ColumnTypes::Column1:
                return "column 1";
            case ColumnTypes::Column2:
                return "column 2";
            case ColumnTypes::Column3:
                return "column 3";
            case ColumnTypes::Column4:
                return "column 4";
            case ColumnTypes::Column5:
                return "column 5";
            case ColumnTypes::Column6:
                return "column 6";
            case ColumnTypes::X:
                return "X";
            case ColumnTypes::Y:
                return "Y";
            case ColumnTypes::Y2:
                return "Y2";
            case ColumnTypes::Z:
                return "Z";
            case ColumnTypes::DeltaX:
                return "Delta X";
            case ColumnTypes::DeltaY:
                return "Delta Y";
            case ColumnTypes::DeltaZ:
                return "Delta Z";
            case ColumnTypes::XLow:
                return "X_low";
            case ColumnTypes::XHigh:
                return "X_high";
            case ColumnTypes::YLow:
                return "Y_low";
            case ColumnTypes::YHigh:
                return "Y_high";
            case ColumnTypes::Pointsize:
                return "Pointsize";
            case ColumnTypes::Pointtype:
                return "Pointtype";
            case ColumnTypes::Color:
                return "Color";
            case ColumnTypes::Boxwidth:
                return "Boxwidth";
            case ColumnTypes::Length:
                return "Length";
            case ColumnTypes::Angle:
                return "angle";
        }

        return "(undefined)";
    }

    const std::string getPlotStyleName(const PlotStyle2D plotStyleID)
    {
        switch(plotStyleID)
        {
            case PlotStyle2D::Dots:
                return "dots";
            case PlotStyle2D::Points:
                return "points";
            case PlotStyle2D::XErrorBars:
                return "xerrorbars";
            case PlotStyle2D::YErrorBars:
                return "yerrorbars";
            case PlotStyle2D::XYErrorBars:
                return "xyerrorbars";
            case PlotStyle2D::Lines:
                return "lines";
            case PlotStyle2D::LinesPoints:
                return "linespoints";
            case PlotStyle2D::FilledCurves:
                return "filledcurves";
            case PlotStyle2D::XErrorLines:
                return "xerrorlines";
            case PlotStyle2D::YErrorLines:
                return "yerrorlines";
            case PlotStyle2D::XYErrorLines:
                return "xyerrorlines";
            case PlotStyle2D::Steps:
                return "steps";
            case PlotStyle2D::FSteps:
                return "fsteps";
            case PlotStyle2D::FillSteps:
                return "fillsteps";
            case PlotStyle2D::Boxes:
                return "boxes";
            case PlotStyle2D::HBoxes:
                return "boxxyerror";
            case PlotStyle2D::BoxErrorBars:
                return "boxerrorbars";
            case PlotStyle2D::BoxxyError:
                return "boxxyerror";
            case PlotStyle2D::Arrows:
                return "arrows";
            case PlotStyle2D::Vectors:
                return "vectors";
            case PlotStyle2D::Custom:
                return "custom";
        }

        return "(undefined)";
    }

    const std::string generateColumnFormat(const std::string& formatTemplate, size_t columnID, const columnAssignmentList_t& columnAssignments)
    {
        std::stringstream buffer;
        bool escape = false; // COLUMN_FORMAT_ESCAPE_INTERNAL_COLUMN_ID ??

        // *INDENT-OFF*
        for (auto chr : formatTemplate) {
            if      (chr == COLUMN_FORMAT_PLACEHOLDER_COLUMN_NUMBER) {buffer << columnID;}
            else if (chr == COLUMN_FORMAT_ESCAPE_INTERNAL_COLUMN_ID) {escape = true;}
            else {
                if (escape) {buffer << columnAssignments.at(chr - '1');}
                else        {buffer << chr;}
            }
        }
        // *INDENT-ON*

        return buffer.str();
    }

    std::fstream openOrThrow(const std::string& filename, const std::ios_base::openmode& mode)
    {
        std::fstream hFile(filename, mode);

        if (!hFile.is_open())
        {
            throw FileIOError("Could not open '" + filename + "'");
        }

        return hFile;
    }

    void runGnuplot(const std::string& filename, bool verbose)
    {
        // *INDENT-OFF*
        if (verbose)    {std::cout << "About to run gnuplot script '" << filename << "' ..." << std::endl;}

        const auto error = std::system((std::string("gnuplot ") + filename).data());

        if (verbose) {
            if (error)  {std::cerr << "gnuplot did not succeed. Error code: " << error << std::endl;}
            else        {std::cout << "done." << std::endl;}
        }
        // *INDENT-ON*
    }

    std::string optionalStyleString(const std::string& optionName, const size_t styleID)
    {
        // *INDENT-OFF*
        if (styleID == STYLE_ID_DEFAULT)    {return "";}
        else                                {return optionName + " " + std::to_string(styleID + 1) + " ";}
        // *INDENT-ON*
    }

    std::string optionalQuotedTextString(const std::string& optionName, const std::string& option)
    {
        // *INDENT-OFF*
        std::stringstream buffer;
        if (option.empty()) {return "";}
        else                {buffer << optionName << " " << std::quoted(option) << " ";
                             return buffer.str();}
        // *INDENT-ON*
    }

    std::string optionalNumber(const std::string& optionName, const double number, bool turnOn)
    {
        // *INDENT-OFF*
        std::stringstream buffer;
        if (turnOn) {buffer << optionName << " " << number << " ";
                     return buffer.str();}
        else        {return "";}
        // *INDENT-ON*
    }

    std::string optionalNumber(const std::string& optionName, const double number)
    {
        return optionalNumber(optionName, number, number != 0.);
    }

};
