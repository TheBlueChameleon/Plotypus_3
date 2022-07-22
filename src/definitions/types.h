#ifndef TYPES_H
#define TYPES_H

#include <cmath>
#include <functional>
#include <limits>
#include <string>

namespace Plotypus
{
    //! @addtogroup Plotypus_Definitions
    //! @{

    // ====================================================================== //
    /**
     * @brief used to assert filename valdity
     */

    constexpr static auto invalidFilenameChars = "*~|:;<> '\"";

    // ====================================================================== //
    /**
     * @brief specifies script output data type
     */
    enum class FileType
    {
        Pdf,
        Png,
        PostScript
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

        //! @brief a sheet with multiple plots on it
        Multiplot
    };

    // ====================================================================== //
    /**
     * @brief convenience symbol to be used with setting data ranges
     */
    constexpr double AUTO_RANGE = std::numeric_limits<double>::quiet_NaN();

    // ---------------------------------------------------------------------- //
    /**
     * @brief used to compactly describe an axis of a plot
     */
    struct AxisDescriptor
    {
        std::string label          = "";
        std::string labelOptions   = "";
        bool        tics           = true;
        //! @todo std::vector<std::pair<std::string, double>> labels;
        //! @todo std::string formatstring
        //! @todo bool logscale
        std::string ticsOptions    = "";
        double      rangeMin       = 0;
        double      rangeMax       = AUTO_RANGE;
        int         rangeStride    = 1;
        std::string rangeOptions   = "";
    };

    // ====================================================================== //
    /**
     * @brief data selector: takes an object of type T and extracts the
     *  plottable quantity of type double
     */

    template <typename T>
    using DataSelector = std::function<double (const T&)>;

    template <typename T>
    static inline double defaultDataSelector(const T& x)
    {
        return x;
    }

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

    // ---------------------------------------------------------------------- //

    using columnAssignmentList_t = std::array<size_t, 6>;
    constexpr size_t UNUSED_COLUMN          = 0u;
    constexpr size_t UNSUPPORTED_COLUMN     = std::numeric_limits<size_t>::max();
    constexpr size_t INVALID_COLUMN_LIST    = 0u;

    //! }
}

#endif // TYPES_H
