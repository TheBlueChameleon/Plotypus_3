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
#include <sstream>
#include <vector>

#include "../definitions/constants.h"

namespace Plotypus
{
    // ---------------------------------------------------------------------- //
    // general purpose

    extern std::string gnuplotCommand;
    void runGnuplot(const std::string& filename, bool verbose = true);

    template<class T>
    bool contains(const T& toFind, const std::vector<T>& container);

    std::fstream openOrThrow(const std::string& filename, const std::ios_base::openmode& mode = std::ios_base::out);

    void writeCleanSheetCommands(std::ostream& hFile);

    // ---------------------------------------------------------------------- //
    // throw if ...

    void throwIfInvalidFilename(const std::string& component, const std::string& stringToTest);

    template<std::ranges::sized_range T>
    void throwIfInvalidIndex(const std::string& indexName, const size_t i, const T& collection);

    // ---------------------------------------------------------------------- //
    // column assignment magic

    template<class T, UnaryPredicate<T> U>
    size_t getConsecutiveEntriesCount(const std::array<T, 6>& columns, const U& isNullColumn, const U& isIgnoredColumn);
    template<class T, UnaryPredicate<T> U>
    bool checkColumnListOccupationIsFrom(
        const std::array<T, 6>& columns, const std::vector<size_t>& allowedOccupations,
        const U& isNullColumn, const U& isIgnoredColumn
    );
    template<class T, UnaryPredicate<T> U>
    bool checkColumnListOccupationVsPlotStyle(
        const PlotStyle styleID, const std::array<T, 6>& data,
        const U& isNullData, const U& isIgnoredColumn
    );

    const std::string generateColumnFormat(const std::string& formatTemplate, size_t columnID, const Plotypus::columnAssignmentList_t& columnAssignments);

    size_t           getColumnID      (const PlotStyle styleID, const ColumnType columnType);
    columnTypeList_t getColumnTypeList(const PlotStyle styleID, const size_t columnListLength);

    // ---------------------------------------------------------------------- //
    // enum lookups

    std::string getFileTypeName     (const FileType fileType);
    std::string getFileTypeTerminal (const FileType fileType);
    std::string getFileTypeExtension(const FileType fileType);
    std::string getLengthUnitName(const LengthUnit lengthUnit);
    std::string getColumnTypeName(const ColumnType columnType);
    std::string getSheetTypeName(const SheetType sheetType);
    std::string getDataviewTypeName(const DataviewType viewType);
    std::string getPlotStyleName(const PlotStyle plotStyleID);
    std::string getAxisName(const AxisType axis);
    std::string getPositionSystemName(const PositionSystem ps);
    std::string getLayerName(const Layer layer);
    std::string getAlignmentName(const HorizontalAlignment alignment);
    std::string getAlignmentName(const VerticalAlignment   alignment);
    std::string getAlignmentName(const Margin              alignment);
    std::string getJustificationName(const HorizontalAlignment alignment);
    std::string getStackingOrderName(const StackingOrder stackingOrder, bool variantMultiPlot = false);
    std::string getStackingDirectionName(const StackingDirection stackingDirection);
    std::string getColorSpaceName(const ColorSpace colorSpace);

    PlotStyleFamily getPlotStyleFamily(const PlotStyle plotStyle);

    bool hasAxisLabel(const AxisType axis);

    double& getMarginsElement(Plotypus::Margins_t margins, const Margin margin);

    SheetPosition_t getPaperformatSize(const PaperFormats paperformat);

    // ---------------------------------------------------------------------- //
    // optional parameters handling

    std::string optionalSizeTArgument       (const std::string& optionName, const std::optional<size_t>& styleID);
    std::string optionalStringArgument      (const std::string& optionName, const std::optional<std::string>& option);
    std::string optionalQuotedStringArgument(const std::string& optionName, const std::optional<std::string>& option);
    std::string optionalNumberArgument      (const std::string& optionName, const std::optional<double>& number);

    template<typename T>
    std::string optionalEnumArgument        (const std::string& optionName, const std::optional<T> enumValue, const std::function<std::string(const T)> nameGetter);

    std::string optionalNumberAsString      (const std::optional<double>& option, const std::string& alternative);

    void setOptionalDoubleOrClearIfNan      (std::optional<double>& option, double value);
    void setOptionalSizeTOrClearIfDefault   (std::optional<size_t>& option, size_t value);

    // ---------------------------------------------------------------------- //
    // predicates

    bool predicateColumnAssignmentUnused(const size_t assignment);
    bool predicateColumnAssignmentDummy (const size_t assignment);

    template<typename T>
    bool predicateIsNullSpan(const std::span<T>& span);
    template<typename T>
    bool predicateIsNullSelector(const DataSelector_t<T>& selector);

    template<typename T>
    bool predicateConstFalse(const T& argument);
};

#include "util.txx"
#endif // UTIL_H
