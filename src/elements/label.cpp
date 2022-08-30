#include "label.h"

namespace Plotypus
{
    Label::Label() :
        Overlay(POSITION_ORIGIN)
    {}

    Label::Label(const std::string& text, double x, double y, bool boxed, size_t boxStyleID) :
        Overlay({x, y, std::optional<double>()}), boxed(boxed)
    {
        setBoxStyleID(boxStyleID);
    }

    Label::Label(const std::string& text, double x, double y, double z, bool boxed, size_t boxStyleID) :
        Overlay({x, y, z}), boxed(boxed)
    {
        setBoxStyleID(boxStyleID);
    }

    // ====================================================================== //

    const std::string& Label::getText() const
    {
        return text;
    }

    Label& Label::setText(const std::string& newText)
    {
        text = newText;
        return *this;
    }

    std::string Label::getFont() const
    {
        return font.value_or("");
    }

    Label& Label::setFont(const std::string& newFont)
    {
        font = newFont;
        return *this;
    }

    Label& Label::clearFont()
    {
        font.reset();
        return *this;
    }

    std::string Label::getTextcolor() const
    {
        return textcolor.value_or("");
    }

    Label& Label::setTextcolor(const std::string& newTextcolor)
    {
        textcolor = newTextcolor;
        return *this;
    }

    Label& Label::clearTextColor()
    {
        textcolor.reset();
        return *this;
    }

    HorizontalAlignment Label::getAlignment() const
    {
        return alignment.value_or(HorizontalAlignment::Left);
    }

    Label& Label::setAlignment(const HorizontalAlignment newHorizontalAlignment)
    {
        alignment = newHorizontalAlignment;
        return *this;
    }

    Label& Label::clearAlignment()
    {
        alignment.reset();
        return *this;
    }

    bool Label::getBoxed() const
    {
        return boxed;
    }

    Label& Label::setBoxed(bool newBoxed)
    {
        boxed = newBoxed;
        return *this;
    }

    size_t Label::getBoxStyleID() const
    {
        return boxStyleID.value_or(0);
    }

    Label& Label::setBoxStyleID(size_t newBoxStyleID)
    {
        // *INDENT-OFF*
        if (boxStyleID != OPTIONAL_SIZE_T_DEFAULT) {boxStyleID = newBoxStyleID;}
        else                                       {boxStyleID.reset();}
        // *INDENT-ON*

        return *this;
    }

    Label& Label::clearBoxStyleID()
    {
        boxStyleID.reset();
        return *this;
    }

    double Label::getRotateBy() const
    {
        return rotateBy.value_or(0.);
    }

    Label& Label::setRotateBy(double newRotateBy)
    {
        rotateBy = newRotateBy;
        return *this;
    }

    Label& Label::clearRotate()
    {
        rotateBy.reset();
        return *this;
    }

    // ====================================================================== //

    void Label::writeTxt(std::ostream& hFile) const
    {
        hFile << text << std::endl;
    }

    void Label::writeScript(std::ostream& hFile) const
    {
        /* cf. gnuplot 5.4 documentation, p. 164 */

        hFile << "set label " << getTag() << " ";
        hFile << std::quoted(text);

        if (position.has_value())
        {
            hFile << " ";
            writePosition(hFile);
        }

        hFile << " " << getLayerName(layer);

        if (alignment.has_value())
        {
            hFile << " " << getAlignmentName(alignment.value());
        }

        hFile << optionalNumberArgument("rotate by", rotateBy);
        hFile << optionalQuotedStringArgument("font", font);
        hFile << optionalQuotedStringArgument("textcolor", textcolor);

        if (boxed)
        {
            hFile << " boxed " << optionalSizeTArgument("bs", boxStyleID);
        }

        if (options.has_value())
        {
            hFile << " " << options.value();
        }

        hFile << std::endl;
    }
}
