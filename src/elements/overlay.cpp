#include "overlay.h"

static size_t lastTag = 0;

namespace Plotypus
{
    void Overlay::writePosition(std::ostream& hFile) const
    {
        if (position.has_value())
        {
            const auto& posValues = position.value();
            const double x = std::get<0>(posValues);
            const double y = std::get<1>(posValues);
            const auto&  z = std::get<2>(posValues);

            hFile << getPositionSystemName(positionSystem);
            hFile << x << ", " << y;
            if (z.has_value())
            {
                hFile << ", " << z.value();
            }
        }
    }

    // ====================================================================== //

    Overlay::Overlay(const OverlayPosition_t& position) :
        position(position)
    {
        tag = ++lastTag;
    }

    Overlay& Overlay::reset()
    {
        position.reset();
        positionSystem = PositionSystem::Default;
        options.reset();

        return *this;
    }

    // ====================================================================== //

    size_t Overlay::getTag() const
    {
        return tag;
    }

    OverlayPosition_t Overlay::getPosition() const
    {
        return position.value_or(POSITION_ORIGIN);
    }

    Overlay& Overlay::setPosition(const OverlayPosition_t& newPosition)
    {
        position = newPosition;
        return *this;
    }

    Overlay& Overlay::setPosition(const double x, const double y)
    {
        position = {x, y, std::optional<double>()};
        return *this;
    }

    Overlay& Overlay::setPosition(const double x, const double y, double z)
    {
        position = {x, y, z};
        return *this;
    }

    Overlay& Overlay::clearPosition()
    {
        position.reset();
        return *this;
    }

    PositionSystem Overlay::getPositionSystem() const
    {
        return positionSystem;
    }

    Overlay& Overlay::setPositionSystem(const PositionSystem newPositionSystem)
    {
        positionSystem = newPositionSystem;
        return *this;
    }

    Layer Overlay::getLayer() const
    {
        return layer;
    }

    Overlay& Overlay::setLayer(const Layer newLayer)
    {
        layer = newLayer;
        return *this;
    }

    std::string Overlay::getOptions() const
    {
        return options.value_or("");
    }

    Overlay& Overlay::setOptions(const std::string& newOptions)
    {
        options = newOptions;
        return *this;
    }

    Overlay& Overlay::clearOptions()
    {
        options.reset();
        return *this;
    }

}
