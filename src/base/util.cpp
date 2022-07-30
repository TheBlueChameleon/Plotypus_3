#include <iostream>

#include "util.h"

using namespace Plotypus;

namespace Plotypus
{
    // ---------------------------------------------------------------------- //
    // general purpose

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

    // ---------------------------------------------------------------------- //
    // throw if ...

    void throwIfInvalidFilename(const std::string& component, const std::string& stringToTest)
    {
        if (stringToTest.find_first_of(INVALID_FILENAME_CHARS) != std::string::npos)
        {
            throw InvalidFilenameError("Attempted to set invalid " + component + ".\n" +
                                       "   value               : '" + stringToTest + "'\n" +
                                       "   forbidden characters: " + INVALID_FILENAME_CHARS
                                      );
        }
    }

    // ---------------------------------------------------------------------- //
    // column assignment magic

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

    // ---------------------------------------------------------------------- //
    // enum name lookups

    std::string getTerminalName(FileType fileType)
    {
        // *INDENT-OFF*
        switch(fileType)
        {
            case FileType::Custom:      return "Custom";
            case FileType::Ascii:       return "Ascii";
            case FileType::Gif:         return "gif";
            case FileType::Jpeg:        return "Jpeg";
            case FileType::LaTeX:       return "LaTeX";
            case FileType::Pdf:         return "Pdf";
            case FileType::Png:         return "Png";
            case FileType::PostScript:  return "PostScript";
            case FileType::Screen:      return "Screen";
        }
        // *INDENT-ON*

        return "(undefined)";
    }

    std::string getLengthUnitName(LengthUnit lengthUnit)
    {
        // *INDENT-OFF*
        switch(lengthUnit)
        {
            case LengthUnit::Centimeter: return "cm";
            case LengthUnit::Inch:       return "in";
        }
        // *INDENT-ON*

        return "(undefined)";
    }

    std::string getColumnIDName(const ColumnType columnType)
    {
        // *INDENT-OFF*
        switch(columnType)
        {
            case ColumnType::Column1:      return "column 1";
            case ColumnType::Column2:      return "column 2";
            case ColumnType::Column3:      return "column 3";
            case ColumnType::Column4:      return "column 4";
            case ColumnType::Column5:      return "column 5";
            case ColumnType::Column6:      return "column 6";
            case ColumnType::X:            return "X";
            case ColumnType::Y:            return "Y";
            case ColumnType::Y2:           return "Y2";
            case ColumnType::Z:            return "Z";
            case ColumnType::DeltaX:       return "Delta X";
            case ColumnType::DeltaY:       return "Delta Y";
            case ColumnType::DeltaZ:       return "Delta Z";
            case ColumnType::XLow:         return "X_low";
            case ColumnType::XHigh:        return "X_high";
            case ColumnType::YLow:         return "Y_low";
            case ColumnType::YHigh:        return "Y_high";
            case ColumnType::Pointsize:    return "Pointsize";
            case ColumnType::Pointtype:    return "Pointtype";
            case ColumnType::Color:        return "Color";
            case ColumnType::Boxwidth:     return "Boxwidth";
            case ColumnType::Length:       return "Length";
            case ColumnType::Angle:        return "angle";
        }
        // *INDENT-ON*

        return "(undefined)";
    }

    std::string getPlotStyleName(const PlotStyle2D plotStyleID)
    {
        // *INDENT-OFF*
        switch(plotStyleID)
        {
            case PlotStyle2D::Dots:         return "dots";
            case PlotStyle2D::Points:       return "points";
            case PlotStyle2D::XErrorBars:   return "xerrorbars";
            case PlotStyle2D::YErrorBars:   return "yerrorbars";
            case PlotStyle2D::XYErrorBars:  return "xyerrorbars";
            case PlotStyle2D::Lines:        return "lines";
            case PlotStyle2D::LinesPoints:  return "linespoints";
            case PlotStyle2D::FilledCurves: return "filledcurves";
            case PlotStyle2D::XErrorLines:  return "xerrorlines";
            case PlotStyle2D::YErrorLines:  return "yerrorlines";
            case PlotStyle2D::XYErrorLines: return "xyerrorlines";
            case PlotStyle2D::Steps:        return "steps";
            case PlotStyle2D::FSteps:       return "fsteps";
            case PlotStyle2D::FillSteps:    return "fillsteps";
            case PlotStyle2D::Boxes:        return "boxes";
            case PlotStyle2D::HBoxes:       return "boxxyerror";
            case PlotStyle2D::BoxErrorBars: return "boxerrorbars";
            case PlotStyle2D::BoxxyError:   return "boxxyerror";
            case PlotStyle2D::Arrows:       return "arrows";
            case PlotStyle2D::Vectors:      return "vectors";
            case PlotStyle2D::Custom:       return "custom";
        }
        // *INDENT-ON*

        return "(undefined)";
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

    std::string optionalQuotedTextString(const std::string& optionName, const std::optional<std::string>& option)
    {
        // *INDENT-OFF*
        std::stringstream buffer;
        if (option.has_value()) {return "";}
        else                    {buffer << optionName << " " << std::quoted(option.value()) << " ";
                                 return buffer.str();}
        // *INDENT-ON*
    }

    std::string optionalNumberString(const std::string& optionName, const double number, bool turnOn)
    {
        // *INDENT-OFF*
        std::stringstream buffer;
        if (turnOn) {buffer << optionName << " " << number << " ";
                     return buffer.str();}
        else        {return "";}
        // *INDENT-ON*
    }

    std::string optionalNumberString(const std::string& optionName, const double number)
    {
        return optionalNumberString(optionName, number, number != 0.);
    }

};
