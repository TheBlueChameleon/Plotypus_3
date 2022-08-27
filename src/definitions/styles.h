#ifndef STYLES_H
#define STYLES_H

#include <string>
#include <utility>

#include "constants.h"

namespace Plotypus
{
    //! @addtogroup Plotypus_Definitions
    //! @{

    struct PointStyle
    {
        PointForm   form = PointForm::Point;
        std::string customSymbol = "\\U+2299";
        double      size = 1.0;
        std::string color = "";

        bool operator== (const PointStyle&) const = default;

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
        PointStyle  pointStyle;
        std::string options     = "";

        bool operator== (const LineStyle&) const = default;
    };

    // ========================================================================== //
    /**
     * @todo set style arrow support - p. 199 -- expands LineStyle?
     */
    struct ArrowStyle {};

    // ====================================================================== //
    /**
     * @brief Sheet element: BoxStyle (used with Text overlays)
     *
     * Cf. page 201 gnuplot 5.4 documentation (section set style textbox)
     */
    struct BoxStyle
    {
        bool        opaque      = true;
        bool        border      = true;
        double      linewidth   = 0.0;
        std::string fillcolor   = "";
        std::string bordercolor = "";
        std::string options     = "";

        bool operator== (const BoxStyle&) const = default;
    };

    //! }
}

#endif // STYLES_H
