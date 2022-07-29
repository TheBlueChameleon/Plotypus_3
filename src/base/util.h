#ifndef UTIL_H
#define UTIL_H

#include <algorithm>
#include <array>
#include <concepts>
#include <fstream>
#include <span>
#include <string>
#include <vector>
#include <ranges>

#include "../definitions/constants.h"

namespace Plotypus
{
    void checkFilename(const std::string& component, const std::string& stringToTest);

    template<std::ranges::sized_range T>
    void checkIndex(const std::string& indexName, const size_t i, T collection);

    template<class T>
    bool contains(const T& toFind, const std::vector<T>& container);

    template<class T, UnaryPredicate<T> U>
    size_t getConsecutiveEntriesCount(const std::array<T, 6>& columns, const U& isNullColumn);
    template<class T, UnaryPredicate<T> U>
    bool checkColumnListOccupationIsFrom(const std::array<T, 6>& columns, const std::vector<size_t>& allowedOccupations, const U& isNullColumn);

    std::string getTerminalName(FileType fileType);
    std::string getLengthUnitName(LengthUnits lengthUnit);
    std::string getColumnIDName(const ColumnTypes columnType);
    std::string getPlotStyleName(const PlotStyle2D plotStyleID);

    const std::string generateColumnFormat(const std::string& formatTemplate, size_t columnID, const Plotypus::columnAssignmentList_t& columnAssignments);

    std::fstream openOrThrow(const std::string& filename, const std::ios_base::openmode& mode = std::ios_base::out);
    void runGnuplot(const std::string& filename, bool verbose = true);

    std::string optionalStyleString     (const std::string& optionName, const size_t styleID);
    std::string optionalQuotedTextString(const std::string& optionName, const std::string& option);
    std::string optionalNumberString    (const std::string& optionName, const double number, bool turnOn);
    std::string optionalNumberString    (const std::string& optionName, const double number);
};

#include "util.txx"
#endif // UTIL_H
