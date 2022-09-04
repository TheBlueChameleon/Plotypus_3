#include "overlayscollection.h"

namespace Plotypus
{

const std::vector<Overlay *> &OverlaysCollection::getOverlays() const
{
    return overlays;
}

}
