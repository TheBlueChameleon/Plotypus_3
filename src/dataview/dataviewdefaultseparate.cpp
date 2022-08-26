#include "dataviewdefaultseparate.h"

namespace Plotypus
{
    void DataViewDefaultSeparate::clearNonFunctionMembers()
    {
        for (auto& component : m_data)
        {
            component = std::span<double>();
        }
    }

    void DataViewDefaultSeparate::fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const
    {

    }

    DataViewDefaultSeparate::DataViewDefaultSeparate(const PlotStyle style, const std::string& label) :
        DataViewDefault(style, label)
    {}

    DataViewDefaultSeparate::DataViewDefaultSeparate(const std::string& style, const std::string& label) :
        DataViewDefault(style, label)
    {}

    size_t DataViewDefaultSeparate::getArity() const
    {
        return m_data[1].size();          // quick solution: return arity of Y column
    }

    std::span<double>& DataViewDefaultSeparate::data(ColumnType columnType)
    {
        const auto columnID = getColumnID(columnType) - 1;
        throwIfInvalidIndex("column index", columnID, m_data);
        return m_data[columnID];
    }

    const columnViewList_t& DataViewDefaultSeparate::getData() const
    {
        return m_data;
    }

    void DataViewDefaultSeparate::setData(const columnViewList_t& newData)
    {
        m_data = newData;
    }

    bool DataViewDefaultSeparate::isDummy() const
    {
        bool result = func.empty();
        for (const auto& component : m_data)
        {
            result &= component.empty();
        }
        return result;
    }

    bool DataViewDefaultSeparate::isComplete() const
    {
        // *INDENT-OFF*
        if (isDummy())                                                              {return true;}
        if (std::ranges::all_of(m_data, [] (const auto& s) {return s.empty();}))    {return false;}

        constexpr auto isNullSpan = [] (const std::span<double>& span) {return span.empty();};
        // *INDENT-ON*

        switch (styleID)
        {
            case PlotStyle::Dots:
                return checkColumnListOccupationIsFrom(m_data, {1, 2}, isNullSpan);
            case PlotStyle::Points:
                return checkColumnListOccupationIsFrom(m_data, {1, 2, 3, 4, 5}, isNullSpan);
            case PlotStyle::XErrorBars:
                return checkColumnListOccupationIsFrom(m_data, {3, 4}, isNullSpan);
            case PlotStyle::YErrorBars:
                return checkColumnListOccupationIsFrom(m_data, {3, 4}, isNullSpan);
            case PlotStyle::XYErrorBars:
                return checkColumnListOccupationIsFrom(m_data, {4, 6}, isNullSpan);
            case PlotStyle::Lines:
                return checkColumnListOccupationIsFrom(m_data, {1, 2}, isNullSpan);
            case PlotStyle::LinesPoints:
                return checkColumnListOccupationIsFrom(m_data, {1, 2}, isNullSpan);
            case PlotStyle::FilledCurves:
                return checkColumnListOccupationIsFrom(m_data, {1, 2, 3}, isNullSpan);
            case PlotStyle::XErrorLines:
                return checkColumnListOccupationIsFrom(m_data, {3, 4}, isNullSpan);
            case PlotStyle::YErrorLines:
                return checkColumnListOccupationIsFrom(m_data, {3, 4}, isNullSpan);
            case PlotStyle::XYErrorLines:
                return checkColumnListOccupationIsFrom(m_data, {4, 6}, isNullSpan);
            case PlotStyle::Steps:
                return checkColumnListOccupationIsFrom(m_data, {1, 2}, isNullSpan);
            case PlotStyle::FSteps:
                return checkColumnListOccupationIsFrom(m_data, {1, 2}, isNullSpan);
            case PlotStyle::FillSteps:
                return checkColumnListOccupationIsFrom(m_data, {1, 2}, isNullSpan);
            case PlotStyle::Impulses:
                return checkColumnListOccupationIsFrom(m_data, {1, 2}, isNullSpan);
            case PlotStyle::Boxes:
                return checkColumnListOccupationIsFrom(m_data, {1, 2, 3}, isNullSpan);
            case PlotStyle::HBoxes:
                return checkColumnListOccupationIsFrom(m_data, {1, 2, 3}, isNullSpan);
            case PlotStyle::BoxErrorBars:
                return checkColumnListOccupationIsFrom(m_data, {3, 4, 5}, isNullSpan);
            case PlotStyle::BoxxyError:
                return checkColumnListOccupationIsFrom(m_data, {4, 6}, isNullSpan);
            case PlotStyle::Arrows:
                return checkColumnListOccupationIsFrom(m_data, {4}, isNullSpan);
            case PlotStyle::Vectors:
                return checkColumnListOccupationIsFrom(m_data, {4}, isNullSpan);
            case PlotStyle::Image:
                return checkColumnListOccupationIsFrom(m_data, {3}, isNullSpan);
            case PlotStyle::Custom:
                return checkColumnListOccupationIsFrom(m_data, {1, 2, 3, 4, 5, 6}, isNullSpan);
        }

        return true;
    }

}
