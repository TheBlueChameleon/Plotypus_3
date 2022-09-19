#include "../base/util.h"

#include "dataviewdefault.h"

namespace Plotypus
{
    void DataviewDefault::clearFunctionMembers()
    {
        func = "";
    }

    void DataviewDefault::writeDatDataAsc(std::ostream& hFile, std::vector<double>& lineBuffer, bool missingXColumn) const
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

    void DataviewDefault::writeDatDataBin(std::ostream& hFile, std::vector<double>& lineBuffer, bool missingXColumn) const
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

    void DataviewDefault::writeUsingSpecification(std::ostream& hFile) const
    {
        // *INDENT-OFF*
        if (isFunction()) {return;}
        // *INDENT-ON*

        bool firstValue = true;

        hFile << " using ";
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
    }

    size_t DataviewDefault::getColumnIDOrThrow(const ColumnType columnType)
    {
        auto columnID = getColumnID(plotStyleID, columnType);

        if (columnID == COLUMN_UNSUPPORTED)
        {
            std::string errMsg = "Column type ";
            errMsg += "\"" + getColumnIDName(columnType) + "\"";
            errMsg += " not supported for plot type ";
            errMsg += "\"" + getPlotStyleName(plotStyleID) + "\"";

            throw UnsupportedOperationError( errMsg );
        }

        return columnID;
    }

    void DataviewDefault::postSetColumnActions(const ColumnType columnType)
    {
        if (plotStyleID == PlotStyle::FilledCurves && columnType == ColumnType::DeltaY)
        {
            makePlusMinusFormat();
        }
        else if (contains(plotStyleID, {PlotStyle::Points, PlotStyle::Points3D,
                                        PlotStyle::LinesPoints, PlotStyle::LinesPoints3D
                                       }))
        {
            // *INDENT-OFF*
            if (columnType == ColumnType::Pointtype) {variablePointType  = true;}
            if (columnType == ColumnType::Pointsize) {variablePointSize  = true;}
            if (columnType == ColumnType::Color    ) {variablePointColor = true;}
            // *INDENT-ON*
        }
    }

    void DataviewDefault::makePlusMinusFormat()
    {
        /* check prerequisites:
         * - is PlotStyle::FilledCurve
         * - has Y column
         * - has DeltaY column
         * - more?
         */

        // *INDENT-OFF*
        const auto id_data  = getColumnID(PlotStyle::FilledCurves, ColumnType::Y);
        const auto id_delta = getColumnID(PlotStyle::FilledCurves, ColumnType::DeltaY);

        const auto index_data  = id_data  - 1;
        const auto index_delta = id_delta - 1;

        if (plotStyleID != PlotStyle::FilledCurves)          {throw UnsupportedOperationError("PlusMinusFormat can only be set for FilledCurves");}
        if (columnAssignments[index_data]  == COLUMN_UNUSED) {throw UnsupportedOperationError("PlusMinusFormat can only be set if Y values are present");}
        if (columnAssignments[index_delta] == COLUMN_UNUSED) {throw UnsupportedOperationError("PlusMinusFormat can only be set if delta Y values are present");}
        // *INDENT-ON*


        /* write format:
         * - for ColID::YLow : "(!2 - !3)"
         * - for ColID::YHigh: "(!2 + !3)"
         * - use symbol COLUMN_FORMAT_ESCAPE_INTERNAL_COLUMN_ID for "!"
         * - use appropriate getters for "2", "3"
         */

        const auto index_yLow  = getColumnID(PlotStyle::FilledCurves, ColumnType::YLow ) - 1;
        const auto index_yHigh = getColumnID(PlotStyle::FilledCurves, ColumnType::YHigh) - 1;

        const std::string element_data  = "!" + std::to_string(id_data);
        const std::string element_delta = "!" + std::to_string(id_delta);

        columnFormats[index_yLow ] = "(" + element_data + " - " + element_delta + ")";
        columnFormats[index_yHigh] = "(" + element_data + " + " + element_delta + ")";
    }

    // ====================================================================== //

    DataviewDefault::DataviewDefault(const DataviewType type, const PlotStyle plotStyleID) :
        Dataview(type, plotStyleID)
    {}

    DataviewDefault::DataviewDefault(const DataviewType type, const PlotStyle plotStyleID, const std::string& title) :
        Dataview(type, plotStyleID, title)
    {}

    DataviewDefault::DataviewDefault(const DataviewType type, const std::string& plotStyle) :
        Dataview(type, plotStyle)
    {}

    DataviewDefault::DataviewDefault(const DataviewType type, const std::string& plotStyle, const std::string& title) :
        Dataview(type, plotStyle, title)
    {}

    // ====================================================================== //

    DataviewDefault& DataviewDefault::reset()
    {
        Dataview::reset();

        clearFunctionMembers();
        clearNonFunctionMembers();

        lineStyle.reset();
        pointStyle.reset();

        columnAssignments = {COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED};
        columnFormats     = {COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT};
        columnHeadlines   = {};

        return *this;
    }

    DataviewDefault& DataviewDefault::setPlotStyleID(const PlotStyle newPlotStyle)
    {
        Dataview::setPlotStyleID(newPlotStyle);

        if (newPlotStyle == PlotStyle::HBoxes)
        {
            columnFormats[0] = "(0)";               // x     : constant zero
            columnFormats[1] = "$!1";               // y     : x column
            columnFormats[2] = "(0)";               // x_low : constant zero
            columnFormats[3] = "$!2";               // x_high: y column
            columnFormats[4] = "($!1 - $!3 / 2.)";  // y_low : x column minus boxwidth halves
            columnFormats[5] = "($!1 - $!3 / 2.)";  // y_high: x column plus boxwidth halves
        }

        return *this;
    }

    const std::string& DataviewDefault::getFunc() const
    {
        return func;
    }

    DataviewDefault& DataviewDefault::setFunc(const std::string& newFunc)
    {
        func        = newFunc;
        clearNonFunctionMembers();
        return *this;
    }

    size_t DataviewDefault::getLineStyle() const
    {
        return lineStyle.value_or(OPTIONAL_SIZE_T_DEFAULT);
    }

    DataviewDefault& DataviewDefault::setLineStyle(size_t newLineStyle)
    {
        lineStyle = newLineStyle;
        return *this;
    }

    DataviewDefault& DataviewDefault::clearLineStyle()
    {
        lineStyle.reset();
        return *this;
    }

    size_t DataviewDefault::getPointStyle() const
    {
        return pointStyle.value_or(OPTIONAL_SIZE_T_DEFAULT);
    }

    DataviewDefault& DataviewDefault::setPointStyle(size_t newPointStyle)
    {
        pointStyle = newPointStyle;
        return *this;
    }

    DataviewDefault& DataviewDefault::clearPointStyle()
    {
        pointStyle.reset();
        return *this;
    }

    size_t& DataviewDefault::columnAssignment(const size_t columnID)
    {
        throwIfInvalidIndex("column ID", columnID, columnAssignments);
        return columnAssignments[columnID];
    }

    size_t& DataviewDefault::columnAssignment(const ColumnType columnType)
    {
        return columnAssignment(getColumnID(plotStyleID, columnType) - 1);
    }

    std::string& DataviewDefault::columnFormat(const size_t columnID)
    {
        throwIfInvalidIndex("column ID", columnID, columnAssignments);
        return columnFormats[columnID];
    }

    std::string& DataviewDefault::columnFormat(const ColumnType columnType)
    {
        return columnFormat(getColumnID(plotStyleID, columnType) - 1);
    }

    std::string& DataviewDefault::columnHeadline(const size_t columnID)
    {
        throwIfInvalidIndex("column ID", columnID, columnAssignments);
        return columnHeadlines[columnID];
    }

    std::string& DataviewDefault::columnHeadline(const ColumnType columnType)
    {
        return columnHeadline(getColumnID(plotStyleID, columnType) - 1);
    }

    bool DataviewDefault::getVariablePointSize() const
    {
        return variablePointSize;
    }

    DataviewDefault& DataviewDefault::setVariablePointSize(bool newVariablePointSize)
    {
        variablePointSize = newVariablePointSize;
        return *this;
    }

    bool DataviewDefault::getVariablePointType() const
    {
        return variablePointType;
    }

    DataviewDefault& DataviewDefault::setVariablePointType(bool newVariablePointType)
    {
        variablePointType = newVariablePointType;
        return *this;
    }

    bool DataviewDefault::getVariablePointColor() const
    {
        return variablePointColor;
    }

    DataviewDefault& DataviewDefault::setVariablePointColor(bool newVariablePointColor)
    {
        variablePointColor = newVariablePointColor;
        return *this;
    }

    bool DataviewDefault::isFunction() const
    {
        return !func.empty();
    }

// ====================================================================== //

    void DataviewDefault::writeTxtData(std::ostream& hFile) const
    {
        // *INDENT-OFF*
        if      (isDummy())     {hFile << "(external input from " << std::quoted(dataFilename) << ")"  << std::endl; return;}
        else if (isFunction())  {hFile << "(function " << std::quoted(func) << ", title " << std::quoted(title.value_or("")) << ")"  << std::endl; return;}
        else if (!isComplete()) {throw UnsupportedOperationError("Incomplete or non-consecutive list of columns or unsupported column type or detected");}
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

    void DataviewDefault::writeDatData() const
    {

        // *INDENT-OFF*
        if (isDummy())      {return;}
        if (isFunction())   {return;}
        if (!isComplete())  {throw UnsupportedOperationError("Incomplete or non-consecutive list of columns or unsupported column type or detected");}

        const auto isUnusedColumn = [] (const size_t assignment) {return assignment == COLUMN_UNUSED;};

        bool missingXColumn = (columnAssignments[0] == COLUMN_UNUSED);
        auto lineLength     = getConsecutiveEntriesCount(columnAssignments, isUnusedColumn);

        std::vector<double> lineBuffer(lineLength);
        std::fstream hFile = openOrThrow(dataFilename);

        if (binaryDataOutput)   {writeDatDataBin(hFile, lineBuffer, missingXColumn);}
        else                    {writeDatDataAsc(hFile, lineBuffer, missingXColumn);}
        // *INDENT-ON*
    }

    void DataviewDefault::writeScriptData(std::ostream& hFile, const StylesCollection& stylesColloction) const
    {
        // *INDENT-OFF*
        if (isFunction()) {hFile << func;}
        else
        {
            hFile << " " << std::quoted(dataFilename);
            if (binaryDataOutput) {hFile << " binary format=\"%float64\"";}
        }
        writeUsingSpecification(hFile);

        hFile << optionalQuotedStringArgument("title", title);

        hFile << " with " << plotStyle;

        hFile << optionalSizeTArgument("linestyle", lineStyle);
        stylesColloction.writePointStyleCode(hFile, pointStyle.value_or(OPTIONAL_SIZE_T_DEFAULT));

        if (variablePointSize ) {hFile << " pointsize variable";}
        if (variablePointType ) {hFile << " pointtype variable";}
        if (variablePointColor) {hFile << " linecolor variable";}

        if (options.has_value()) {hFile << " " << options.value();}
        // *INDENT-ON*
    }
}
