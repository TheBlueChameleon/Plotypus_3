#include "overlay.h"

static size_t lastTag = 0;

namespace Plotypus
{
    void Overlay::writePosition(std::ostream& hFile) const
    {
        if (position.has_value())
        {
            const std::string systemPrefix = positionSystem.has_value() ?
                                             getPositionSystemName(positionSystem.value()) + " " :
                                             "";

            const auto& posValues = position.value();
            const double x = std::get<0>(posValues);
            const double y = std::get<1>(posValues);
            const auto&  z = std::get<2>(posValues);

            hFile << systemPrefix << x << ", ";
            hFile << systemPrefix << y;
            if (z.has_value())
            {
                hFile << ", ";
                hFile << systemPrefix << z.value() << " ";
            }
        }
    }

    // ====================================================================== //

    Overlay::Overlay()
    {
        tag = ++lastTag;
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
        if (position.has_value())
        {
            auto& posRef = position.value();
            std::get<0>(posRef) = x;
            std::get<1>(posRef) = y;
        }
        else
        {
            position = {x, y, std::optional<double>()};
        }
        return *this;
    }

    Overlay& Overlay::setPosition(const double x, const double y, double z)
    {
        if (position.has_value())
        {
            auto& posRef = position.value();
            std::get<0>(posRef) = x;
            std::get<1>(posRef) = y;
            std::get<2>(posRef) = z;
        }
        else
        {
            position = {x, y, z};
        }

        return *this;
    }

    Overlay& Overlay::clearPosition()
    {
        position.reset();
        return *this;
    }

    PositionSystem Overlay::getPositionSystem() const
    {
        return positionSystem.value_or(PositionSystem::First);
    }

    Overlay& Overlay::setPositionSystem(const PositionSystem newPositionSystem)
    {
        positionSystem = newPositionSystem;
        return *this;
    }

    Overlay& Overlay::clearPositionSystem()
    {
        positionSystem.reset();
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
