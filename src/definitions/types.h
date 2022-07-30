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

    //! @addtogroup Plotypus_Definitions
    //! @{

    template<class T, class U>
    concept UnaryPredicate = std::predicate<T, U>; // T(U) -> bool.

    // ====================================================================== //
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
    using columnFormatList_t        = std::array<std::string, 6>;

    // ---------------------------------------------------------------------- //

    using locatedTicsLabel_t = std::pair<std::string, double>;

    // ====================================================================== //
    /**
     * @brief used to compactly describe an axis of a plot
     */

    struct AxisDescriptor
    {
        AxisType                        type;

        std::optional<std::string>      labelText;
        std::optional<std::string>      labelFont;
        std::optional<std::string>      labelColor;
        std::optional<std::string>      labelOptions;
        double                          rangeMin            = 0.;
        double                          rangeMax            = AXIS_AUTO_RANGE;
        std::optional<std::string>      rangeOptions;
        bool                            tics                = true;
        double                          ticsStart           = AXIS_AUTO_RANGE;
        double                          ticsEnd             = AXIS_AUTO_RANGE;
        double                          ticsIncrement       = AXIS_AUTO_RANGE;
        std::optional<std::string>      ticsFormatstring;
        std::vector<locatedTicsLabel_t> ticsLabels;
        bool                            ticsLogscale        = false;
        std::optional<std::string>      ticsFont;
        std::optional<std::string>      ticsTextColor;
        std::optional<std::string>      ticsOptions;
        bool                            minorTics           = false;
        size_t                          minorTicsIntervals  = AXIS_AUTO_MINOR_TICS;

        AxisDescriptor();
        AxisDescriptor(const AxisType type,                           double rangeMin = AXIS_AUTO_RANGE, double rangeMax = AXIS_AUTO_RANGE);
        AxisDescriptor(const AxisType type, const std::string& label, double rangeMin = AXIS_AUTO_RANGE, double rangeMax = AXIS_AUTO_RANGE);
    };

    // ====================================================================== //

    /**
     * @brief Sheet element: Label (Text overlay)
     *
     * From this, a gnuplot command will be generated describing a textbox
     * element with the indicated properties.
     *
     * In general, empty std::string elements are ignored.
     */

    struct Label
    {
        std::string                 text        = "label";

        /**
         * @brief Where to place the text.
         *
         * The coordinates (x, y) are given relative to the coordinate system
         * specified by the plot, unless specified as relative to the screen
         * coordinate system by the bool screenCS.
         */
        std::pair<double, double>   coordinates = {0.0, 0.0};
        /**
         * @brief specifies that the coordinates parameter is relative to the
         *  screen coordinate system
         */
        bool                        screenCS    = false;

        /**
         * @brief alignment of text wrt. the indicated cooridnate
         *
         *  may be either of "left", "center", "right"
         */
        std::string                 alignment   = "left";

        /**
         * @brief specifies that the text is to be placed in a box with
         *  previously specified style
         *
         * The style of the box is specified by the member variable boxStyleID.
         */
        bool                        boxed       = true;
        /**
         * @brief The style of the box to be drawn for the text overlay.
         *
         * The box style may be specified by a previously added BoxStyle.
         * If boxStyleID == 0, the default box style is used (which may be set
         * by adding a FO_BoxStyle with ID 0).
         *
         * If bool boxed == false, the boxStyleID will be ignored.
         */
        size_t                      boxStyleID  = STYLE_ID_DEFAULT;
        /** @brief rotation of text in degrees wrt. to horizontal */

        int                         rotate      = 0;
        std::string                 font        = "";
        std::string                 textcolor   = "";

        /**
         * @brief options is appended to the gnuplot command and can hold
         *  arbitrary gnuplot options that are valid in context of set label.
         *
         * This includes the rarely used options in version 5.4 or any later
         * added features I'm not aware of yet.
         */
        std::string                 options     = "";

        bool operator== (const Label&) const = default;
    };

    //! }
}

#endif // TYPES_H
