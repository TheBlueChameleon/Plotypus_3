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

    DataViewDefaultSeparate::DataViewDefaultSeparate(const PlotStyle2D style, const std::string& label) :
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
        const auto columnID = getColumnID(columnType);
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
            case PlotStyle2D::Impulses:
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
            case PlotStyle2D::Image:
                return checkColumnListOccupationIsFrom(m_data, {3}, isNullSpan);
            case PlotStyle2D::Custom:
                return checkColumnListOccupationIsFrom(m_data, {1, 2, 3, 4, 5, 6}, isNullSpan);
        }

        return true;
    }

}
