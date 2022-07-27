#include <ranges>

#include "dataview2dseparate.h"

namespace Plotypus
{
    void DataView2DSeparate::clearNonFunctionMembers()
    {
        for (auto& component : m_data)
        {
            component = std::span<double>();
        }
    }

    void DataView2DSeparate::fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const
    {

    }

    DataView2DSeparate::DataView2DSeparate(const PlotStyle2D style, const std::string& label) :
        DataView2D(style, label)
    {}

    DataView2DSeparate::DataView2DSeparate(const std::string& style, const std::string& label) :
        DataView2D(style, label)
    {}

    size_t DataView2DSeparate::getArity() const
    {
        return m_data[1].size();          // quick solution: return arity of Y column
    }

    std::span<double>& DataView2DSeparate::data(ColumnTypes columnType)
    {
        const auto columnID = getColumnID(columnType);
        checkIndex("foo bar", columnID, m_data);
        return m_data[columnID];
    }

    const columnViewList_t& DataView2DSeparate::getData() const
    {
        return m_data;
    }

    void DataView2DSeparate::setData(const columnViewList_t& newData)
    {
        m_data = newData;
    }

    bool DataView2DSeparate::isDummy() const
    {
        bool result = func.empty();
        for (const auto& component : m_data)
        {
            result &= component.empty();
        }
        return result;
    }

    bool DataView2DSeparate::isComplete() const
    {

        // *INDENT-OFF*
        if (isDummy())                                                              {return true;}
        if (std::ranges::all_of(m_data, [] (const auto& s) {return s.empty();}))    {return false;}

        constexpr auto isNullSpan = [] (const std::span<double>& span) {return span.empty();};
        // *INDENT-ON*

        switch (styleID)
        {
            case PlotStyle2D::Dots:
                return checkColumnListOccupationIsFrom(m_data, {1, 2}, isNullSpan);
            case PlotStyle2D::Points:
                return checkColumnListOccupationIsFrom(m_data, {1, 2, 3, 4, 5}, isNullSpan);
            case PlotStyle2D::XErrorBars:
                return checkColumnListOccupationIsFrom(m_data, {3, 4}, isNullSpan);
            case PlotStyle2D::YErrorBars:
                return checkColumnListOccupationIsFrom(m_data, {3, 4}, isNullSpan);
            case PlotStyle2D::XYErrorBars:
                return checkColumnListOccupationIsFrom(m_data, {4, 6}, isNullSpan);
            case PlotStyle2D::Lines:
                return checkColumnListOccupationIsFrom(m_data, {1, 2}, isNullSpan);
            case PlotStyle2D::LinesPoints:
                return checkColumnListOccupationIsFrom(m_data, {1, 2}, isNullSpan);
            case PlotStyle2D::FilledCurves:
                return checkColumnListOccupationIsFrom(m_data, {1, 2, 3}, isNullSpan);
            case PlotStyle2D::XErrorLines:
                return checkColumnListOccupationIsFrom(m_data, {3, 4}, isNullSpan);
            case PlotStyle2D::YErrorLines:
                return checkColumnListOccupationIsFrom(m_data, {3, 4}, isNullSpan);
            case PlotStyle2D::XYErrorLines:
                return checkColumnListOccupationIsFrom(m_data, {4, 6}, isNullSpan);
            case PlotStyle2D::Steps:
                return checkColumnListOccupationIsFrom(m_data, {1, 2}, isNullSpan);
            case PlotStyle2D::FSteps:
                return checkColumnListOccupationIsFrom(m_data, {1, 2}, isNullSpan);
            case PlotStyle2D::FillSteps:
                return checkColumnListOccupationIsFrom(m_data, {1, 2}, isNullSpan);
            case PlotStyle2D::Boxes:
                return checkColumnListOccupationIsFrom(m_data, {1, 2, 3}, isNullSpan);
            case PlotStyle2D::HBoxes:
                return checkColumnListOccupationIsFrom(m_data, {1, 2, 3}, isNullSpan);
            case PlotStyle2D::BoxErrorBars:
                return checkColumnListOccupationIsFrom(m_data, {3, 4, 5}, isNullSpan);
            case PlotStyle2D::BoxxyError:
                return checkColumnListOccupationIsFrom(m_data, {4, 6}, isNullSpan);
            case PlotStyle2D::Arrows:
                return checkColumnListOccupationIsFrom(m_data, {4}, isNullSpan);
            case PlotStyle2D::Vectors:
                return checkColumnListOccupationIsFrom(m_data, {4}, isNullSpan);
            case PlotStyle2D::Custom:
                return checkColumnListOccupationIsFrom(m_data, {1, 2, 3, 4, 5, 6}, isNullSpan);
        }

        return true;
    }

}
