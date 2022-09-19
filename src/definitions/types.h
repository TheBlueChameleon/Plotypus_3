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
    class Dataview;
    template <typename T>
    concept DataViewLike = std::is_base_of<Dataview, T>::value;

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
    // Overlays

    using OverlayPosition_t = std::tuple<double, double, std::optional<double>>;
    constexpr OverlayPosition_t POSITION_ORIGIN = {0, 0, std::optional<double>()};

    // ====================================================================== //
    // Sheets

    using SheetPosition_t = std::pair<double, double>;
    constexpr SheetPosition_t DEFAULT_SHEET_POSITION = {-1., -1.};

    // ====================================================================== //
    // Multiplots

    using GridPosition_t = std::pair<size_t, size_t>;
    constexpr GridPosition_t DEFAULT_GRID_POSITION = {0, 0};

    //! @todo use this also for set margin command
    using Margins_t = std::array<double, 4>;                       // use MarginAlignment as indices
    constexpr Margins_t DEFAULT_MARGIN_SIZE = {0., 0., 0., 0.};

    using MultiplotSpacing_t = std::pair<double, std::optional<double>>;
    constexpr MultiplotSpacing_t DEFAULT_MULTIPLOT_SPACING = {0., std::optional<double>()};

    struct MultiplotLayout_t
    {
        GridPosition_t                      gridDimensions;
        StackingOrder                       stackingOrder;                  // rowsfirst ~> Vertical; columnsfirst ~> Horizontal
        StackingDirection                   stackingDirection;
        std::optional<Margins_t>            margins;
        std::optional<MultiplotSpacing_t>   spacing;
    };

    constexpr MultiplotLayout_t DEFAULT_MULTIPLOT_LAYOUT{DEFAULT_GRID_POSITION};

    //! }
}

#endif // TYPES_H
