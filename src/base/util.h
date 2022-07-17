#ifndef UTIL_H
#define UTIL_H

#include <algorithm>
#include <array>
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

    template<class T, class U>
    bool checkColumnList(const std::array<T, 6>& columns, size_t minColumnCount, size_t maxColumnCount, const U& null, bool requireColumn1 = false);

    const std::string getColumnIDName(const ColumnTypes columnType);
    const std::string getPlotStyleName(const PlotStyle2D styleID);
};

#include "util.txx"
#endif // UTIL_H
