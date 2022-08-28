#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Plotypus
{
//! @addtogroup Plotypus_Definitions
//! @{

    // ====================================================================== //
    /**
     * @brief specifies script output data type
     */
    enum class FileType
    {
        Ascii,
        Gif,
        Jpeg,
        LaTeX,
        Pdf,
        Png,
        PostScript,
        Screen,

        Custom
    };

    // ---------------------------------------------------------------------- //

    enum class LengthUnit
    {
        Inch,
        Centimeter,
    };

    enum class LineEnds
    {
        Rounded,
        Butt,
    };

    // ====================================================================== //
    /**
     * @brief internally used specifyer of data format
     */
    enum class SheetType
    {
        //! @brief an empty sheet, optionally with title. Ready to be populated with overlays
        Sheet,

        //! @brief functionality of sheet, together with capacity to render 2D/3D plots with orthogonal axes
        PlotOrthogonalAxis,

        //! @brief same, but renders pie charts and spiderplots
        PlotRadialAxes,

        //! @brief a sheet with multiple subsheets on it
        Multiplot
    };

    // ====================================================================== //
    /**
     * @brief foo bar
     */
    enum class ColumnType
    {
        Column1,
        Column2,
        Column3,
        Column4,
        Column5,
        Column6,

        X, Y, Z,
        DeltaX, DeltaY, DeltaZ,
        XLow, XHigh, YLow, YHigh,
        Pointsize, Pointtype, Color,

        Boxwidth,

        Length, Angle
    };

    // ====================================================================== //
    /**
     * @brief foo bar
     */
    enum class AxisType
    {
        X, X2,
        Y, Y2,
        Z,
        Radial, Azimuthal,
        Colourbar,
    };

    // ========================================================================== //
    /**
     * @brief Sheet border lines
     */
    enum BorderLine
    {
        Bottom = 1,
        Left = 2,
        Top = 4,
        Right = 8,
        Polar = 4096,

        BottomLeftFront = 1,
        BottomLeftBack = 2,
        BottomRightFront = 4,
        BottomRightBack = 8,
        LeftVertial = 16,
        BackVertical = 32,
        RightVertical = 64,
        FrontVertical = 128,
        TopLeftBack = 256,
        TopRightBack = 512,
        TopLeftFront = 1024,
        TopRightFront = 2048
    };

    // ========================================================================== //
    /**
     * @brief Sheet element: Plot Styles
     */
    enum class PlotStyle
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

        Impulses,
        Boxes,
        HBoxes,
        BoxErrorBars,
        BoxxyError,

        Arrows,
        Vectors,

        Image,
        // RgbImage -- cool, but requires three more ColumnTypes... see manual, p.75

        Dots3D,
        Points3D,

        Lines3D,
        LinesPoints3D,

        Impulses3D,
        Boxes3D,

        Vectors3D,
        Image3D,

        Custom
    };

    // ---------------------------------------------------------------------- //
    /**
     * @brief used internally to distinguish between mechanisms for plot command generation
     */
    enum class PlotStyleFamily
    {
        Undefined,
        Orthogonal2D,
        Orthogonal3D,
        Radial,
        Custom
    };

    // ========================================================================== //
    /**
     * @brief Sheet element: Point Style (used with plots)
     */
    enum class PointForm
    {
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
        FilledPentagon,
        None = -1,
        Custom = -2
    };

    // ========================================================================== //
    /**
     * @brief boo bar
     */

    constexpr size_t STYLE_ID_DEFAULT = std::numeric_limits<size_t>::max();

    // ====================================================================== //
    /**
     * @brief used to assert filename valdity
     * @todo apply CAPITAL_SNAKE_CASE
     */

    constexpr static auto INVALID_FILENAME_CHARS = "*~|:;<> '\"";

    // ====================================================================== //
    /**
     * @brief convenience symbol to be used with setting data ranges
     */
    constexpr double AXIS_AUTO_RANGE        = std::numeric_limits<double>::quiet_NaN();
    constexpr double AXIS_NO_AUTO_TICS      = std::numeric_limits<double>::infinity();
    constexpr size_t AXIS_AUTO_MINOR_TICS   = std::numeric_limits<size_t>::max();

    // ====================================================================== //

    constexpr size_t COLUMN_UNUSED          = 0u;
    constexpr size_t COLUMN_UNSUPPORTED     = std::numeric_limits<size_t>::max();
    constexpr size_t COLUMN_LIST_INVALID    = 0u;

    constexpr auto COLUMN_FORMAT_PLACEHOLDER_COLUMN_NUMBER = '_';
    constexpr auto COLUMN_FORMAT_ESCAPE_INTERNAL_COLUMN_ID = '!';

    constexpr auto COLUMN_FORMAT_DEFAULT         = "_";
    constexpr auto COLUMN_FORMAT_FILTER_POSITIVE = "($_ >= 0 ? $_ : 1/0)";
    constexpr auto COLUMN_FORMAT_FILTER_NEGATIVE = "($_ <= 0 ? $_ : 1/0)";

    // ====================================================================== //

    constexpr size_t BORDERS_NONE = 0u;

    constexpr size_t BORDERS_2D_DEFAULT = BorderLine::Bottom + BorderLine::Top + BorderLine::Left + BorderLine::Right;
    constexpr size_t BORDERS_2D_BOTTOM_LEFT = BorderLine::Bottom + BorderLine::Left;

    constexpr size_t BORDERS_3D_DEFAULT = BorderLine::BottomLeftBack + BorderLine::BottomLeftFront + BorderLine::BottomRightBack + BorderLine::BottomRightFront + BorderLine::LeftVertial;
    constexpr size_t BORDERS_3D_TRIPLE_FRONT = BorderLine::BottomLeftFront + BorderLine::BottomRightFront + BorderLine::LeftVertial;
    constexpr size_t BORDERS_3D_TRIPLE_BACK = BorderLine::BottomLeftBack + BorderLine::BottomRightBack + BorderLine::LeftVertial;
    constexpr size_t BORDERS_ALL = BorderLine::Polar - 1u;

    constexpr size_t BORDERS_DEFAULT = BORDERS_3D_DEFAULT;

    // ====================================================================== //
    // source: https://ayapin-film.sakura.ne.jp/Gnuplot/Docs/ps_guide.pdf

    constexpr auto SYMBOL_ALPHA                 = "{/symbol a}";
    constexpr auto SYMBOL_BETA                  = "{/symbol b}";
    constexpr auto SYMBOL_CHI                   = "{/symbol c}";
    constexpr auto SYMBOL_DELTA                 = "{/symbol d}";
    constexpr auto SYMBOL_EPSILON               = "{/symbol e}";
    constexpr auto SYMBOL_PHI                   = "{/symbol f}";
    constexpr auto SYMBOL_GAMMA                 = "{/symbol g}";
    constexpr auto SYMBOL_ETA                   = "{/symbol h}";
    constexpr auto SYMBOL_ITOA                  = "{/symbol i}";
    constexpr auto SYMBOL_VARPHI                = "{/symbol j}";
    constexpr auto SYMBOL_KAPPA                 = "{/symbol k}";
    constexpr auto SYMBOL_LAMBDA                = "{/symbol l}";
    constexpr auto SYMBOL_MU                    = "{/symbol m}";
    constexpr auto SYMBOL_NU                    = "{/symbol n}";
    constexpr auto SYMBOL_OMICRON               = "{/symbol o}";
    constexpr auto SYMBOL_PI                    = "{/symbol p}";
    constexpr auto SYMBOL_THETA                 = "{/symbol q}";
    constexpr auto SYMBOL_RHO                   = "{/symbol r}";
    constexpr auto SYMBOL_SIGMA                 = "{/symbol s}";
    constexpr auto SYMBOL_TAU                   = "{/symbol t}";
    constexpr auto SYMBOL_UPSILON               = "{/symbol u}";
    constexpr auto SYMBOL_VARPI                 = "{/symbol v}";
    constexpr auto SYMBOL_OMEGA                 = "{/symbol w}";
    constexpr auto SYMBOL_XI                    = "{/symbol x}";
    constexpr auto SYMBOL_PSI                   = "{/symbol y}";
    constexpr auto SYMBOL_ZETA                  = "{/symbol z}";

    constexpr auto SYMBOL_CAPITAL_ALPHA         = "{/symbol A}";
    constexpr auto SYMBOL_CAPITAL_BETA          = "{/symbol B}";
    constexpr auto SYMBOL_CAPITAL_CHI           = "{/symbol C}";
    constexpr auto SYMBOL_CAPITAL_DELTA         = "{/symbol D}";
    constexpr auto SYMBOL_CAPITAL_EPSILON       = "{/symbol E}";
    constexpr auto SYMBOL_CAPITAL_PHI           = "{/symbol F}";
    constexpr auto SYMBOL_CAPITAL_GAMMA         = "{/symbol G}";
    constexpr auto SYMBOL_CAPITAL_ETA           = "{/symbol H}";
    constexpr auto SYMBOL_CAPITAL_ITOA          = "{/symbol I}";
    constexpr auto SYMBOL_CAPITAL_VARPHI        = "{/symbol J}";
    constexpr auto SYMBOL_CAPITAL_KAPPA         = "{/symbol K}";
    constexpr auto SYMBOL_CAPITAL_LAMBDA        = "{/symbol L}";
    constexpr auto SYMBOL_CAPITAL_MU            = "{/symbol M}";
    constexpr auto SYMBOL_CAPITAL_NU            = "{/symbol N}";
    constexpr auto SYMBOL_CAPITAL_OMICRON       = "{/symbol O}";
    constexpr auto SYMBOL_CAPITAL_PI            = "{/symbol P}";
    constexpr auto SYMBOL_CAPITAL_THETA         = "{/symbol Q}";
    constexpr auto SYMBOL_CAPITAL_RHO           = "{/symbol R}";
    constexpr auto SYMBOL_CAPITAL_SIGMA         = "{/symbol S}";
    constexpr auto SYMBOL_CAPITAL_TAU           = "{/symbol T}";
    constexpr auto SYMBOL_CAPITAL_UPSILON       = "{/symbol U}";
    constexpr auto SYMBOL_CAPITAL_VARPI         = "{/symbol V}";
    constexpr auto SYMBOL_CAPITAL_OMEGA         = "{/symbol W}";
    constexpr auto SYMBOL_CAPITAL_XI            = "{/symbol X}";
    constexpr auto SYMBOL_CAPITAL_PSI           = "{/symbol Y}";
    constexpr auto SYMBOL_CAPITAL_ZETA          = "{/symbol Z}";

    constexpr auto SYMBOL_ALEPH                 = "{/symbol \300}";
    constexpr auto SYMBOL_REAL_PART             = "{/symbol \302}";
    constexpr auto SYMBOL_IMAGINARY_PART        = "{/symbol \301}";

    constexpr auto SYMBOL_LESS_OR_EQUAL         = "{/symbol \243}";
    constexpr auto SYMBOL_GREATER_OR_EQUAL      = "{/symbol \263}";
    constexpr auto SYMBOL_APPROXIMATELY         = "{/symbol \273}";
    constexpr auto SYMBOL_NOT_EQUAL             = "{/symbol \271}";
    constexpr auto SYMBOL_PROPORTIONAL          = "{/symbol \265}";
    constexpr auto SYMBOL_PLUSMINUS             = "{/symbol \261}";
    constexpr auto SYMBOL_SQUAREROOT            = "{/symbol \326}";
    constexpr auto SYMBOL_DOT                   = "·";
    constexpr auto SYMBOL_TIMES                 = "{/symbol \264}";
    constexpr auto SYMBOL_DIVISION              = "{/symbol \270}";
    constexpr auto SYMBOL_PARTIAL_DERIVATIVE    = "{/symbol \266}";
    constexpr auto SYMBOL_INTEGRAL              = "{/symbol \362}";
    constexpr auto SYMBOL_NABLA                 = "{/symbol \321}";
    constexpr auto SYMBOL_OTIMES                = "{/symbol \304}";
    constexpr auto SYMBOL_OPLUS                 = "{/symbol \305}";

    constexpr auto SYMBOL_ELEMENT               = "{/symbol \316}";
    constexpr auto SYMBOL_NOT_ELEMENT           = "{/symbol \317}";
    constexpr auto SYMBOL_FORALL                = "{/symbol \042}";
    constexpr auto SYMBOL_EXISTS                = "{/symbol \044}";

    constexpr auto SYMBOL_AT                    = "{\\100}";
    constexpr auto SYMBOL_FORWARD_SLASH         = "{\\057}";
    constexpr auto SYMBOL_BACKWARD_SLASH        = "{\\134}";
    constexpr auto SYMBOL_CURLY_BRACE_OPEN      = "{\\173}";
    constexpr auto SYMBOL_CURLY_BRACE_CLOSE     = "{\\175}";
    constexpr auto SYMBOL_AMPERSAND             = "{\\046}";
    constexpr auto SYMBOL_TILDE                 = "{\\176}";
    constexpr auto SYMBOL_CARET                 = "{\\136}";
    constexpr auto SYMBOL_UNDERSCORE            = "{\\137}";
    constexpr auto SYMBOL_EURO                  = "{/symbol \240}";
    constexpr auto SYMBOL_INFINITY              = "{/symbol \245}";
    constexpr auto SYMBOL_DEGREE                = "{/symbol \260}";
    constexpr auto SYMBOL_HBAR                  = "ħ";

    constexpr auto SYMBOL_CLUB                  = "{/symbol \247}";
    constexpr auto SYMBOL_SPADES                = "{/symbol \250}";
    constexpr auto SYMBOL_HEARTS                = "{/symbol \241}";
    constexpr auto SYMBOL_DIAMONDS              = "{/symbol \242}";

    constexpr auto SYMBOL_ARROW_LEFTRIGHT       = "{/symbol \253}";
    constexpr auto SYMBOL_ARROW_LEFT            = "{/symbol \254}";
    constexpr auto SYMBOL_ARROW_UP              = "{/symbol \255}";
    constexpr auto SYMBOL_ARROW_RIGHT           = "{/symbol \256}";
    constexpr auto SYMBOL_ARROW_DOWN            = "{/symbol \257}";

    constexpr auto SYMBOL_CHECKED               = "{/zapfdingbats 3}";
    constexpr auto SYMBOL_CROSSED               = "{/zapfdingbats 7}";
    constexpr auto SYMBOL_BOX                   = "{/zapfdingbats p}";
    constexpr auto SYMBOL_CHECKED_BOX           = "{/zapfdingbats @p3}";
    constexpr auto SYMBOL_CROSSED_BOX           = "{/zapfdingbats @p7}";
//! @}
}

#endif // CONSTANTS_H
