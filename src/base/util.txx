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
    size_t getConsecutiveEntriesCount(const std::array<T, 6>& columns, const U& isNullColumn)
    {
        /* Returns the number of consecutively occupied colums, and checks whether columns obeys the following rules:
         * - columns[1] must always be occupied (i.e. non-null)
         * - there may be only one occupied block (i.e. any occupied column after the first null invalidates the list)
         * - exception: columns[0] may be unoccupied
         * - if columns[0] is unoccupied, only columns[1] may be occupied
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
            if (isNullColumn(columns[i]))   {foundNull = true;}
            else                            {++result;}

            if (foundNull && !isNullColumn(columns[i])) {return COLUMN_LIST_INVALID;}
        }

        // *INDENT-ON*

        return result;
    }

    template<class T, UnaryPredicate<T> U>
    bool checkColumnListOccupationIsFrom(const std::array<T, 6>& columns, const std::vector<size_t>& allowedOccupations, const U& isNullColumn)
    {
        auto consecutiveEntriesCount = getConsecutiveEntriesCount(columns, isNullColumn);

        // *INDENT-OFF*
        if (consecutiveEntriesCount == COLUMN_LIST_INVALID) {return false;}
        else                                                {return contains(consecutiveEntriesCount, allowedOccupations);}
        // *INDENT-ON*
    }

    template<class T, UnaryPredicate<T> U>
    bool checkColumnListOccupationVsPlotStyle(const PlotStyle styleID, const std::array<T, 6>& data, const U& isNullData)
    {
        switch (styleID)
        {
            case PlotStyle::Dots:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullData);
            case PlotStyle::Points:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3, 4, 5}, isNullData);
            case PlotStyle::XErrorBars:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullData);
            case PlotStyle::YErrorBars:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullData);
            case PlotStyle::XYErrorBars:
                return checkColumnListOccupationIsFrom(data, {4, 6}, isNullData);
            case PlotStyle::Lines:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullData);
            case PlotStyle::LinesPoints:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3, 4, 5}, isNullData);
            case PlotStyle::FilledCurves:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3}, isNullData);
            case PlotStyle::XErrorLines:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullData);
            case PlotStyle::YErrorLines:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullData);
            case PlotStyle::XYErrorLines:
                return checkColumnListOccupationIsFrom(data, {4, 6}, isNullData);
            case PlotStyle::Steps:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullData);
            case PlotStyle::FSteps:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullData);
            case PlotStyle::FillSteps:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullData);
            case PlotStyle::Impulses:
                return checkColumnListOccupationIsFrom(data, {1, 2}, isNullData);
            case PlotStyle::Boxes:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3}, isNullData);
            case PlotStyle::HBoxes:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3}, isNullData);
            case PlotStyle::BoxErrorBars:
                return checkColumnListOccupationIsFrom(data, {3, 4, 5}, isNullData);
            case PlotStyle::BoxxyError:
                return checkColumnListOccupationIsFrom(data, {4, 6}, isNullData);
            case PlotStyle::Arrows:
                return checkColumnListOccupationIsFrom(data, {4}, isNullData);
            case PlotStyle::Vectors:
                return checkColumnListOccupationIsFrom(data, {4}, isNullData);
            case PlotStyle::Image:
                return checkColumnListOccupationIsFrom(data, {3}, isNullData);

            case PlotStyle::Dots3D:
                return checkColumnListOccupationIsFrom(data, {3}, isNullData);
            case PlotStyle::Points3D:
                return checkColumnListOccupationIsFrom(data, {3, 4, 5, 6}, isNullData);
            case PlotStyle::Lines3D:
                return checkColumnListOccupationIsFrom(data, {3}, isNullData);
            case PlotStyle::LinesPoints3D:
                return checkColumnListOccupationIsFrom(data, {3, 4, 5, 6}, isNullData);
            case PlotStyle::Boxes3D:
                return checkColumnListOccupationIsFrom(data, {3, 4, 5}, isNullData);
            case PlotStyle::Impulses3D:
                return checkColumnListOccupationIsFrom(data, {3}, isNullData);
            case PlotStyle::Image3D:
                return checkColumnListOccupationIsFrom(data, {3, 4}, isNullData);
            case PlotStyle::Vectors3D:
                return checkColumnListOccupationIsFrom(data, {6}, isNullData);

            case PlotStyle::Custom:
                return checkColumnListOccupationIsFrom(data, {1, 2, 3, 4, 5, 6}, isNullData);
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
}

#endif // UTIL_TXX
