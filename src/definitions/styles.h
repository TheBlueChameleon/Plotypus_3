#ifndef STYLES_H
#define STYLES_H

#include <string>
#include <utility>

namespace Plotypus
{
//! @addtogroup Platypus_Definitions
//! @{

    // ========================================================================== //
    /**
     * @brief Sheet element: Point Style (used with plots)
     */
    enum class PointStyle
    {
        None = -1,
        Point,
        Plus,
        Cross,
        Asterisk,
        Box,
        FilledBox,
        Circle,
        FilledCircle,
        TriangleUp,
        FilledTriangleUp,
        TriangleDown,
        FilledTriangleDown,
        Diamond,
        FilledDiamond,
        Pentagon,
        FilledPentagon
    };

    // ========================================================================== //
    /**
     * @brief Sheet element: Line Style (used with plots)
     *
     * cf. gnuplot 5.4 documentation, p. 198
     * Used with class Platypus::Plot2D
     */
    struct LineStyle
    {
        std::string  color     = "";
        double       width     = 0;
        PointStyle   point     = PointStyle::Point;
        double       pointsize = 0;
        std::string  options   = "";

        /*
         */
    };

    // ====================================================================== //
    /**
     * @brief Sheet element: BoxStyle (used with Text overlays)
     *
     * Cf. page 201 gnuplot 5.4 documentation (section set style textbox)
     *
     * @todo add negative ID: auto register as custom
     */
    struct BoxStyle
    {
        /**
         * @brief ID is a constant that can be used for later reference in a
         *  custom code element.
         *
         * If zero, it will be ignored. May not be negative.
         * (gnuplot doesn't allow that).
         *
         * ID can be referenced by the Label member boxStyle. If zero, this will
         * be ommitted and (re)defines the standard box style.
         */
        int         ID          = 0;
        bool        opaque      = true;
        std::string fillcolor   = "";
        bool        border      = true;
        std::string bordercolor = "";
        int         linewidth   = 0;
        std::string options     = "";
    };

    // ====================================================================== //
    /**
     * @brief Sheet element: Label (Text overlay)
     *
     * From this, a gnuplot command will be generated describing a textbox element
     * with the indicated properties.
     *
     *
     *
     * in general, empty std::string elements are ignored.
     *
     * options is appended to the gnuplot command and can hold arbitrary gnuplot
     * options that are valid in context of set label. This includes the rarely
     * used options in version 5.4 or any later added features I'm not aware of
     * yet.
     * You may also abuse this to include a \n and any code to be executed before
     * the custom gnuplot code is run.
     */

    struct Label
    {
        /**
         * @brief ID is a constant that can be used for later reference in a
         *  custom code element.
         *
         *  If zero, it will be ignored. May not be negative.
         *  (gnuplot doesn't allow that.)
         */
        int                         ID          = 0;

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
        int                         boxStyleID  = 0;
        /** @brief rotation of text in degrees wrt. to horizontal */

        int                         rotate      = 0;
        std::string                 font        = "";
        std::string                 textcolor   = "";
        std::string                 options     = "";
    };

//! @}
}

#endif // STYLES_H
