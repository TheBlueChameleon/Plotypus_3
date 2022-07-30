#ifndef UTIL_H
#define UTIL_H

#include <algorithm>
#include <array>
#include <concepts>
#include <fstream>
#include <optional>
#include <ranges>
#include <span>
#include <string>
#include <vector>

#include "../definitions/constants.h"

namespace Plotypus
{
    // ---------------------------------------------------------------------- //
    // general purpose

    template<class T>
    bool contains(const T& toFind, const std::vector<T>& container);

    std::fstream openOrThrow(const std::string& filename, const std::ios_base::openmode& mode = std::ios_base::out);
    void runGnuplot(const std::string& filename, bool verbose = true);

    // ---------------------------------------------------------------------- //
    // throw if ...

    void throwIfInvalidFilename(const std::string& component, const std::string& stringToTest);

    template<std::ranges::sized_range T>
    void throwIfInvalidIndex(const std::string& indexName, const size_t i, T collection);

    // ---------------------------------------------------------------------- //
    // column assignment magic

    template<class T, UnaryPredicate<T> U>
    size_t getConsecutiveEntriesCount(const std::array<T, 6>& columns, const U& isNullColumn);
    template<class T, UnaryPredicate<T> U>
    bool checkColumnListOccupationIsFrom(const std::array<T, 6>& columns, const std::vector<size_t>& allowedOccupations, const U& isNullColumn);

    const std::string generateColumnFormat(const std::string& formatTemplate, size_t columnID, const Plotypus::columnAssignmentList_t& columnAssignments);

    // ---------------------------------------------------------------------- //
    // enum name lookups

    std::string getTerminalName(FileType fileType);
    std::string getLengthUnitName(LengthUnit lengthUnit);
    std::string getColumnIDName(const ColumnType columnType);
    std::string getPlotStyleName(const PlotStyle2D plotStyleID);
    std::string getAxisName(const AxisType axis);

    bool hasAxisLabel(const AxisType axis);

    // ---------------------------------------------------------------------- //
    // strings from optional parameters

    std::string optionalStyleString     (const std::string& optionName, const size_t styleID);
    std::string optionalQuotedTextString(const std::string& optionName, const std::string& option);
    std::string optionalQuotedTextString(const std::string& optionName, const std::optional<std::string>& option);
    std::string optionalNumberString    (const std::string& optionName, const double number, bool turnOn);
    std::string optionalNumberString    (const std::string& optionName, const double number);
};

#include "util.txx"
#endif // UTIL_H
