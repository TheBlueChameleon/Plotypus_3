#include "keydescriptor.h"

namespace Plotypus
{
    StackingOrder getMarginAlignmentSense(MarginAlignment alignment)
    {
        // *INDENT-OFF*
        switch (alignment)
        {
            case MarginAlignment::Left:     return StackingOrder::Horizontal;
            case MarginAlignment::Right:    return StackingOrder::Horizontal;
            case MarginAlignment::Top:      return StackingOrder::Vertical;
            case MarginAlignment::Bottom:   return StackingOrder::Vertical;
        }
        // *INDENT-ON*

        return StackingOrder::Default;
    }

    KeyDescriptor::AbstractAlignment convertToAbstractAlignment(HorizontalAlignment alignment)
    {
        // *INDENT-OFF*
        switch (alignment)
        {
            case HorizontalAlignment::Default: return KeyDescriptor::AbstractAlignment::Default;
            case HorizontalAlignment::Left:    return KeyDescriptor::AbstractAlignment::Minimal;
            case HorizontalAlignment::Center:  return KeyDescriptor::AbstractAlignment::Central;
            case HorizontalAlignment::Right:   return KeyDescriptor::AbstractAlignment::Maximal;
        }
        // *INDENT-ON*

        return KeyDescriptor::AbstractAlignment::Default;
    }

    KeyDescriptor::AbstractAlignment convertToAbstractAlignment(VerticalAlignment alignment)
    {
        // *INDENT-OFF*
        switch (alignment)
        {
            case VerticalAlignment::Default:    return KeyDescriptor::AbstractAlignment::Default;
            case VerticalAlignment::Bottom:     return KeyDescriptor::AbstractAlignment::Minimal;
            case VerticalAlignment::Center:     return KeyDescriptor::AbstractAlignment::Central;
            case VerticalAlignment::Top:        return KeyDescriptor::AbstractAlignment::Maximal;
        }
        // *INDENT-ON*

        return KeyDescriptor::AbstractAlignment::Default;
    }

    VerticalAlignment convertToVerticalAlignment(KeyDescriptor::AbstractAlignment alignment)
    {
        // *INDENT-OFF*
        switch (alignment)
        {
            case KeyDescriptor::AbstractAlignment::Default: return  VerticalAlignment::Default;
            case KeyDescriptor::AbstractAlignment::Minimal: return  VerticalAlignment::Bottom;
            case KeyDescriptor::AbstractAlignment::Central: return  VerticalAlignment::Center;
            case KeyDescriptor::AbstractAlignment::Maximal: return  VerticalAlignment::Top;
        }
        // *INDENT-ON*

        return VerticalAlignment::Default;
    }

    HorizontalAlignment convertToHorizontalAlignment(KeyDescriptor::AbstractAlignment alignment)
    {
        // *INDENT-OFF*
        switch (alignment)
        {
            case KeyDescriptor::AbstractAlignment::Default: return  HorizontalAlignment::Default;
            case KeyDescriptor::AbstractAlignment::Minimal: return  HorizontalAlignment::Left;
            case KeyDescriptor::AbstractAlignment::Central: return  HorizontalAlignment::Center;
            case KeyDescriptor::AbstractAlignment::Maximal: return  HorizontalAlignment::Right;
        }
        // *INDENT-ON*

        return HorizontalAlignment::Default;
    }

    void KeyDescriptor::writePosition(std::ostream& hFile) const
    {
        // *INDENT-OFF*
        if (!position.has_value())  {return;}
        else                        {hFile << " ";}
        // *INDENT-ON*

        std::visit(
            [&hFile](auto&& arg)
        {
            using T = std::decay_t<decltype(arg)>;
            if      constexpr (std::is_same_v<T, explicitPosition_t>)
            {
                const auto& [fixed, coordinates] = arg;
                const auto [x, y, z] = coordinates;

                // *INDENT-OFF*
                if (fixed) {hFile << " fixed";}
                hFile << " at " << x << ", " << y;
                if (z.has_value()) {hFile << ", " << z.value();}
                // *INDENT-ON*
            }
            else if constexpr (std::is_same_v<T, marginPosition_t>)
            {
                const auto [marginAlignment, abstractAlignment] = arg;

                hFile << getAlignmentName(marginAlignment);

                // *INDENT-OFF*
                if (abstractAlignment != AbstractAlignment::Default) {hFile  << " ";}
                // *INDENT-ON*

                auto marginAlignmentSense = getMarginAlignmentSense(marginAlignment);
                if (marginAlignmentSense == StackingOrder::Horizontal)
                {
                    VerticalAlignment verticalAlignment = convertToVerticalAlignment(abstractAlignment);
                    hFile << getAlignmentName(verticalAlignment);
                }
                else
                {
                    HorizontalAlignment horizontalAlignment = convertToHorizontalAlignment(abstractAlignment);
                    hFile << getAlignmentName(horizontalAlignment);
                }
            }
            else if constexpr (std::is_same_v<T, insidePosition_t>)
            {
                hFile << "inside ";

                const auto [horizontalAlignment, verticalAlignment] = arg;
                hFile << getAlignmentName(horizontalAlignment);
                if (horizontalAlignment != HorizontalAlignment::Default && verticalAlignment != VerticalAlignment::Default)
                {
                    hFile  << " ";
                }
                hFile << getAlignmentName(verticalAlignment);
            }

        }, position.value());
    }

    // ====================================================================== //

    KeyDescriptor& KeyDescriptor::reset()
    {
        on = true;
        position.reset();
        stackingOrder = StackingOrder::Default;
        justification = HorizontalAlignment::Default;
        opaque = true;
        boxed  = false;
        inverseOrder  = false;
        reverseSymbol = false;
        title.reset();
        lineStyle.reset();
        maxGroupSize.reset();

        return *this;
    }

    bool KeyDescriptor::getOn() const
    {
        return on;
    }

    KeyDescriptor& KeyDescriptor::setOn(bool newOn)
    {
        on = newOn;
        return *this;
    }

    KeyDescriptor::keyPosition_t KeyDescriptor::getPosition() const
    {
        return position.value_or(explicitPosition_t(true, POSITION_ORIGIN));
    }

    KeyDescriptor& KeyDescriptor::setPosition(const bool fixed, const OverlayPosition_t& coordinates)
    {
        position = explicitPosition_t{fixed, coordinates};
        return *this;
    }

    KeyDescriptor& KeyDescriptor::setPosition(const MarginAlignment marginAlignment)
    {
        position = marginPosition_t{marginAlignment, AbstractAlignment::Default};
        return *this;
    }

    KeyDescriptor& KeyDescriptor::setPosition(const MarginAlignment marginAlignment, const HorizontalAlignment horizontalAlignment)
    {
        auto marginAlignmentSense = getMarginAlignmentSense(marginAlignment);

        if (marginAlignmentSense != StackingOrder::Vertical)
        {
            throw InvalidArgumentError("Horizontal margin specification must be paired with vertical alignment");
        }

        position = marginPosition_t{marginAlignment, convertToAbstractAlignment(horizontalAlignment)};
        return *this;
    }

    KeyDescriptor& KeyDescriptor::setPosition(const MarginAlignment marginAlignment, const VerticalAlignment verticalAlignment)
    {
        auto marginAlignmentSense = getMarginAlignmentSense(marginAlignment);

        if (marginAlignmentSense != StackingOrder::Horizontal)
        {
            throw InvalidArgumentError("Vertical margin specification must be paired with horizontal alignment");
        }

        position = marginPosition_t{marginAlignment, convertToAbstractAlignment(verticalAlignment)};
        return *this;
    }

    KeyDescriptor& KeyDescriptor::setPosition(const HorizontalAlignment horizontalAlignment, const VerticalAlignment verticalAlignment)
    {
        position = insidePosition_t{horizontalAlignment, verticalAlignment};
        return *this;
    }

    KeyDescriptor& KeyDescriptor::clearPosition()
    {
        position.reset();
        return *this;
    }

    StackingOrder KeyDescriptor::getStackingOrder() const
    {
        return stackingOrder;
    }

    KeyDescriptor& KeyDescriptor::setStackingOrder(StackingOrder newStackingOrder)
    {
        stackingOrder = newStackingOrder;
        return *this;
    }

    HorizontalAlignment KeyDescriptor::getJustification() const
    {
        return justification;
    }

    KeyDescriptor& KeyDescriptor::setJustification(const HorizontalAlignment newJustification)
    {
        if (newJustification == HorizontalAlignment::Center)
        {
            throw UnsupportedOperationError("Cannot justify key elements centered");
        }

        justification = newJustification;
        return *this;
    }

    bool KeyDescriptor::getOpaque() const
    {
        return opaque;
    }

    KeyDescriptor& KeyDescriptor::setOpaque(bool newOpaque)
    {
        opaque = newOpaque;
        return *this;
    }

    bool KeyDescriptor::getBoxed() const
    {
        return boxed;
    }

    KeyDescriptor& KeyDescriptor::setBoxed(bool newBoxed)
    {
        boxed = newBoxed;
        return *this;
    }

    bool KeyDescriptor::getInverseOrder() const
    {
        return inverseOrder;
    }

    KeyDescriptor& KeyDescriptor::setInverseOrder(bool newInverseOrder)
    {
        inverseOrder = newInverseOrder;
        return *this;
    }

    bool KeyDescriptor::getReverseSymbol() const
    {
        return reverseSymbol;
    }

    KeyDescriptor& KeyDescriptor::setReverseSymbol(bool newReverseSymbol)
    {
        reverseSymbol = newReverseSymbol;
        return *this;
    }

    std::string KeyDescriptor::getTitle() const
    {
        return title.value_or("");
    }

    KeyDescriptor& KeyDescriptor::setTitle(const std::string& newTitle)
    {
        title = newTitle;
        return *this;
    }

    KeyDescriptor& KeyDescriptor::clearTitle()
    {
        title.reset();
        return *this;
    }

    size_t KeyDescriptor::getLineStyle() const
    {
        return lineStyle.value_or(OPTIONAL_SIZE_T_DEFAULT);
    }

    KeyDescriptor& KeyDescriptor::setLineStyle(std::optional<size_t> newLineStyle)
    {
        lineStyle = newLineStyle;
        return *this;
    }

    KeyDescriptor& KeyDescriptor::clearLineStyle()
    {
        lineStyle.reset();
        return *this;
    }

    size_t KeyDescriptor::getMaxGroupSize() const
    {
        return maxGroupSize.value_or(OPTIONAL_SIZE_T_DEFAULT);
    }

    KeyDescriptor& KeyDescriptor::setMaxGroupSize(std::optional<size_t> newMaxGroupSize)
    {
        maxGroupSize = newMaxGroupSize;
        return *this;
    }

    KeyDescriptor& KeyDescriptor::clearMaxGroupSize()
    {
        maxGroupSize.reset();
        return *this;
    }

    std::string KeyDescriptor::getOptions() const
    {
        return options.value_or("");
    }

    KeyDescriptor& KeyDescriptor::setOptions(const std::string& newOptions)
    {
        options = newOptions;
        return *this;
    }

    KeyDescriptor& KeyDescriptor::clearOptions()
    {
        options.reset();
        return *this;
    }

    // ====================================================================== //
    // writer

    void KeyDescriptor::writeKeyDescriptor(std::ostream& hFile) const
    {
        hFile << "set key";
        if (on)
        {
            hFile << " on";
            writePosition(hFile);
            // *INDENT-OFF*
            if (opaque)                                         {hFile << " opaque";}
            if (justification != HorizontalAlignment::Default)  {hFile << " " << getJustificationName(justification);}
            if (inverseOrder)                                   {hFile << " invert";}
            if (reverseSymbol)                                  {hFile << " reverse";}
            if (boxed)                                          {hFile << " box" << optionalSizeTArgument("linestyle", lineStyle);}
            // *INDENT-ON*


            switch (stackingOrder)
            {
                case StackingOrder::Default:
                    break;
                case StackingOrder::Horizontal:
                    hFile << " " << getStackingOrderName(stackingOrder);
                    hFile << optionalSizeTArgument("maxrows", maxGroupSize);
                    break;
                case StackingOrder::Vertical:
                    hFile << " " << getStackingOrderName(stackingOrder);
                    hFile << optionalSizeTArgument("maxcols", maxGroupSize);
                    break;
            }

            hFile << optionalQuotedStringArgument("title", title);
        }
        else
        {
            hFile << " off";
        }
        hFile << std::endl;
    }
}
