#include "stylescollection.h"

using namespace Plotypus;
using namespace std::string_literals;

namespace Plotypus
{
    StylesCollection::StylesCollection() {}

    // ====================================================================== //

    StylesCollection& StylesCollection::reset()
    {
        boxStyles  .clear();
        lineStyles .clear();
        pointStyles.clear();

        return *this;
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
        throwIfInvalidIndex("box style index", i, boxStyles);
        return boxStyles[i];
    }

    const BoxStyle& StylesCollection::getBoxStyle(const size_t i) const
    {
        throwIfInvalidIndex("box style index", i, boxStyles);
        return boxStyles[i];
    }

    StylesCollection& StylesCollection::setBoxStyles(const std::vector<BoxStyle>& newBoxstyles)
    {
        boxStyles = newBoxstyles;
        return *this;
    }

    BoxStyle& StylesCollection::addBoxStyle(const BoxStyle& newBoxstyle)
    {
        boxStyles.push_back(newBoxstyle);
        return boxStyles.back();
    }

    BoxStyle& StylesCollection::addBoxStyle(const std::string& fillcolor, bool border, const std::string& bordercolor)
    {
        const std::optional<std::string> fillcolorOptional = (fillcolor.empty() ? std::optional<std::string>() : fillcolor);
        return addBoxStyle({true, border, 1.0, fillcolorOptional, bordercolor});
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
        throwIfInvalidIndex("line style index", i, lineStyles);
        return lineStyles[i];
    }

    const LineStyle& StylesCollection::getLineStyle(const size_t i) const
    {
        throwIfInvalidIndex("line style index", i, lineStyles);
        return lineStyles[i];
    }

    StylesCollection& StylesCollection::setLineStyles(const std::vector<LineStyle>& newLineStyles)
    {
        lineStyles = newLineStyles;
        return *this;
    }

    LineStyle& StylesCollection::addLineStyle(const LineStyle& newLineStyle)
    {
        lineStyles.push_back(newLineStyle);
        return lineStyles.back();
    }

    LineStyle& StylesCollection::addLineStyle(const std::string& color, double width, std::string dashtype, PointForm pointForm)
    {
        LineStyle ls = LineStyle{std::optional(color), std::optional(width), std::optional(dashtype)};
        if (pointForm != PointForm::None)
        {
            ls.pointStyle->form = pointForm;
        }

        return addLineStyle(ls);
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
        throwIfInvalidIndex("point style index", i, pointStyles);
        return pointStyles[i];
    }

    const PointStyle& StylesCollection::getPointStyle(const size_t i) const
    {
        throwIfInvalidIndex("point style index", i, pointStyles);
        return pointStyles[i];
    }

    StylesCollection& StylesCollection::setPointStyles(const std::vector<PointStyle>& newPointStyles)
    {
        pointStyles = newPointStyles;
        return *this;
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

            /* cf. gnuplot 5.4 documentation, p.206 */

            for (size_t ID = 1u; const auto& style : boxStyles)
            {
                hFile << "set style textbox ";
                hFile << std::to_string(ID);
                hFile << (style.opaque ? " opaque" : " transparent") ;
                hFile << optionalQuotedStringArgument("fillcolor", style.fillcolor);

                if (style.border)
                {
                    hFile << " border";
                    hFile << optionalQuotedStringArgument("bordercolor", style.bordercolor);
                    hFile << optionalNumberArgument      ("linewidth",   style.linewidth);
                }
                else
                {
                    hFile << "noborder ";
                }

                hFile << optionalStringArgument("", style.options);
                hFile << std::endl;

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

            /* cf. gnuplot 5.4 documentation, p. 203 */

            for (size_t ID = 1u; const auto& style : lineStyles)
            {
                hFile << "set style line ";
                hFile << std::to_string(ID);

                hFile << optionalQuotedStringArgument("linecolor", style.color);
                hFile << optionalNumberArgument      ("linewidth", style.width);

                if (style.pointStyle.has_value())
                {
                    const auto& ps = style.pointStyle.value();
                    if (ps.form != PointForm::None)
                    {
                        // *INDENT-OFF*
                        if (ps.form == PointForm::Custom)   {hFile << " pointtype " << std::quoted(ps.customSymbol);}
                        else                                {hFile << " pointtype " << std::to_string(static_cast<unsigned>(ps.form));}

                        hFile << optionalNumberArgument("pointsize", ps.size);
                        // *INDENT-ON*
                    }
                }

                hFile << optionalQuotedStringArgument("dashtype", style.dashtype);
                hFile << optionalStringArgument      ("", style.options);
                hFile << std::endl;

                ++ID;
            }
            hFile << std::endl;
        }
    }

    void StylesCollection::writePointStyleCode(std::ostream& hFile, const size_t i) const
    {
        // *INDENT-OFF*
        if (i == OPTIONAL_SIZE_T_DEFAULT) {return;}
        throwIfInvalidIndex("point style index", i, pointStyles);

        const auto& psr = pointStyles[i];
        const int pointStyleInt = static_cast<int>(psr.form);

        if      (psr.form == PointForm::None)   {return;}
        else if (psr.form == PointForm::Custom) {hFile << " pointtype " << std::quoted(psr.customSymbol);}
        else                                    {hFile << " pointtype " << std::to_string(pointStyleInt);}

        hFile << optionalNumberArgument("pointsize", psr.size);
        hFile << optionalQuotedStringArgument("linecolor", psr.color);

        hFile << optionalStringArgument("", psr.options);
        // *INDENT-ON*
    }
}

