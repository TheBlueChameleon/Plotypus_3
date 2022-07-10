#ifndef TYPES_H
#define TYPES_H

#include <cmath>
#include <functional>
#include <string>

namespace Plotypus
{
//! @addtogroup Platypus_Definitions
//! @{

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
     * @brief used to compactly describe an axis of a plot
     */
    struct AxisDescriptor
    {
        std::string label          = "";
        std::string labelOptions   = "";
        bool        tics           = true;
        std::string ticsOptions    = "";
        double      rangeMin       = 0;
        double      rangeMax       = std::nan("inf");
        int         rangeStride    = 1;
        std::string rangeOptions   = "";
    };

    // ====================================================================== //
    /**
     * @brief data selector: takes an object of type T and extracts the
     *  plottable quantity of type double
     */

    template <typename T>
    using DataSelector = std::function<double (const T)>;

    template <typename T>
    static inline double defaultDataSelector(const T x)
    {
        return x;
    }

//! @}
}

#endif // TYPES_H
