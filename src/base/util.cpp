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

    columnTypeList_t getAssignmentsForType(const PlotStyle styleID, const size_t columnListLength)
    {
        // *INDENT-OFF*
        switch (styleID) {
            case PlotStyle::Dots:
                switch (columnListLength) {
                    case 1: return {ColumnType::Y, ColumnType::Column2, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 2: return {ColumnType::X, ColumnType::Y, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                }
                break;
            case PlotStyle::Points:
                switch (columnListLength) {
                    case 1: return {ColumnType::Y, ColumnType::Column2, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 2: return {ColumnType::X, ColumnType::Y, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 3: return {ColumnType::X, ColumnType::Y, ColumnType::Pointsize, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 4: return {ColumnType::X, ColumnType::Y, ColumnType::Pointsize, ColumnType::Pointtype, ColumnType::Column5, ColumnType::Column6};
                    case 5: return {ColumnType::X, ColumnType::Y, ColumnType::Pointsize, ColumnType::Pointtype, ColumnType::Color, ColumnType::Column6};
                }
                break;
            case PlotStyle::XErrorBars:
                switch (columnListLength) {
                    case 3: return {ColumnType::X, ColumnType::Y, ColumnType::DeltaX, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 4: return {ColumnType::X, ColumnType::Y, ColumnType::XLow, ColumnType::XHigh, ColumnType::Column5, ColumnType::Column6};
                }
                break;
            case PlotStyle::YErrorBars:
                switch (columnListLength) {
                    case 2: return {ColumnType::Y, ColumnType::DeltaY, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 3: return {ColumnType::X, ColumnType::Y, ColumnType::DeltaY, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 4: return {ColumnType::X, ColumnType::Y, ColumnType::YLow, ColumnType::YHigh, ColumnType::Column5, ColumnType::Column6};
                }
                break;
            case PlotStyle::XYErrorBars:
                switch (columnListLength) {
                    case 4: return {ColumnType::Y, ColumnType::DeltaX, ColumnType::DeltaY, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 6: return {ColumnType::X, ColumnType::Y, ColumnType::XLow, ColumnType::XHigh, ColumnType::YLow, ColumnType::YHigh};
                }
                break;
            case PlotStyle::Lines:
                switch (columnListLength) {
                    case 1: return {ColumnType::Y, ColumnType::Column2, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 2: return {ColumnType::X, ColumnType::Y, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                }
                break;
            case PlotStyle::LinesPoints:
                switch (columnListLength) {
                    case 1: return {ColumnType::Y, ColumnType::Column2, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 2: return {ColumnType::X, ColumnType::Y, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 3: return {ColumnType::X, ColumnType::Y, ColumnType::Pointsize, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 4: return {ColumnType::X, ColumnType::Y, ColumnType::Pointsize, ColumnType::Pointtype, ColumnType::Column5, ColumnType::Column6};
                    case 5: return {ColumnType::X, ColumnType::Y, ColumnType::Pointsize, ColumnType::Pointtype, ColumnType::Color, ColumnType::Column6};
                }
                break;
            case PlotStyle::FilledCurves:
                switch (columnListLength) {
                    case 1: return {ColumnType::Y, ColumnType::Column2, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 2: return {ColumnType::X, ColumnType::Y, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 3: return {ColumnType::X, ColumnType::Y, ColumnType::Y2, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                }
                break;
            case PlotStyle::XErrorLines:
                switch (columnListLength) {
                    case 3: return {ColumnType::X, ColumnType::Y, ColumnType::DeltaX, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 4: return {ColumnType::X, ColumnType::Y, ColumnType::XLow, ColumnType::XHigh, ColumnType::Column5, ColumnType::Column6};
                }
                break;
            case PlotStyle::YErrorLines:
                switch (columnListLength) {
                    case 2: return {ColumnType::Y, ColumnType::DeltaY, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 3: return {ColumnType::X, ColumnType::Y, ColumnType::DeltaY, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 4: return {ColumnType::X, ColumnType::Y, ColumnType::YLow, ColumnType::YHigh, ColumnType::Column5, ColumnType::Column6};
                }
                break;
            case PlotStyle::XYErrorLines:
                switch (columnListLength) {
                    case 4: return {ColumnType::Y, ColumnType::DeltaX, ColumnType::DeltaY, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 6: return {ColumnType::X, ColumnType::Y, ColumnType::XLow, ColumnType::XHigh, ColumnType::YLow, ColumnType::YHigh};
                }
                break;
            case PlotStyle::Steps:
                switch (columnListLength) {
                    case 1: return {ColumnType::Y, ColumnType::Column2, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 2: return {ColumnType::X, ColumnType::Y, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                }
                break;
            case PlotStyle::FSteps:
                switch (columnListLength) {
                    case 1: return {ColumnType::Y, ColumnType::Column2, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 2: return {ColumnType::X, ColumnType::Y, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                }
                break;
            case PlotStyle::FillSteps:
                switch (columnListLength) {
                    case 1: return {ColumnType::Y, ColumnType::Column2, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 2: return {ColumnType::X, ColumnType::Y, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                }
                break;
            case PlotStyle::Impulses:
                switch (columnListLength) {
                    case 1: return {ColumnType::Y, ColumnType::Column2, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 2: return {ColumnType::X, ColumnType::Y, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                }
                break;
            case PlotStyle::Boxes:
                switch (columnListLength) {
                    case 1: return {ColumnType::Y, ColumnType::Column2, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 2: return {ColumnType::X, ColumnType::Y, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 3: return {ColumnType::X, ColumnType::Y, ColumnType::Boxwidth, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                }
                break;
            case PlotStyle::HBoxes:
                switch (columnListLength) {
                    case 1: return {ColumnType::Y, ColumnType::Column2, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 2: return {ColumnType::X, ColumnType::Y, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 3: return {ColumnType::X, ColumnType::Y, ColumnType::Boxwidth, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                }
                break;
            case PlotStyle::BoxErrorBars:
                switch (columnListLength) {
                    case 3: return {ColumnType::X, ColumnType::Y, ColumnType::DeltaY, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 4: return {ColumnType::X, ColumnType::Y, ColumnType::DeltaX, ColumnType::DeltaY, ColumnType::Column5, ColumnType::Column6};
                    case 5: return {ColumnType::X, ColumnType::Y, ColumnType::YLow, ColumnType::YHigh, ColumnType::DeltaX, ColumnType::Column6};
                }
                break;
            case PlotStyle::BoxxyError:
                switch (columnListLength) {
                    case 4: return {ColumnType::X, ColumnType::Y, ColumnType::DeltaX, ColumnType::DeltaY, ColumnType::Column5, ColumnType::Column6};
                    case 6: return {ColumnType::X, ColumnType::Y, ColumnType::XLow, ColumnType::XHigh, ColumnType::YLow, ColumnType::YHigh};
                }
                break;
            case PlotStyle::Arrows:
                if (columnListLength == 4) {return {ColumnType::X, ColumnType::Y, ColumnType::Length, ColumnType::Angle, ColumnType::Column5, ColumnType::Column6};}
                break;
            case PlotStyle::Vectors:
                if (columnListLength == 4) {return {ColumnType::X, ColumnType::Y, ColumnType::DeltaX, ColumnType::DeltaY, ColumnType::Column5, ColumnType::Column6};}
                break;
            case PlotStyle::Image:
                if (columnListLength == 3) {return {ColumnType::X, ColumnType::Y, ColumnType::Color, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};}
                break;

            case PlotStyle::Dots3D:
                if (columnListLength == 3) {return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Column3, ColumnType::Column5, ColumnType::Column6};}
                break;
            case PlotStyle::Points3D:
                switch (columnListLength) {
                    case 3: return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 4: return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Pointsize, ColumnType::Column5, ColumnType::Column6};
                    case 5: return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Pointsize, ColumnType::Pointtype, ColumnType::Column6};
                    case 6: return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Pointsize, ColumnType::Pointtype, ColumnType::Color};
                }
                break;
            case PlotStyle::Lines3D:
                if (columnListLength == 3) {return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Column3, ColumnType::Column5, ColumnType::Column6};}
                break;
            case PlotStyle::LinesPoints3D:
                switch (columnListLength) {
                    case 3: return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 4: return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Pointsize, ColumnType::Column5, ColumnType::Column6};
                    case 5: return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Pointsize, ColumnType::Pointtype, ColumnType::Column6};
                    case 6: return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Pointsize, ColumnType::Pointtype, ColumnType::Color};
                }
                break;
            case PlotStyle::Boxes3D:
                switch (columnListLength) {
                    case 3: return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
                    case 4: return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Boxwidth, ColumnType::Column5, ColumnType::Column6};
                    case 5: return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Boxwidth, ColumnType::Color, ColumnType::Column6};
                }
                break;
            case PlotStyle::Impulses3D:
                if (columnListLength == 3) {return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};}
                break;
            case PlotStyle::Image3D:
                if (columnListLength == 4) {return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::Color, ColumnType::Column5, ColumnType::Column6};}
                break;
            case PlotStyle::Vectors3D:
                if (columnListLength == 6) {return {ColumnType::X, ColumnType::Y, ColumnType::Z, ColumnType::DeltaX, ColumnType::DeltaY, ColumnType::DeltaZ};}
                break;

            case PlotStyle::Custom:
                return {ColumnType::Column1, ColumnType::Column2, ColumnType::Column3, ColumnType::Column4, ColumnType::Column5, ColumnType::Column6};
        }
        // *INDENT-ON*

        std::string msg = "Invalid argument count for plot type\n"
                          "  argument count: " + std::to_string(columnListLength) + "\n"
                          "  plot type     : " + getPlotStyleName(styleID);
        throw InvalidArgumentError(msg);
    }

    // ---------------------------------------------------------------------- //
    // enum name lookups

    std::string getTerminalName(const FileType fileType)
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

    std::string getLengthUnitName(const LengthUnit lengthUnit)
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

    std::string getPlotStyleName(const PlotStyle plotStyleID)
    {
        // *INDENT-OFF*
        switch(plotStyleID)
        {
            case PlotStyle::Dots:           return "dots";
            case PlotStyle::Points:         return "points";
            case PlotStyle::XErrorBars:     return "xerrorbars";
            case PlotStyle::YErrorBars:     return "yerrorbars";
            case PlotStyle::XYErrorBars:    return "xyerrorbars";
            case PlotStyle::Lines:          return "lines";
            case PlotStyle::LinesPoints:    return "linespoints";
            case PlotStyle::FilledCurves:   return "filledcurves";
            case PlotStyle::XErrorLines:    return "xerrorlines";
            case PlotStyle::YErrorLines:    return "yerrorlines";
            case PlotStyle::XYErrorLines:   return "xyerrorlines";
            case PlotStyle::Steps:          return "steps";
            case PlotStyle::FSteps:         return "fsteps";
            case PlotStyle::FillSteps:      return "fillsteps";
            case PlotStyle::Impulses:       return "impulses";
            case PlotStyle::Boxes:          return "boxes";
            case PlotStyle::HBoxes:         return "boxxyerror";
            case PlotStyle::BoxErrorBars:   return "boxerrorbars";
            case PlotStyle::BoxxyError:     return "boxxyerror";
            case PlotStyle::Arrows:         return "arrows";
            case PlotStyle::Vectors:        return "vectors";
            case PlotStyle::Image:          return "image pixels";
            case PlotStyle::Dots3D:         return "dots";
            case PlotStyle::Points3D:       return "points";
            case PlotStyle::Lines3D:        return "lines";
            case PlotStyle::LinesPoints3D:  return "linespoints";
            case PlotStyle::Impulses3D:     return "impulses";
            case PlotStyle::Boxes3D:        return "boxes";
            case PlotStyle::Vectors3D:      return "vectors";
            case PlotStyle::Image3D:        return "image";
            case PlotStyle::Custom:         return "custom";
        }
        // *INDENT-ON*

        return "(undefined)";
    }

    std::string getAxisName(const AxisType axis)
    {
        // *INDENT-OFF*
        switch (axis)
        {
            case AxisType::Azimuthal:   return "t";
            case AxisType::Colourbar:   return "cb";
            case AxisType::Radial:      return "r";
            case AxisType::X:           return "x";
            case AxisType::X2:          return "x2";
            case AxisType::Y:           return "y";
            case AxisType::Y2:          return "y2";
            case AxisType::Z:           return "z";
        }
        // *INDENT-ON*

        return "(undefined)";
    }

    PlotStyleFamily getPlotStyleFamily(const PlotStyle plotStyleID)
    {
        // *INDENT-OFF*
        switch(plotStyleID)
        {
            case PlotStyle::Dots:           return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::Points:         return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::XErrorBars:     return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::YErrorBars:     return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::XYErrorBars:    return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::Lines:          return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::LinesPoints:    return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::FilledCurves:   return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::XErrorLines:    return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::YErrorLines:    return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::XYErrorLines:   return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::Steps:          return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::FSteps:         return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::FillSteps:      return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::Impulses:       return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::Boxes:          return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::HBoxes:         return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::BoxErrorBars:   return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::BoxxyError:     return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::Arrows:         return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::Vectors:        return PlotStyleFamily::Orthogonal2D;
            case PlotStyle::Image:          return PlotStyleFamily::Orthogonal2D;

            case PlotStyle::Dots3D:         return PlotStyleFamily::Orthogonal3D;
            case PlotStyle::Points3D:       return PlotStyleFamily::Orthogonal3D;
            case PlotStyle::Lines3D:        return PlotStyleFamily::Orthogonal3D;
            case PlotStyle::LinesPoints3D:  return PlotStyleFamily::Orthogonal3D;
            case PlotStyle::Impulses3D:     return PlotStyleFamily::Orthogonal3D;
            case PlotStyle::Boxes3D:        return PlotStyleFamily::Orthogonal3D;
            case PlotStyle::Vectors3D:      return PlotStyleFamily::Orthogonal3D;
            case PlotStyle::Image3D:        return PlotStyleFamily::Orthogonal3D;

            case PlotStyle::Custom:         return PlotStyleFamily::Custom;
        }
        // *INDENT-ON*

        return PlotStyleFamily::Undefined;
    }

    bool hasAxisLabel(const AxisType axis)
    {
        // *INDENT-OFF*
        switch (axis)
        {
            case AxisType::Azimuthal:   return false;
            case AxisType::Colourbar:   return true;
            case AxisType::Radial:      return true;
            case AxisType::X:           return true;
            case AxisType::X2:          return true;
            case AxisType::Y:           return true;
            case AxisType::Y2:          return true;
            case AxisType::Z:           return true;
        }
        // *INDENT-ON*

        return false;
    }

    // ---------------------------------------------------------------------- //
    // strings from optional parameters

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
        if (!option.has_value()) {return "";}
        else                     {buffer << optionName << " " << std::quoted(option.value()) << " ";
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
