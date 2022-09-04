#ifndef OVERLAY_H
#define OVERLAY_H

#include <fstream>

#include "../definitions/types.h"

namespace Plotypus
{
    class Overlay
    {
        protected:
            const OverlayType                   type;
            size_t                              tag;

            std::optional<OverlayPosition_t>    position;
            PositionSystem                      positionSystem = PositionSystem::Default;
            Layer                               layer          = Layer::Default;

            std::optional<std::string>          options;

            void writePosition(std::ostream& hFile) const;

        public:
            Overlay(const OverlayType type, const OverlayPosition_t& position);

            Overlay&            reset();

            OverlayType         getType() const;
            size_t              getTag() const;

            OverlayPosition_t   getPosition() const;
            Overlay&            setPosition(const OverlayPosition_t& newPosition);
            Overlay&            setPosition(const double x, const double y);
            Overlay&            setPosition(const double x, const double y, double z);
            Overlay&            clearPosition();

            PositionSystem      getPositionSystem() const;
            Overlay&            setPositionSystem(const PositionSystem newPositionSystem);

            Layer               getLayer() const;
            virtual Overlay&    setLayer(const Layer newLayer);

            std::string         getOptions() const;
            Overlay&            setOptions(const std::string& newOptions);
            Overlay&            clearOptions();

            // writers

            virtual void writeTxt   (std::ostream& hFile) const = 0;
            virtual void writeScript(std::ostream& hFile) const = 0;

            bool operator== (const Overlay&) const = default;
    };
}

#endif // OVERLAY_H
