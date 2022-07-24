#ifndef UTIL_H
#define UTIL_H

#include <algorithm>
#include <array>
#include <fstream>
#include <span>
#include <string>
#include <vector>

#include "../definitions/constants.h"

namespace Plotypus
{
    void checkFilename(const std::string& component, const std::string& stringToTest);

    template<class T>
    void checkIndex(const std::string& indexName, const size_t i, std::vector<T> vector);

    void runGnuplot(const std::string& filename, bool verbose = true);

    std::fstream openOrThrow(const std::string& filename, const std::ios_base::openmode& mode = std::ios_base::out);

    template<class T>
    bool contains(const T& toFind, const std::vector<T>& container);

    template<class T, class U>
    size_t getConsecutiveEntriesCount(const std::array<T, 6>& columns, const U& null);
    template<class T, class U>
    bool checkColumnListOccupationIsFrom(const std::array<T, 6>& columns, const std::vector<size_t>& allowedOccupations, const U& null);

    const std::string getColumnIDName(const ColumnTypes columnType);
    const std::string getPlotStyleName(const PlotStyle2D styleID);

    const std::string generateColumnFormat(const std::string& formatTemplate, size_t columnID, const Plotypus::columnAssignmentList_t &columnAssignments);
};

#include "util.txx"
#endif // UTIL_H
