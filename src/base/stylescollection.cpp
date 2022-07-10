#include "localMacros.h"
#include "stylescollection.h"

using namespace Plotypus;

namespace Plotypus
{
    StylesCollection::StylesCollection() {}

    const std::vector<BoxStyle>& StylesCollection::getBoxStyles() const
    {
        return boxStyles;
    }

    BoxStyle& StylesCollection::getBoxStyle(int i)
    {
        CHECK_INDEX_EXT(i, boxStyles, "box style index")
        return boxStyles[i];
    }

    void StylesCollection::setBoxStyles(const std::vector<BoxStyle>& newBoxstyles)
    {
        boxStyles = newBoxstyles;
    }

    void StylesCollection::addBoxStyle(const BoxStyle& newBoxstyle)
    {
        boxStyles.push_back(newBoxstyle);
    }

    void StylesCollection::addBoxStyle(const std::string& fillcolor, bool border, const std::string& bordercolor, int ID)
    {
        addBoxStyle(
        {
            (ID < 0 ? static_cast<signed>(boxStyles.size() + 1) : ID),  // ID
            true,                                                       // opaque
            fillcolor,
            border,
            bordercolor
        });
    }

    // ---------------------------------------------------------------------- //

    const std::vector<LineStyle>& StylesCollection::getLineStyles() const
    {
        return lineStyles;
    }

    LineStyle& StylesCollection::getLineStyle(int i)
    {
        CHECK_INDEX_EXT(i, lineStyles, "box style index")
        return lineStyles[i];
    }

    void StylesCollection::setLineStyles(const std::vector<LineStyle>& newLineStyles)
    {
        lineStyles = newLineStyles;
    }

    void StylesCollection::addLineStyle(const LineStyle& newLineStyle)
    {
        lineStyles.push_back(newLineStyle);
    }

    void StylesCollection::addLineStyle(const std::string& color, double width, std::string dashtype, PointForm pointForm, int ID)
    {
        addLineStyle(
        {
            (ID < 0 ? static_cast<signed>(boxStyles.size() + 1) : ID),  // ID
            color,
            width,
            dashtype,
            pointForm
        });
    }

    // ---------------------------------------------------------------------- //

    const std::vector<PointStyle>& StylesCollection::getPointStyles() const
    {
        return pointStyles;
    }

    PointStyle& StylesCollection::getPointStyle(int i)
    {
        CHECK_INDEX_EXT(i, pointStyles, "box style index")
        return pointStyles[i];
    }

    void StylesCollection::setPointStyles(const std::vector<PointStyle>& newPointStyles)
    {
        pointStyles = newPointStyles;
    }

    int StylesCollection::addPointStyle(const PointStyle& newPointStyle)
    {
        pointStyles.push_back(newPointStyle);
        return pointStyles.size() - 1;
    }

    int StylesCollection::addPointStyle(PointForm form, double size, std::string color)
    {
        return addPointStyle(
        {
            form,
            size,
            color
        });
    }
}
