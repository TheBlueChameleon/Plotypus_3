#include "overlayscollection.h"

#include "../base/util.h"
#include "../elements/label.h"

namespace Plotypus
{
    Overlay* OverlaysCollection::addOverlay(Overlay* overlay)
    {
        overlays.push_back(overlay);
        return overlays.back();
    }

    // ====================================================================== //

    OverlaysCollection::~OverlaysCollection()
    {
        clearOverlays();
    }

    // ====================================================================== //

    OverlaysCollection& OverlaysCollection::reset()
    {
        return clearOverlays();
    }

    OverlaysCollection& OverlaysCollection::clearOverlays()
    {
        for (auto overlay : overlays)
        {
            delete overlay;
        }
        overlays.clear();

        return *this;
    }

    size_t OverlaysCollection::getOverlayCount() const
    {
        return overlays.size();
    }

    const std::vector<Overlay*>& OverlaysCollection::getOverlays() const
    {
        return overlays;
    }

    Overlay& OverlaysCollection::overlay(const size_t i)
    {
        throwIfInvalidIndex("overlay index", i, overlays);
        return *overlays[i];
    }

    Label& OverlaysCollection::addLabel(const Label& label)
    {
        return *reinterpret_cast<Label*>(addOverlay( new Label(label) ));
    }

    Label& OverlaysCollection::addLabel(const std::string& text, double x, double y, bool boxed, size_t boxStyleID)
    {
        return *reinterpret_cast<Label*>(addOverlay( new Label(text, x, y, boxed, boxStyleID) ));
    }
}
