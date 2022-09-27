#ifndef UTIL_TXX
#define UTIL_TXX

namespace Plotypus
{
    // ---------------------------------------------------------------------- //
    // general purpose

    template<class T>
    bool contains(const T& toFind, const std::vector<T>& container)
    {
        const auto last = container.end();
        const auto found = std::find(container.begin(), container.end(), toFind);
        return found != last;
    }

    // ---------------------------------------------------------------------- //
    // throw if ...

    template<std::ranges::sized_range T>
    void throwIfInvalidIndex(const std::string& indexName, const size_t i, const T& collection)
    {
        if (i >= collection.size())
        {
            throw Plotypus::InvalidIndexError("    Invalid " + indexName + ": " + std::to_string(i));
        }
    }

    // ---------------------------------------------------------------------- //
    // column assignment magic

    template<class T, UnaryPredicate<T> U>
    size_t getConsecutiveEntriesCount(const std::array<T, 6>& columns, const U& isNullColumn, const U& isIgnoredColumn)
    {
        /* Returns the number of consecutively occupied colums, and checks whether columns obeys the following rules:
         * - columns[1] must always be occupied (i.e. non-null)
         * - there may be only one occupied block (i.e. any occupied column after the first null invalidates the list)
         * - exception: columns[0] may be unoccupied
         * - if columns[0] is unoccupied, only columns[1] may be occupied
         * - a dummy type column will not be counted to enable computed quantities via the columnFormat mechanism
         *
         * The return value
         * - is either the number of consecutive occupied columns
         * - or COLUMN_LIST_INVALID if either of the above rules is violated
         */

        // *INDENT-OFF*

        bool foundNull = isNullColumn(columns[0]);
        size_t result  = !foundNull;

        if (isNullColumn(columns[1]))   {return COLUMN_LIST_INVALID;}
        else                            {++result;}

        for (size_t i = 2u; i < columns.size(); ++i)
        {
            if      (isNullColumn(columns[i]))      {foundNull = true;}
            else if (isIgnoredColumn(columns[i]))   {/* sic: do nothing */}
            else                                    {++result;}

            if (foundNull && !isNullColumn(columns[i])) {return COLUMN_LIST_INVALID;}
        }

        // *INDENT-ON*

        return result;
    }

    template<class T, UnaryPredicate<T> U>
    bool checkColumnListOccupationIsFrom(const std::array<T, 6>& columns, const std::vector<size_t>& allowedOccupations, const U& isNullColumn, const U& isIgnoredColumn)
    {
        auto consecutiveEntriesCount = getConsecutiveEntriesCount(columns, isNullColumn, isIgnoredColumn);

        // *INDENT-OFF*
        if (consecutiveEntriesCount == COLUMN_LIST_INVALID) {return false;}
        else                                                {return contains(consecutiveEntriesCount, allowedOccupations);}
        // *INDENT-ON*
    }

    template<class T, UnaryPredicate<T> U>
    bool checkColumnListOccupationVsPlotStyle(const PlotStyle styleID, const std::array<T, 6>& data, const U& isNullData, const U& isIgnoredColumn)
    {
        switch (styleID)
        {
            case PlotStyle::Dots:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullData, isIgnoredColumn);
            case PlotStyle::Points:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3, 4, 5}, isNullData, isIgnoredColumn);
            case PlotStyle::XErrorBars:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullData, isIgnoredColumn);
            case PlotStyle::YErrorBars:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullData, isIgnoredColumn);
            case PlotStyle::XYErrorBars:
                return checkColumnListOccupationIsFrom(data, {4, 6}, isNullData, isIgnoredColumn);
            case PlotStyle::Lines:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullData, isIgnoredColumn);
            case PlotStyle::LinesPoints:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3, 4, 5}, isNullData, isIgnoredColumn);
            case PlotStyle::FilledCurves:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3}, isNullData, isIgnoredColumn);
            case PlotStyle::XErrorLines:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullData, isIgnoredColumn);
            case PlotStyle::YErrorLines:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullData, isIgnoredColumn);
            case PlotStyle::XYErrorLines:
                return checkColumnListOccupationIsFrom(data, {4, 6}, isNullData, isIgnoredColumn);
            case PlotStyle::Steps:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullData, isIgnoredColumn);
            case PlotStyle::FSteps:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullData, isIgnoredColumn);
            case PlotStyle::FillSteps:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullData, isIgnoredColumn);
            case PlotStyle::Impulses:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullData, isIgnoredColumn);
            case PlotStyle::Boxes:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3}, isNullData, isIgnoredColumn);
            case PlotStyle::HBoxes:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3}, isNullData, isIgnoredColumn);
            case PlotStyle::BoxErrorBars:
                return checkColumnListOccupationIsFrom(data, {3, 4, 5}, isNullData, isIgnoredColumn);
            case PlotStyle::BoxxyError:
                return checkColumnListOccupationIsFrom(data, {4, 6}, isNullData, isIgnoredColumn);
            case PlotStyle::Arrows:
                return checkColumnListOccupationIsFrom(data, {4}, isNullData, isIgnoredColumn);
            case PlotStyle::Vectors:
                return checkColumnListOccupationIsFrom(data, {4}, isNullData, isIgnoredColumn);
            case PlotStyle::Image:
                return checkColumnListOccupationIsFrom(data, {3}, isNullData, isIgnoredColumn);

            case PlotStyle::Dots3D:
                return checkColumnListOccupationIsFrom(data, {3}, isNullData, isIgnoredColumn);
            case PlotStyle::Points3D:
                return checkColumnListOccupationIsFrom(data, {3, 4, 5, 6}, isNullData, isIgnoredColumn);
            case PlotStyle::Lines3D:
                return checkColumnListOccupationIsFrom(data, {3}, isNullData, isIgnoredColumn);
            case PlotStyle::LinesPoints3D:
                return checkColumnListOccupationIsFrom(data, {3, 4, 5, 6}, isNullData, isIgnoredColumn);
            case PlotStyle::Boxes3D:
                return checkColumnListOccupationIsFrom(data, {3, 4, 5}, isNullData, isIgnoredColumn);
            case PlotStyle::Impulses3D:
                return checkColumnListOccupationIsFrom(data, {3}, isNullData, isIgnoredColumn);
            case PlotStyle::Image3D:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullData, isIgnoredColumn);
            case PlotStyle::Vectors3D:
                return checkColumnListOccupationIsFrom(data, {6}, isNullData, isIgnoredColumn);

            case PlotStyle::Custom:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3, 4, 5, 6}, isNullData, isIgnoredColumn);
        }

        return false;
    }

    // ---------------------------------------------------------------------- //
    // optional parameters handling

    template<typename T>
    std::string optionalEnumArgument(const std::string& optionName, const std::optional<T> enumValue, const std::function<std::string (const T)> nameGetter)
    {
        // *INDENT-OFF*
        std::stringstream buffer;
        if (!enumValue.has_value()) {return "";}
        else                        {buffer << " " << optionName << " " << nameGetter( enumValue.value() );
                                     return buffer.str();}
        // *INDENT-ON*
    }

    // ---------------------------------------------------------------------- //
    // predicates

    template<typename T>
    bool predicateIsNullSpan(const std::span<T>& span)
    {
        return span.empty();
    }

    template<typename T>
    bool predicateIsNullSelector(const DataSelector_t<T>& selector)
    {
        return selector == nullptr;
    }

    template<typename T>
    bool predicateConstFalse(const T& argument)
    {
        return false;
    }
}

#endif // UTIL_TXX
