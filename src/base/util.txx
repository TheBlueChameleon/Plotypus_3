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
}

#endif // UTIL_TXX
