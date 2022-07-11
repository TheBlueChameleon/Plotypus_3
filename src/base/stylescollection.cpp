#include "localMacros.h"
#include "stylescollection.h"

using namespace Plotypus;

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

    const std::vector<BoxStyle>& StylesCollection::getBoxStyles() const
    {
        return boxStyles;
    }

    BoxStyle& StylesCollection::getBoxStyle(const size_t i)
    {
        CHECK_INDEX(i, boxStyles, "box style index");
        return boxStyles[i];
    }

    void StylesCollection::setBoxStyles(const std::vector<BoxStyle>& newBoxstyles)
    {
        boxStyles = newBoxstyles;
    }

    size_t StylesCollection::addBoxStyle(const BoxStyle& newBoxstyle)
    {
        boxStyles.push_back(newBoxstyle);
        return boxStyles.size();
    }

    size_t StylesCollection::addBoxStyle(const std::string& fillcolor, bool border, const std::string& bordercolor)
    {
        return addBoxStyle({true, fillcolor, border, bordercolor});
    }

    // ---------------------------------------------------------------------- //

    const std::vector<LineStyle>& StylesCollection::getLineStyles() const
    {
        return lineStyles;
    }

    LineStyle& StylesCollection::getLineStyle(const size_t i)
    {
        CHECK_INDEX(i, lineStyles, "box style index");
        return lineStyles[i];
    }

    void StylesCollection::setLineStyles(const std::vector<LineStyle>& newLineStyles)
    {
        lineStyles = newLineStyles;
    }

    size_t StylesCollection::addLineStyle(const LineStyle& newLineStyle)
    {
        lineStyles.push_back(newLineStyle);
        return lineStyles.size();
    }

    size_t StylesCollection::addLineStyle(const std::string& color, double width, std::string dashtype, PointForm pointForm)
    {
        return addLineStyle({color, width, dashtype, pointForm});
    }

    // ---------------------------------------------------------------------- //

    const std::vector<PointStyle>& StylesCollection::getPointStyles() const
    {
        return pointStyles;
    }

    PointStyle& StylesCollection::getPointStyle(const size_t i)
    {
        CHECK_INDEX(i, pointStyles, "box style index");
        return pointStyles[i];
    }

    void StylesCollection::setPointStyles(const std::vector<PointStyle>& newPointStyles)
    {
        pointStyles = newPointStyles;
    }

    size_t StylesCollection::addPointStyle(const PointStyle& newPointStyle)
    {
        pointStyles.push_back(newPointStyle);
        return pointStyles.size();
    }

    size_t StylesCollection::addPointStyle(PointForm form, double size, std::string color)
    {
        return addPointStyle(
        {
            form,
            size,
            color
        });
    }

    // ====================================================================== //


    void StylesCollection::writeBoxStyles(std::ofstream& hFile) const
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

    void StylesCollection::writeLineStyles(std::ofstream& hFile) const
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

