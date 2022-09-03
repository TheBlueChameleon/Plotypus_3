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
    void throwIfInvalidIndex(const std::string& indexName, const size_t i, const T& collection);

    // ---------------------------------------------------------------------- //
    // column assignment magic

    template<class T, UnaryPredicate<T> U>
    size_t getConsecutiveEntriesCount(const std::array<T, 6>& columns, const U& isNullColumn);
    template<class T, UnaryPredicate<T> U>
    bool checkColumnListOccupationIsFrom(const std::array<T, 6>& columns, const std::vector<size_t>& allowedOccupations, const U& isNullColumn);
    template<class T, UnaryPredicate<T> U>
    bool checkColumnListOccupationVsPlotType(const PlotStyle styleID, const std::array<T, 6>& data, const U& isNullData);

    const std::string generateColumnFormat(const std::string& formatTemplate, size_t columnID, const Plotypus::columnAssignmentList_t& columnAssignments);

    size_t           getColumnID      (const PlotStyle styleID, const ColumnType columnType);
    columnTypeList_t getColumnTypeList(const PlotStyle styleID, const size_t columnListLength);

    // ---------------------------------------------------------------------- //
    // enum lookups

    std::string getTerminalName(const FileType fileType);
    std::string getLengthUnitName(const LengthUnit lengthUnit);
    std::string getColumnIDName(const ColumnType columnType);
    std::string getSheetTypeName(const SheetType sheetType);
    std::string getDataViewTypeName(const DataViewType viewType);
    std::string getPlotStyleName(const PlotStyle plotStyleID);
    std::string getAxisName(const AxisType axis);
    std::string getPositionSystemName(const PositionSystem ps);
    std::string getLayerName(const Layer layer);
    std::string getAlignmentName(const HorizontalAlignment alignment);
    std::string getAlignmentName(const VerticalAlignment alignment);
    std::string getAlignmentName(const MarginAlignment alignment);
    std::string getJustificationName(const HorizontalAlignment alignment);
    std::string getStackingOrderName(const StackingOrder stackingOrder);

    PlotStyleFamily getPlotStyleFamily(const PlotStyle plotStyleID);

    bool hasAxisLabel(const AxisType axis);

    // ---------------------------------------------------------------------- //
    // optional parameters handling

    std::string optionalSizeTArgument       (const std::string& optionName, const std::optional<size_t>& styleID);
    std::string optionalStringArgument      (const std::string& optionName, const std::optional<std::string>& option);
    std::string optionalQuotedStringArgument(const std::string& optionName, const std::optional<std::string>& option);
    std::string optionalNumberArgument      (const std::string& optionName, const std::optional<double>& number);

    std::string optionalNumberAsString      (const std::optional<double>& option, const std::string& alternative);

    void setOptionalDoubleOrClearIfNan      (std::optional<double>& option, double value);
    void setOptionalSizeTOrClearIfDefault   (std::optional<size_t>& option, size_t value);
};

#include "util.txx"
#endif // UTIL_H
