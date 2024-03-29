#include "dataviewdefaultseparate.h"

#include "../base/util.h"

namespace Plotypus
{
    void DataviewDefaultSeparate::clearNonFunctionMembers()
    {
        for (auto& component : data)
        {
            component = std::span<double>();
        }
    }

    void DataviewDefaultSeparate::fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const
    {
        const auto width = buffer.size();
        size_t fetchedColumns = 0u,
               columnIndex = missingXColumn;

        while (fetchedColumns < width)
        {
            if (columnAssignments[columnIndex] != COLUMN_DUMMY)
            {
                buffer[fetchedColumns] = data[columnIndex][recordID];
                ++fetchedColumns;
            }

            ++columnIndex;
        }
    }

    // ====================================================================== //

    DataviewDefaultSeparate::DataviewDefaultSeparate(const PlotStyle style) :
        DataviewDefault(DataviewType::DataViewDefaultSeparate, style)
    {}

    DataviewDefaultSeparate::DataviewDefaultSeparate(const PlotStyle style, const std::string& title) :
        DataviewDefault(DataviewType::DataViewDefaultSeparate, style, title)
    {}

    DataviewDefaultSeparate::DataviewDefaultSeparate(const std::string& style) :
        DataviewDefault(DataviewType::DataViewDefaultSeparate, style)
    {}

    DataviewDefaultSeparate::DataviewDefaultSeparate(const std::string& style, const std::string& title) :
        DataviewDefault(DataviewType::DataViewDefaultSeparate, style, title)
    {}

    // ====================================================================== //

    size_t DataviewDefaultSeparate::getArity() const
    {
        return data[1].size();          // quick solution: return arity of Y column
    }

    const columnViewList_t& DataviewDefaultSeparate::getData() const
    {
        return data;
    }

    const std::span<double>& DataviewDefaultSeparate::getData(const ColumnType columnType) const
    {
        const auto columnID = getColumnID(plotStyleID, columnType) - 1;
        throwIfInvalidIndex("column index", columnID, data);

        return data[columnID];
    }

    DataviewDefaultSeparate& DataviewDefaultSeparate::setData(const ColumnType columnType, const std::span<double>& newdata)
    {
        const auto columnID = getColumnIDOrThrow(columnType) - 1; // column IDs are 1-based...

        data             [columnID] = newdata;
        columnAssignments[columnID] = columnID + 1;
        columnHeadlines  [columnID] = getColumnTypeName(columnType);

        postSetColumnActions(columnType);

        return *this;
    }

    bool DataviewDefaultSeparate::isDummy() const
    {
        auto isEmpty = [] (const std::span<double>& component)
        {
            return component.empty();
        };

        return std::ranges::all_of(data, isEmpty) && func.empty();
    }

    bool DataviewDefaultSeparate::isComplete() const
    {
        // *INDENT-OFF*
        if (isDummy())                                                          {return true;}
        if (std::ranges::all_of(data, [] (const auto& s) {return s.empty();}))  {return false;}
        // *INDENT-ON*

        return checkColumnListOccupationVsPlotStyle(
                   plotStyleID, data,
                   predicateIsNullSpan,
                   predicateConstFalse<std::span<double>>
               );
    }
}
