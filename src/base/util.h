#ifndef UTIL_H
#define UTIL_H

#include <algorithm>
#include <fstream>
#include <span>
#include <string>
#include <vector>

namespace Plotypus
{
    void checkFilename(const std::string& component, const std::string& stringToTest);

    template<class T>
    void checkIndex(const std::string& indexName, const size_t i, std::vector<T> vector);

    void runGnuplot(const std::string& filename, bool verbose = true);

    std::fstream openOrThrow(const std::string& filename, const std::ios_base::openmode& mode = std::ios_base::out);

    template<class T>
    bool contains(const T& toFind, const std::span<T>& container);
};

#include "util.txx"

#endif // UTIL_H
