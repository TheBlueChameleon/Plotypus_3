#include "dataviewdefault.h"

namespace Plotypus
{
    void DataViewDefault::clearFunctionMembers()
    {
        func = "";
    }

    void DataViewDefault::writeDatDataAsc(std::ostream& hFile, std::vector<double>& lineBuffer, bool missingXColumn) const
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

    void DataViewDefault::writeDatDataBin(std::ostream& hFile, std::vector<double>& lineBuffer, bool missingXColumn) const
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

    void DataViewDefault::writeUsingSpecification(std::ostream& hFile) const
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

    DataViewDefault::DataViewDefault(const PlotStyle style, const std::string& label) :
        DataView(style, label)
    {}

    DataViewDefault::DataViewDefault(const std::string& style, const std::string& label) :
        DataView(style, label)
    {}

    // ====================================================================== //

    void DataViewDefault::reset()
    {
        DataView::reset();

        clearFunctionMembers();
        clearNonFunctionMembers();

        lineStyle  = -1;
        pointStyle = -1;

        columnAssignments = {COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED};
        columnFormats     = {COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT};
        columnHeadlines   = {};
    }

    void DataViewDefault::setStyleID(const PlotStyle newStyle)
    {
        DataView::setStyleID(newStyle);

        if (newStyle == PlotStyle::HBoxes)
        {
            columnFormats[0] = "(0)";               // x     : constant zero
            columnFormats[1] = "$!1";               // y     : x column
            columnFormats[2] = "(0)";               // x_low : constant zero
            columnFormats[3] = "$!2";               // x_high: y column
            columnFormats[4] = "($!1 - $!3 / 2.)";  // y_low : x column minus boxwidth halves
            columnFormats[5] = "($!1 - $!3 / 2.)";  // y_high: x column plus boxwidth halves
        }
    }

    const std::string& DataViewDefault::getFunc() const
    {
        return func;
    }

    void DataViewDefault::setFunc(const std::string& newFunc)
    {
        func        = newFunc;
        clearNonFunctionMembers();
    }

    size_t DataViewDefault::getLineStyle() const
    {
        return lineStyle;
    }

    void DataViewDefault::setLineStyle(size_t newLineStyle)
    {
        lineStyle = newLineStyle;
    }

    size_t& DataViewDefault::columnAssignment(const size_t columnID)
    {
        throwIfInvalidIndex("column ID", columnID, columnAssignments);
        return columnAssignments[columnID];
    }

    size_t& DataViewDefault::columnAssignment(const ColumnType columnType)
    {
        return columnAssignment(getColumnID(columnType) - 1);
    }

    std::string& DataViewDefault::columnFormat(const size_t columnID)
    {
        throwIfInvalidIndex("column ID", columnID, columnAssignments);
        return columnFormats[columnID];
    }

    std::string& DataViewDefault::columnFormat(const ColumnType columnType)
    {
        return columnFormat(getColumnID(columnType) - 1);
    }

    std::string& DataViewDefault::columnHeadline(const size_t columnID)
    {
        throwIfInvalidIndex("column ID", columnID, columnAssignments);
        return columnHeadlines[columnID];
    }

    std::string& DataViewDefault::columnHeadline(const ColumnType columnType)
    {
        return columnHeadline(getColumnID(columnType) - 1);
    }

    bool DataViewDefault::isFunction() const
    {
        return !func.empty();
    }

    size_t DataViewDefault::getColumnID(const ColumnType columnType) const
    {
        switch (columnType)
        {
// *INDENT-OFF*
            case ColumnType::Column1: return 1;
            case ColumnType::Column2: return 2;
            case ColumnType::Column3: return 3;
            case ColumnType::Column4: return 4;
            case ColumnType::Column5: return 5;
            case ColumnType::Column6: return 6;

            case ColumnType::X: return 1;
            case ColumnType::Y: return 2;
            case ColumnType::Y2:
                if (styleID == PlotStyle::FilledCurves)   {return 3;}
                else                                        {return COLUMN_UNSUPPORTED;}
// *INDENT-ON*

            case ColumnType::DeltaX:
                switch(styleID)
                {
                    case PlotStyle::XErrorBars:
                    case PlotStyle::XYErrorBars:
                    case PlotStyle::XErrorLines:
                    case PlotStyle::XYErrorLines:
                    case PlotStyle::BoxxyError:
                    case PlotStyle::Vectors:
                        return 3;

                    case PlotStyle::BoxErrorBars:
                        return 5;

                    case PlotStyle::Dots:
                    case PlotStyle::Points:
                    case PlotStyle::YErrorBars:
                    case PlotStyle::Lines:
                    case PlotStyle::LinesPoints:
                    case PlotStyle::YErrorLines:
                    case PlotStyle::Steps:
                    case PlotStyle::FSteps:
                    case PlotStyle::FillSteps:
                    case PlotStyle::FilledCurves:
                    case PlotStyle::Impulses:
                    case PlotStyle::Boxes:
                    case PlotStyle::HBoxes:
                    case PlotStyle::Arrows:
                    case PlotStyle::Image:
                    case PlotStyle::Dots3D:
                    case PlotStyle::Points3D:
                    case PlotStyle::Lines3D:
                    case PlotStyle::LinesPoints3D:
                    case PlotStyle::Impulses3D:
                    case PlotStyle::Boxes3D:
                    case PlotStyle::Surface3D:
                    case PlotStyle::Vectors3D:
                    case PlotStyle::Image3D:
                    case PlotStyle::Custom:
                        return COLUMN_UNSUPPORTED;
                }

            case ColumnType::DeltaY:
                switch(styleID)
                {
                    case PlotStyle::YErrorBars:
                    case PlotStyle::YErrorLines:
                    case PlotStyle::BoxErrorBars:
                        return 3;

                    case PlotStyle::XYErrorBars:
                    case PlotStyle::XYErrorLines:
                    case PlotStyle::BoxxyError:
                    case PlotStyle::Vectors:
                        return 4;

                    case PlotStyle::Dots:
                    case PlotStyle::Points:
                    case PlotStyle::XErrorBars:
                    case PlotStyle::Lines:
                    case PlotStyle::LinesPoints:
                    case PlotStyle::XErrorLines:
                    case PlotStyle::Steps:
                    case PlotStyle::FSteps:
                    case PlotStyle::FillSteps:
                    case PlotStyle::FilledCurves:
                    case PlotStyle::Impulses:
                    case PlotStyle::Boxes:
                    case PlotStyle::HBoxes:
                    case PlotStyle::Arrows:
                    case PlotStyle::Image:
                    case PlotStyle::Dots3D:
                    case PlotStyle::Points3D:
                    case PlotStyle::Lines3D:
                    case PlotStyle::LinesPoints3D:
                    case PlotStyle::Impulses3D:
                    case PlotStyle::Boxes3D:
                    case PlotStyle::Surface3D:
                    case PlotStyle::Vectors3D:
                    case PlotStyle::Image3D:
                    case PlotStyle::Custom:
                        return COLUMN_UNSUPPORTED;
                }

            case ColumnType::XLow:
                switch(styleID)
                {
                    case PlotStyle::XErrorBars:
                    case PlotStyle::XYErrorBars:
                    case PlotStyle::XErrorLines:
                    case PlotStyle::BoxxyError:
                    case PlotStyle::XYErrorLines:
                        return 3;

                    case PlotStyle::Dots:
                    case PlotStyle::Points:
                    case PlotStyle::Lines:
                    case PlotStyle::LinesPoints:
                    case PlotStyle::YErrorBars:
                    case PlotStyle::YErrorLines:
                    case PlotStyle::BoxErrorBars:
                    case PlotStyle::Steps:
                    case PlotStyle::FSteps:
                    case PlotStyle::FillSteps:
                    case PlotStyle::FilledCurves:
                    case PlotStyle::Impulses:
                    case PlotStyle::Boxes:
                    case PlotStyle::HBoxes:
                    case PlotStyle::Arrows:
                    case PlotStyle::Vectors:
                    case PlotStyle::Image:
                    case PlotStyle::Dots3D:
                    case PlotStyle::Points3D:
                    case PlotStyle::Lines3D:
                    case PlotStyle::LinesPoints3D:
                    case PlotStyle::Impulses3D:
                    case PlotStyle::Boxes3D:
                    case PlotStyle::Surface3D:
                    case PlotStyle::Vectors3D:
                    case PlotStyle::Image3D:
                    case PlotStyle::Custom:
                        return COLUMN_UNSUPPORTED;
                }

            case ColumnType::XHigh:
                switch(styleID)
                {
                    case PlotStyle::XErrorBars:
                    case PlotStyle::XYErrorBars:
                    case PlotStyle::XErrorLines:
                    case PlotStyle::XYErrorLines:
                    case PlotStyle::BoxxyError:
                        return 4;

                    case PlotStyle::Dots:
                    case PlotStyle::Points:
                    case PlotStyle::Lines:
                    case PlotStyle::LinesPoints:
                    case PlotStyle::YErrorBars:
                    case PlotStyle::YErrorLines:
                    case PlotStyle::BoxErrorBars:
                    case PlotStyle::Steps:
                    case PlotStyle::FSteps:
                    case PlotStyle::FillSteps:
                    case PlotStyle::FilledCurves:
                    case PlotStyle::Impulses:
                    case PlotStyle::Boxes:
                    case PlotStyle::HBoxes:
                    case PlotStyle::Arrows:
                    case PlotStyle::Vectors:
                    case PlotStyle::Image:
                    case PlotStyle::Dots3D:
                    case PlotStyle::Points3D:
                    case PlotStyle::Lines3D:
                    case PlotStyle::LinesPoints3D:
                    case PlotStyle::Impulses3D:
                    case PlotStyle::Boxes3D:
                    case PlotStyle::Surface3D:
                    case PlotStyle::Vectors3D:
                    case PlotStyle::Image3D:
                    case PlotStyle::Custom:
                        return COLUMN_UNSUPPORTED;
                }

            case ColumnType::YLow:
                switch(styleID)
                {
                    case PlotStyle::YErrorBars:
                    case PlotStyle::YErrorLines:
                    case PlotStyle::BoxErrorBars:
                        return 3;
                    case PlotStyle::XYErrorBars:
                    case PlotStyle::XYErrorLines:
                    case PlotStyle::BoxxyError:
                        return 5;

                    case PlotStyle::Dots:
                    case PlotStyle::Points:
                    case PlotStyle::Lines:
                    case PlotStyle::LinesPoints:
                    case PlotStyle::XErrorBars:
                    case PlotStyle::XErrorLines:
                    case PlotStyle::Steps:
                    case PlotStyle::FSteps:
                    case PlotStyle::FillSteps:
                    case PlotStyle::FilledCurves:
                    case PlotStyle::Impulses:
                    case PlotStyle::Boxes:
                    case PlotStyle::HBoxes:
                    case PlotStyle::Arrows:
                    case PlotStyle::Vectors:
                    case PlotStyle::Image:
                    case PlotStyle::Dots3D:
                    case PlotStyle::Points3D:
                    case PlotStyle::Lines3D:
                    case PlotStyle::LinesPoints3D:
                    case PlotStyle::Impulses3D:
                    case PlotStyle::Boxes3D:
                    case PlotStyle::Surface3D:
                    case PlotStyle::Vectors3D:
                    case PlotStyle::Image3D:
                    case PlotStyle::Custom:
                        return COLUMN_UNSUPPORTED;
                }

            case ColumnType::YHigh:
                switch(styleID)
                {
                    case PlotStyle::YErrorBars:
                    case PlotStyle::YErrorLines:
                    case PlotStyle::BoxErrorBars:
                        return 4;
                    case PlotStyle::XYErrorBars:
                    case PlotStyle::XYErrorLines:
                    case PlotStyle::BoxxyError:
                        return 6;

                    case PlotStyle::Dots:
                    case PlotStyle::Points:
                    case PlotStyle::Lines:
                    case PlotStyle::LinesPoints:
                    case PlotStyle::XErrorBars:
                    case PlotStyle::XErrorLines:
                    case PlotStyle::Steps:
                    case PlotStyle::FSteps:
                    case PlotStyle::FillSteps:
                    case PlotStyle::FilledCurves:
                    case PlotStyle::Impulses:
                    case PlotStyle::Boxes:
                    case PlotStyle::HBoxes:
                    case PlotStyle::Arrows:
                    case PlotStyle::Vectors:
                    case PlotStyle::Image:
                    case PlotStyle::Dots3D:
                    case PlotStyle::Points3D:
                    case PlotStyle::Lines3D:
                    case PlotStyle::LinesPoints3D:
                    case PlotStyle::Impulses3D:
                    case PlotStyle::Boxes3D:
                    case PlotStyle::Surface3D:
                    case PlotStyle::Vectors3D:
                    case PlotStyle::Image3D:
                    case PlotStyle::Custom:
                        return COLUMN_UNSUPPORTED;
                }

// *INDENT-OFF*
            case ColumnType::Pointsize:
                if (styleID == PlotStyle::Points)                                   {return 3;}
                else                                                                {return COLUMN_UNSUPPORTED;}

            case ColumnType::Pointtype:
                if (styleID == PlotStyle::Points)                                   {return 4;}
                else                                                                {return COLUMN_UNSUPPORTED;}

            case ColumnType::Color:
                if      (styleID == PlotStyle::Points)                              {return 5;}
                else if (styleID == PlotStyle::Image)                               {return 3;}
                else                                                                {return COLUMN_UNSUPPORTED;}

            case ColumnType::Boxwidth:
                if (styleID == PlotStyle::Boxes || styleID == PlotStyle::HBoxes)    {return 3;}
                else                                                                {return COLUMN_UNSUPPORTED;}

            case ColumnType::Length:
                if (styleID == PlotStyle::Arrows)                                   {return 3;}
                else                                                                {return COLUMN_UNSUPPORTED;}

            case ColumnType::Angle:
                if (styleID == PlotStyle::Arrows)                                   {return 4;}
                else                                                                {return COLUMN_UNSUPPORTED;}
// *INDENT-ON*

            case ColumnType::Z:
            case ColumnType::DeltaZ:
                return COLUMN_UNSUPPORTED;
        }

        return COLUMN_UNSUPPORTED;
    }

    // ====================================================================== //

    void DataViewDefault::writeTxtData(std::ostream& hFile) const
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

    void DataViewDefault::writeDatData() const
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

    void DataViewDefault::writeScriptData(std::ostream& hFile, const StylesCollection& stylesColloction) const
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
