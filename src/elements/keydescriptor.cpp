#include "keydescriptor.h"

namespace Plotypus
{
    KeyDescriptor::KeyDescriptor() {}

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

    KeyDescriptor& KeyDescriptor::setPosition(const keyPosition_t& newPosition)
    {
        position = newPosition;
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

    // ====================================================================== //
    // writer

    void KeyDescriptor::writeKeyDescriptor(std::ostream& hFile)
    {

    }
}
