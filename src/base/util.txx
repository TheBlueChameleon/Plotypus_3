#ifndef UTIL_TXX
#define UTIL_TXX

namespace Plotypus
{
    template<std::ranges::sized_range T>
    void checkIndex(const std::string& indexName, const size_t i, T collection)
    {
        if (i >= collection.size() || (i < 0))
        {
            throw Plotypus::InvalidIndexError("    Invalid " + indexName + ": " + std::to_string(i));
        }
    }

    template<class T>
    bool contains(const T& toFind, const std::vector<T>& container)
    {
        const auto last = container.end();
        const auto found = std::find(container.begin(), container.end(), toFind);
        return found != last;
    }

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

    //template<class T, class U>
    template<class T, UnaryPredicate<T> U>
    bool checkColumnListOccupationIsFrom(const std::array<T, 6>& columns, const std::vector<size_t>& allowedOccupations, const U& isNullColumn)
    {
        auto consecutiveEntriesCount = getConsecutiveEntriesCount(columns, isNullColumn);

        // *INDENT-OFF*
        if (consecutiveEntriesCount == COLUMN_LIST_INVALID) {return false;}
        else                                                {return contains(consecutiveEntriesCount, allowedOccupations);}
        // *INDENT-ON*
    }
}

#endif // UTIL_TXX
