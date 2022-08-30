#ifndef TYPES_H
#define TYPES_H

#include <cmath>
#include <functional>
#include <limits>
#include <optional>
#include <span>
#include <string>

#include "constants.h"

namespace Plotypus
{
    //! {

    // ====================================================================== //
    // concepts

    /**
     * @brief foo bar
     */
    class Sheet;
    template <typename T>
    concept SheetLike = std::is_base_of<Sheet, T>::value;

    /**
     * @brief foo bar
     */
    class DataView;
    template <typename T>
    concept DataViewLike = std::is_base_of<DataView, T>::value;

    /**
     * @brief foo bar
     */
    class Overlay;
    template <typename T>
    concept OverlayLike = std::is_base_of<Overlay, T>::value;

    //! @addtogroup Plotypus_Definitions
    //! @{

    template<class T, class U>
    concept UnaryPredicate = std::predicate<T, U>; // T(U) -> bool.

    // ====================================================================== //
    // selectors and column mechanics

    /**
     * @brief data selector: takes an object of type T and extracts the
     *  plottable quantity of type double
     */

    template <typename T>
    using DataSelector_t = std::function<double (const T&)>;

    // ---------------------------------------------------------------------- //

    template <typename T>
    using columnSelectorList_t      = std::array<DataSelector_t<T>, 6>;
    using columnViewList_t          = std::array<std::span<double>, 6>;
    using columnAssignmentList_t    = std::array<size_t, 6>;
    using columnTypeList_t          = std::array<ColumnType, 6>;
    using columnFormatList_t        = std::array<std::string, 6>;

    // ====================================================================== //
    // overlays

    using OverlayPosition_t = std::tuple<double, double, std::optional<double>>;
    constexpr OverlayPosition_t POSITION_ORIGIN = {0, 0, std::optional<double>()};

    // ====================================================================== //

    //! }
}

#endif // TYPES_H
