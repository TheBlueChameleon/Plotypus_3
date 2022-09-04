#ifndef OVERLAYSCOLLECTION_TXX
#define OVERLAYSCOLLECTION_TXX

namespace Plotypus
{
    template<OverlayLike T>
    T& OverlaysCollection::overlayAs(const size_t i)
    {
        return static_cast<T&>(overlay(i));
    }
}

#endif // OVERLAYSCOLLECTION_TXX
