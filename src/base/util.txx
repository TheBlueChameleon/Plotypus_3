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
    bool contains(const T& toFind, const std::span<T>& container)
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
}

#endif // UTIL_TXX
