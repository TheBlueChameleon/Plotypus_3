#ifndef OVERLAY_H
#define OVERLAY_H

#include <fstream>

#include "../definitions/types.h"

namespace Plotypus
{
    class Overlay
    {
        private:
            size_t                              tag;

            std::optional<OverlayPosition_t>    position;
            std::optional<PositionSystem>       positionSystem;

            // front/back

            std::optional<std::string>          options;

            void writePosition(std::ostream& hFile) const;

        public:
            Overlay();

            size_t              getTag() const;

            OverlayPosition_t   getPosition() const;
            Overlay&            setPosition(const OverlayPosition_t& newPosition);
            Overlay&            setPosition(const double x, const double y);
            Overlay&            setPosition(const double x, const double y, double z);
            Overlay&            clearPosition();

            PositionSystem      getPositionSystem() const;
            Overlay&            setPositionSystem(const PositionSystem newPositionSystem);
            Overlay&            clearPositionSystem();

            std::string         getOptions() const;
            Overlay&            setOptions(const std::string& newOptions);
            Overlay&            clearOptions();

            // writers

            virtual void writeTxt   (std::ostream& hFile) const = 0;
            virtual void writeScript(std::ostream& hFile) const = 0;
    };
}

#endif // OVERLAY_H
