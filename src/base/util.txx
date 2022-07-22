#ifndef UTIL_TXX
#define UTIL_TXX

namespace Plotypus
{
    template<class T>
    void checkIndex(const std::string& indexName, const size_t i, std::vector<T> vector)
    {
        if (i >= vector.size() || (i < 0))
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

    template<class T, class U>
    bool checkColumnListComplete(const std::array<T, 6>& columns, size_t minColumnCount, size_t maxColumnCount, const U& null, bool requireColumn1)
    {
        // *INDENT-OFF*
        if (requireColumn1 && columns[0] == null) {return false;}

        for (size_t i = 1; i < minColumnCount; ++i) {
            if (columns[i] == null) {return false;}
        }

        for (size_t i = maxColumnCount; i < 6; ++i) {
            if (columns[i] != null) {return false;}
        }

        bool lastColumnDetected = false;
        for (size_t i = maxColumnCount; i > 0; --i) {
            if                       (columns[i] != null) {lastColumnDetected = true;}
            if (lastColumnDetected && columns[i] == null) {return false;}
        }
        // *INDENT-ON*

        return true;
    }



    template<class T, class U>
    size_t getConsecutiveEntriesCount(const std::array<T, 6>& columns, const U& null)
    {
        /* Returns the number of consecutively occupied colums, and checks whether columns obeys the following rules:
         * - columns[1] must always be occupied (i.e. non-null)
         * - there may be only one occupied block (i.e. any occupied column after the first null invalidates the list)
         * - exception: columns[0] may be unoccupied
         * - if columns[0] is unoccupied, only columns[1] may be occupied
         *
         * The return value
         * - is either the number of consecutive occupied columns
         * - or INVALID_COLUMN_LIST if either of the above rules is violated
         */

        bool foundNull = columns[0] == null;
        size_t result  = !foundNull;

        // *INDENT-OFF*
        if (columns[1] == null) {return INVALID_COLUMN_LIST;}
        else                    {++result;}
        // *INDENT-ON*

        for (size_t i = 2u; i < columns.size(); ++i)
        {
            // *INDENT-OFF*
            if (columns[i] == null) {foundNull = true;}
            else                    {++result;}
            // *INDENT-ON*

            if (foundNull && columns[i] != null)
            {
                result = INVALID_COLUMN_LIST;
                break;
            }
        }

        return result;
    }

    template<class T, class U>
    bool checkColumnListOccupationIsFrom(const std::array<T, 6>& columns, const std::vector<size_t>& allowedOccupations, const U& null)
    {
        auto cec = getConsecutiveEntriesCount(columns, null);
        if (cec == INVALID_COLUMN_LIST)
        {
            return false;
        }

        return contains(cec, allowedOccupations);
    }
}

#endif // UTIL_TXX
