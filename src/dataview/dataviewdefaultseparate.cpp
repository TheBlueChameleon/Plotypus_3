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
        const auto columnID = getColumnID(plotStyleID, columnType) - 1;
        throwIfInvalidIndex("column index", columnID, data);

        return data[columnID];
    }

    DataViewDefaultSeparate& DataViewDefaultSeparate::setData(ColumnType columnType, const std::span<double>& newdata)
    {
        const auto columnID = getColumnIDOrThrow(columnType) - 1; // column IDs are 1-based...

        data             [columnID] = newdata;
        columnAssignments[columnID] = columnID + 1;
        columnHeadlines  [columnID] = getColumnIDName(columnType);

        if (plotStyleID == PlotStyle::FilledCurves && columnType == ColumnType::DeltaY)
        {
            makePlusMinusFormat();
        }

        return *this;
    }

    bool DataViewDefaultSeparate::isDummy() const
    {
        auto isEmpty = [] (const std::span<double>& component)
        {
            return component.empty();
        };

        return std::ranges::all_of(data, isEmpty) && func.empty();
    }

    bool DataViewDefaultSeparate::isComplete() const
    {
        // *INDENT-OFF*
        if (isDummy())                                                          {return true;}
        if (std::ranges::all_of(data, [] (const auto& s) {return s.empty();}))  {return false;}

        constexpr auto isNullSpan = [] (const std::span<double>& span) {return span.empty();};

        return checkColumnListOccupationVsPlotType(plotStyleID, data, isNullSpan);
        // *INDENT-ON*
    }
}
