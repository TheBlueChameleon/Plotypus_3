#include "../base/util.h"

#include "dataviewdefault.h"

namespace Plotypus
{
    void DataviewDefault::clearFunctionMembers()
    {
        func = "";
    }

    void DataviewDefault::writeTxtHeadlines(std::ostream& hFile) const
    {
        for (const auto& headline : columnHeadlines)
        {
            hFile << headline << columnSeparatorTxt;
        }
        hFile << std::endl;
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
                lineBuffer.size() * sizeof(double)
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

        variablePointSize  = false;
        variablePointType  = false;
        variablePointColor = false;

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
            columnAssignments[3] = COLUMN_DUMMY;
            columnAssignments[4] = COLUMN_DUMMY;
            columnAssignments[5] = COLUMN_DUMMY;

            columnFormats[0] = "(0)";               // x     : constant zero
            columnFormats[1] = "(!1)";              // y     : x column
            columnFormats[2] = "(0)";               // x_low : constant zero
            columnFormats[3] = "(!2)";              // x_high: y column
            columnFormats[4] = "(!1 - !3 / 2.)";    // y_low : x column minus boxwidth halves
            columnFormats[5] = "(!1 + !3 / 2.)";    // y_high: x column plus  boxwidth halves
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

    DataviewDefault& DataviewDefault::setLineStyle(const size_t newLineStyle)
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

    DataviewDefault& DataviewDefault::setPointStyle(const size_t newPointStyle)
    {
        pointStyle = newPointStyle;
        return *this;
    }

    DataviewDefault& DataviewDefault::clearPointStyle()
    {
        pointStyle.reset();
        return *this;
    }

    DataviewDefault& DataviewDefault::setColumnAssignment(const size_t columnIndex, const size_t newSourceColumn)
    {
        throwIfInvalidIndex("column ID", columnIndex, columnAssignments);
        columnAssignments[columnIndex] = newSourceColumn;
        return *this;
    }

    DataviewDefault& DataviewDefault::setColumnAssignment(const ColumnType columnType, const size_t newSourceColumn)
    {
        const auto index = getColumnID(plotStyleID, columnType) - 1;
        columnAssignments[index] = newSourceColumn;
        return *this;
    }

    const size_t& DataviewDefault::getColumnAssignment(const size_t columnIndex) const
    {
        throwIfInvalidIndex("column ID", columnIndex, columnAssignments);
        return columnAssignments[columnIndex];
    }

    const size_t& DataviewDefault::getColumnAssignment(const ColumnType columnType) const
    {
        return getColumnAssignment(getColumnID(plotStyleID, columnType) - 1);
    }

    DataviewDefault& DataviewDefault::setColumnFormat(const size_t columnIndex, const std::string& newFormat)
    {
        throwIfInvalidIndex("column ID", columnIndex, columnAssignments);
        columnFormats[columnIndex] = newFormat;
        return *this;
    }

    DataviewDefault& DataviewDefault::setColumnFormat(const ColumnType columnType, const std::string& newFormat)
    {
        const auto index = getColumnID(plotStyleID, columnType) - 1;
        columnFormats[index] = newFormat;
        return *this;
    }

    const std::string& DataviewDefault::getColumnFormat(const size_t columnIndex) const
    {
        throwIfInvalidIndex("column ID", columnIndex, columnAssignments);
        return columnFormats[columnIndex];
    }

    const std::string& DataviewDefault::getColumnFormat(const ColumnType columnType) const
    {
        return getColumnFormat(getColumnID(plotStyleID, columnType) - 1);
    }

    DataviewDefault& DataviewDefault::setColumnHeadline(const size_t columnIndex, const std::string& newHeadline)
    {
        throwIfInvalidIndex("column ID", columnIndex, columnAssignments);
        columnHeadlines[columnIndex] = newHeadline;
        return *this;
    }

    DataviewDefault& DataviewDefault::setColumnHeadline(const ColumnType columnType, const std::string& newHeadline)
    {
        const auto index = getColumnID(plotStyleID, columnType) - 1;
        columnHeadlines[index] = newHeadline;
        return *this;
    }

    const std::string& DataviewDefault::getColumnHeadline(const size_t columnIndex) const
    {
        throwIfInvalidIndex("column ID", columnIndex, columnAssignments);
        return columnHeadlines[columnIndex];
    }

    const std::string& DataviewDefault::getColumnHeadline(const ColumnType columnType) const
    {
        return getColumnHeadline(getColumnID(plotStyleID, columnType) - 1);
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
            writeTxtHeadlines(hFile);

            bool missingXColumn = (columnAssignments[0] == COLUMN_UNUSED);
            auto lineLength     = getConsecutiveEntriesCount(columnAssignments, predicateColumnAssignmentUnused, predicateColumnAssignmentDummy);
            // note: the case (lineLength == COLUMN_LIST_INVALID) should not be possible due to calling isComplete

            std::vector<double> lineBuffer(lineLength);

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
        // *INDENT-ON*

        bool missingXColumn = (columnAssignments[0] == COLUMN_UNUSED);
        auto lineLength     = getConsecutiveEntriesCount(columnAssignments, predicateColumnAssignmentUnused, predicateColumnAssignmentDummy);
        // note: the case (lineLength == COLUMN_LIST_INVALID) should not be possible due to calling isComplete

        std::vector<double> lineBuffer(lineLength);
        std::fstream hFile = openOrThrow(dataFilename);

        // *INDENT-OFF*
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
