#ifndef STYLES_H
#define STYLES_H

#include <string>
#include <utility>

namespace Plotypus
{
    //! @addtogroup Plotypus_Definitions
    //! @{

    // ========================================================================== //
    /**
     * @brief Sheet element: Plot Style for 2D plots
     */
    enum class PlotStyle2D
    {
        Dots,
        Points,
        XErrorBars,
        YErrorBars,
        XYErrorBars,

        Lines,
        LinesPoints,
        FilledCurves,
        XErrorLines,
        YErrorLines,
        XYErrorLines,

        Steps,
        FSteps,
        FillSteps,

        Boxes,
        HBoxes,
        BoxErrorBars,
        BoxxyError,

        Arrows,
        Vectors,

        Custom
    };


    // ========================================================================== //
    /**
     * @brief Sheet element: Plot Style for 3D plots
     */

    enum class PlotStyle3D
    {
        Lines,
        Surface,
        Image,
        Arrows,
        Vectors
    };

    // ========================================================================== //
    /**
     * @brief Sheet element: Point Style (used with plots)
     */
    enum class PointForm
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

    struct PointStyle
    {
        PointForm   form = PointForm::Point;
        double      size = 1.0;
        std::string color = "";

    };

    // ========================================================================== //
    /**
     * @brief Sheet element: Line Style (used with plots)
     *
     * cf. gnuplot 5.4 documentation, p. 203
     * Note: there, line*types* are used, which differ from line styles in permanence
     * of the definition
     */
    struct LineStyle
    {
        std::string color       = "";
        double      width       = 0.0;
        std::string dashtype    = "";
        PointForm   pointForm   = PointForm::Point;
        double      pointsize   = 1.;
        std::string options     = "";

        bool operator== (const LineStyle&) const = default;
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
        bool        opaque      = true;
        std::string fillcolor   = "";
        bool        border      = true;
        std::string bordercolor = "";
        double      linewidth   = 0.0;
        std::string options     = "";

        bool operator== (const BoxStyle&) const = default;
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

#endif // STYLES_H
