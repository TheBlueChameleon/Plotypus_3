#include <iomanip>

#include "stylescollection.h"

using namespace Plotypus;
using namespace std::string_literals;

namespace Plotypus
{
    StylesCollection::StylesCollection() {}

    // ====================================================================== //

    void StylesCollection::reset()
    {
        boxStyles  .clear();
        lineStyles .clear();
        pointStyles.clear();
    }

    // ---------------------------------------------------------------------- //

    size_t StylesCollection::getBoxStyleCount() const
    {
        return boxStyles.size();
    }

    const std::vector<BoxStyle>& StylesCollection::getBoxStyles() const
    {
        return boxStyles;
    }

    BoxStyle& StylesCollection::boxStyle(const size_t i)
    {
        checkIndex("box style index", i, boxStyles);
        return boxStyles[i];
    }

    const BoxStyle& StylesCollection::getBoxStyle(const size_t i) const
    {
        checkIndex("box style index", i, boxStyles);
        return boxStyles[i];
    }

    void StylesCollection::setBoxStyles(const std::vector<BoxStyle>& newBoxstyles)
    {
        boxStyles = newBoxstyles;
    }

    BoxStyle& StylesCollection::addBoxStyle(const BoxStyle& newBoxstyle)
    {
        boxStyles.push_back(newBoxstyle);
        return boxStyles.back();
    }

    BoxStyle& StylesCollection::addBoxStyle(const std::string& fillcolor, bool border, const std::string& bordercolor)
    {
        return addBoxStyle({true, fillcolor, border, bordercolor});
    }

    // ---------------------------------------------------------------------- //

    size_t StylesCollection::getLineStyleCount() const
    {
        return lineStyles.size();
    }

    const std::vector<LineStyle>& StylesCollection::getLineStyles() const
    {
        return lineStyles;
    }

    LineStyle& StylesCollection::lineStyle(const size_t i)
    {
        checkIndex("line style index", i, lineStyles);
        return lineStyles[i];
    }

    const LineStyle& StylesCollection::getLineStyle(const size_t i) const
    {
        checkIndex("line style index", i, lineStyles);
        return lineStyles[i];
    }

    void StylesCollection::setLineStyles(const std::vector<LineStyle>& newLineStyles)
    {
        lineStyles = newLineStyles;
    }

    LineStyle& StylesCollection::addLineStyle(const LineStyle& newLineStyle)
    {
        lineStyles.push_back(newLineStyle);
        return lineStyles.back();
    }

    LineStyle& StylesCollection::addLineStyle(const std::string& color, double width, std::string dashtype, PointForm pointForm)
    {
        return addLineStyle({color, width, dashtype, pointForm});
    }

    // ---------------------------------------------------------------------- //

    size_t StylesCollection::getPointStyleCount() const
    {
        return pointStyles.size();
    }

    const std::vector<PointStyle>& StylesCollection::getPointStyles() const
    {
        return pointStyles;
    }

    PointStyle& StylesCollection::pointStyle(const size_t i)
    {
        checkIndex("point style index", i, pointStyles);
        return pointStyles[i];
    }

    const PointStyle& StylesCollection::getPointStyle(const size_t i) const
    {
        checkIndex("point style index", i, pointStyles);
        return pointStyles[i];
    }

    void StylesCollection::setPointStyles(const std::vector<PointStyle>& newPointStyles)
    {
        pointStyles = newPointStyles;
    }

    PointStyle& StylesCollection::addPointStyle(const PointStyle& newPointStyle)
    {
        pointStyles.push_back(newPointStyle);
        return pointStyles.back();
    }

    PointStyle& StylesCollection::addPointStyle(PointForm form, double size, std::string color, std::string customSymbol)
    {
        return addPointStyle(
        {
            form,
            customSymbol,
            size,
            color
        });
    }

    // ====================================================================== //

    void StylesCollection::writeStyles(std::ostream& hFile) const
    {
        writeBoxStyles (hFile);
        writeLineStyles(hFile);
    }


    void StylesCollection::writeBoxStyles(std::ostream& hFile) const
    {
        if (boxStyles.size())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# box style definition" << std::endl << std::endl;

            /* cf. gnuplot 5.4 documentation, p.206
             *
             * set style textbox {<boxstyle-index>}
             *                   {opaque|transparent} {fillcolor <color>}
             *                   {{no}border {<bordercolor>}}{linewidth <lw>}
             *                   {margins <xmargin>,<ymargin>}
             */

            for (size_t ID = 1u; const auto& style : boxStyles)
            {
                hFile << "set style textbox ";
                hFile << std::to_string(ID) + " ";
                hFile << (style.opaque                 ? "opaque "                                             : "transparent ") ;
                hFile << (style.fillcolor.size()       ? "fillcolor \""s + style.fillcolor + "\" "             : ""s);
                if (style.border)
                {
                    hFile << "border ";
                    hFile << (style.bordercolor.size() ? "bordercolor \""s + style.bordercolor + "\" "         : "");
                    hFile << (style.linewidth          ? "linewidth "s + std::to_string(style.linewidth) + " " : "");
                }
                else
                {
                    hFile << "noborder ";
                }
                hFile << style.options << std::endl;

                ++ID;
            }
            hFile << std::endl;
        }
    }

    void StylesCollection::writeLineStyles(std::ostream& hFile) const
    {
        if (lineStyles.size())
        {
            hFile << "# " << std::string(76, '-') << " #\n";
            hFile << "# line style definition" << std::endl << std::endl;

            /* cf. gnuplot 5.4 documentation, p. 203
             *
             * set style line <index> {{linetype | lt} <line_type> | <colorspec>}
             *                        {{linecolor | lc} <colorspec>}
             *                        {{linewidth | lw} <line_width>}
             *                        {{pointtype | pt} <point_type>}
             *                        {{pointsize | ps} <point_size>}
             *                        {{pointinterval | pi} <interval>}
             *                        {{pointnumber | pn} <max_symbols>}
             *                        {{dashtype | dt} <dashtype>}
             *                        {palette}
             */

            for (size_t ID = 1u; const auto& style : lineStyles)
            {
                hFile << "set style line ";
                hFile << std::to_string(ID) + " ";

                if (!style.color.empty())
                {
                    hFile << "linecolor "s << std::quoted(style.color) << " ";
                }
                hFile << "linewidth " + std::to_string(style.width) + " ";

                if (style.pointForm != PointForm::None)
                {
                    hFile << "pointtype " + std::to_string(static_cast<unsigned>(style.pointForm) ) + " ";
                    hFile << "pointsize " + std::to_string(                      style.pointsize  ) + " ";
                }

                if (!style.dashtype.empty())
                {
                    hFile << "dashtype " << std::quoted(style.dashtype) << " ";
                }

                hFile << style.options << std::endl;
                ++ID;
            }
            hFile << std::endl;
        }
    }
}

