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

//    std::span<double>& DataViewDefaultSeparate::data(ColumnType columnType)
//    {
//        const auto columnID = getColumnID(columnType) - 1;
//        throwIfInvalidIndex("column index", columnID, m_data);
//        return m_data[columnID];
//    }

    const columnViewList_t& DataViewDefaultSeparate::getData() const
    {
        return data;
    }

    const std::span<double>& DataViewDefaultSeparate::getData(ColumnType columnType) const
    {
        const auto columnID = getColumnID(columnType) - 1;
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
        if (isDummy())                                                              {return true;}
        if (std::ranges::all_of(data, [] (const auto& s) {return s.empty();}))    {return false;}

        constexpr auto isNullSpan = [] (const std::span<double>& span) {return span.empty();};
        // *INDENT-ON*

        switch (styleID)
        {
            case PlotStyle::Dots:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullSpan);
            case PlotStyle::Points:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3, 4, 5}, isNullSpan);
            case PlotStyle::XErrorBars:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullSpan);
            case PlotStyle::YErrorBars:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullSpan);
            case PlotStyle::XYErrorBars:
                return checkColumnListOccupationIsFrom(data, {4, 6}, isNullSpan);
            case PlotStyle::Lines:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullSpan);
            case PlotStyle::LinesPoints:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullSpan);
            case PlotStyle::FilledCurves:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3}, isNullSpan);
            case PlotStyle::XErrorLines:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullSpan);
            case PlotStyle::YErrorLines:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullSpan);
            case PlotStyle::XYErrorLines:
                return checkColumnListOccupationIsFrom(data, {4, 6}, isNullSpan);
            case PlotStyle::Steps:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullSpan);
            case PlotStyle::FSteps:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullSpan);
            case PlotStyle::FillSteps:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullSpan);
            case PlotStyle::Impulses:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullSpan);
            case PlotStyle::Boxes:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3}, isNullSpan);
            case PlotStyle::HBoxes:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3}, isNullSpan);
            case PlotStyle::BoxErrorBars:
                return checkColumnListOccupationIsFrom(data, {3, 4, 5}, isNullSpan);
            case PlotStyle::BoxxyError:
                return checkColumnListOccupationIsFrom(data, {4, 6}, isNullSpan);
            case PlotStyle::Arrows:
                return checkColumnListOccupationIsFrom(data, {4}, isNullSpan);
            case PlotStyle::Vectors:
                return checkColumnListOccupationIsFrom(data, {4}, isNullSpan);
            case PlotStyle::Image:
                return checkColumnListOccupationIsFrom(data, {3}, isNullSpan);
            case PlotStyle::Custom:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3, 4, 5, 6}, isNullSpan);
        }

        return true;
    }

}
