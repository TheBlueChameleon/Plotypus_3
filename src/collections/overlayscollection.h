#ifndef OVERLAYSCOLLECTION_H
#define OVERLAYSCOLLECTION_H

#include "../definitions/constants.h"
#include "../definitions/types.h"

namespace Plotypus
{
    class Overlay;
    class Label;

    class OverlaysCollection
    {
        protected:
            std::vector<Overlay*> overlays;

            Overlay* addOverlay(Overlay* overlay);
            static void clearOverlay(Overlay* overlay);

        public:
            OverlaysCollection() = default;
            ~OverlaysCollection();

            OverlaysCollection& reset();
            OverlaysCollection& clearOverlays();

            size_t getOverlayCount() const;

            const std::vector<Overlay*>& getOverlays() const;

            Overlay& overlay(const size_t i);
            template<OverlayLike T>
            T&       overlayAs(const size_t i);

            Label& addLabel(const Label& label);
            Label& addLabel(const std::string& text, double x, double y, bool boxed = false, size_t boxStyleID = OPTIONAL_SIZE_T_DEFAULT);
    };
}

#include "overlayscollection.txx"
#endif // OVERLAYSCOLLECTION_H
