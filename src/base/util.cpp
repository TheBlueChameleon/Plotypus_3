#include <iostream>

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

    std::fstream openOrThrow(const std::string& filename, const std::ios_base::openmode& mode)
    {
        std::fstream hFile(filename, mode);

        if (!hFile.is_open())
        {
            throw FileIOError("Could not open '" + filename + "'");
        }

        return hFile;
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

    const std::string getPlotStyleName(const PlotStyle2D styleID)
    {
        switch(styleID)
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
                return "horizontal boxes";
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

    size_t getConsecutiveCountFromColumnList(const columnAssignmentList_t& columns, bool allowMissingX)
    {
        /* Checks whether 'columns' holds the consecutives values 1..n, any order, ignoring zeros.
         * Returns number of consecutive columns, or zero if any gaps detected.
         *
         * Any occurrence of UNSUPPORTED_COLUMN triggers return 0
         * Any occurrence of UNUSED_COLUMN is ignored (~> ignoring zeros)
         *
         * Naive approach (O(n²)), okay since n == 6:
         *  find maximum and all its predecessors
         */

        // *INDENT-OFF*
        size_t max = *std::max_element(columns.begin(), columns.end());
        if (max == UNSUPPORTED_COLUMN) {return 0;}

        for (auto i = max - 1; i > allowMissingX; --i) {
            bool found = false;
            for (auto j = 0u; j < columns.size(); ++j) {
                if (columns[j] == i) {found = true; break;}
            }

            if (!found) {return 0;}
        }
        // *INDENT-ON*

        return max;
    }

};
