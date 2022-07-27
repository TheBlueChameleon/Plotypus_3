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
        Pdf,
        Png,
        PostScript,
        Gif
    };

    // ====================================================================== //
    /**
     * @brief internally used specifyer of data format
     */
    enum class PlotType
    {
        //! @brief an empty sheet, optionally with title. Ready to be populated with overlays
        Sheet,

        //! @brief functionality of sheet, together with frame formatting and capacity to accept 2D data sequences
        Plot2D,
        //! @brief same, but accepts 3D data sequences
        Plot3D,
        //! @brief same, but renders the z data as coloured pixels
        PlotColormap,

        //! @brief a sheet with multiple subsheets on it
        FramesCollection
    };

    // ====================================================================== //
    /**
     * @brief foo bar
     */
    enum class ColumnTypes
    {
        Column1,
        Column2,
        Column3,
        Column4,
        Column5,
        Column6,

        X, Y, Y2, Z,
        DeltaX, DeltaY, DeltaZ,
        XLow, XHigh, YLow, YHigh,
        Pointsize, Pointtype, Color,

        Boxwidth,

        Length, Angle
    };

    // ========================================================================== //
    /**
     * @brief Sheet border lines
     */
    enum BorderLines
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

    constexpr static auto invalidFilenameChars = "*~|:;<> '\"";

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

    constexpr size_t BORDERS_2D_DEFAULT = BorderLines::Bottom + BorderLines::Top + BorderLines::Left + BorderLines::Right;
    constexpr size_t BORDERS_2D_BOTTOM_LEFT = BorderLines::Bottom + BorderLines::Left;

    constexpr size_t BORDERS_3D_DEFAULT = BorderLines::BottomLeftBack + BorderLines::BottomLeftFront + BorderLines::BottomRightBack + BorderLines::BottomRightFront + BorderLines::LeftVertial;
    constexpr size_t BORDERS_3D_TRIPLE_FRONT = BorderLines::BottomLeftFront + BorderLines::BottomRightFront + BorderLines::LeftVertial;
    constexpr size_t BORDERS_3D_TRIPLE_BACK = BorderLines::BottomLeftBack + BorderLines::BottomRightBack + BorderLines::LeftVertial;

    constexpr size_t BORDERS_DEFAULT = BORDERS_3D_DEFAULT;

//! @}
}

#endif // CONSTANTS_H
