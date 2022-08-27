#include "dataviewdefaultseparate.h"

namespace Plotypus
{
    void DataViewDefaultSeparate::clearNonFunctionMembers()
    {
        for (auto& component : data)
        {
            component = std::span<double>();
        }
    }

    void DataViewDefaultSeparate::fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const
    {
        const auto width = buffer.size();
        for (int columnIndex = missingXColumn; columnIndex < width; ++columnIndex)
        {
            buffer[columnIndex] = data[columnIndex][recordID];
        }
    }

    DataViewDefaultSeparate::DataViewDefaultSeparate(const PlotStyle style, const std::string& label) :
        DataViewDefault(style, label)
    {}

    DataViewDefaultSeparate::DataViewDefaultSeparate(const std::string& style, const std::string& label) :
        DataViewDefault(style, label)
    {}

    size_t DataViewDefaultSeparate::getArity() const
    {
        return data[1].size();          // quick solution: return arity of Y column
    }

    const columnViewList_t& DataViewDefaultSeparate::getData() const
    {
        return data;
    }

    const std::span<double>& DataViewDefaultSeparate::getData(ColumnType columnType) const
    {
        const auto columnID = getColumnID(styleID, columnType) - 1;
        throwIfInvalidIndex("column index", columnID, data);

        return data[columnID];
    }

    void DataViewDefaultSeparate::setData(ColumnType columnType, const std::span<double>& newdata)
    {
        const auto columnID = getColumnIDOrThrow(columnType) - 1; // column IDs are 1-based...

        data             [columnID] = newdata;
        columnAssignments[columnID] = columnID + 1;
        columnHeadlines  [columnID] = getColumnIDName(columnType);
    }

    bool DataViewDefaultSeparate::isDummy() const
    {
        bool result = func.empty();
        for (const auto& component : data)
        {
            result &= component.empty();
        }
        return result;
    }

    bool DataViewDefaultSeparate::isComplete() const
    {
        // *INDENT-OFF*
        if (isDummy())                                                          {return true;}
        if (std::ranges::all_of(data, [] (const auto& s) {return s.empty();}))  {return false;}

        constexpr auto isNullSpan = [] (const std::span<double>& span) {return span.empty();};

        return checkColumnListOccupationVsPlotType(styleID, data, isNullSpan);
        // *INDENT-ON*
    }
}
