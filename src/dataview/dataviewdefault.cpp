#include "../base/util.h"

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

    size_t DataViewDefault::getColumnIDOrThrow(const ColumnType columnType)
    {
        auto columnID = getColumnID(styleID, columnType);

        if (columnID == COLUMN_UNSUPPORTED)
        {
            std::string errMsg = "Column type ";
            errMsg += "\"" + getColumnIDName(columnType) + "\"";
            errMsg += " not supported for plot type ";
            errMsg += "\"" + getPlotStyleName(styleID) + "\"";

            throw UnsupportedOperationError( errMsg );
        }

        return columnID;
    }

    // ====================================================================== //

    DataViewDefault::DataViewDefault(const PlotStyle style, const std::string& label) :
        DataView(style, label)
    {}

    DataViewDefault::DataViewDefault(const std::string& style, const std::string& label) :
        DataView(style, label)
    {}

    // ====================================================================== //

    DataViewDefault& DataViewDefault::reset()
    {
        DataView::reset();

        clearFunctionMembers();
        clearNonFunctionMembers();

        lineStyle  = -1;
        pointStyle = -1;

        columnAssignments = {COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED};
        columnFormats     = {COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT};
        columnHeadlines   = {};

        return *this;
    }

    DataViewDefault& DataViewDefault::setStyleID(const PlotStyle newStyle)
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

        return *this;
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

    size_t DataViewDefault::getPointStyle() const
    {
        return pointStyle;
    }

    void DataViewDefault::setPointStyle(size_t newPointStyle)
    {
        pointStyle = newPointStyle;
    }

    size_t& DataViewDefault::columnAssignment(const size_t columnID)
    {
        throwIfInvalidIndex("column ID", columnID, columnAssignments);
        return columnAssignments[columnID];
    }

    size_t& DataViewDefault::columnAssignment(const ColumnType columnType)
    {
        return columnAssignment(getColumnID(styleID, columnType) - 1);
    }

    std::string& DataViewDefault::columnFormat(const size_t columnID)
    {
        throwIfInvalidIndex("column ID", columnID, columnAssignments);
        return columnFormats[columnID];
    }

    std::string& DataViewDefault::columnFormat(const ColumnType columnType)
    {
        return columnFormat(getColumnID(styleID, columnType) - 1);
    }

    std::string& DataViewDefault::columnHeadline(const size_t columnID)
    {
        throwIfInvalidIndex("column ID", columnID, columnAssignments);
        return columnHeadlines[columnID];
    }

    std::string& DataViewDefault::columnHeadline(const ColumnType columnType)
    {
        return columnHeadline(getColumnID(styleID, columnType) - 1);
    }

    bool DataViewDefault::isFunction() const
    {
        return !func.empty();
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
