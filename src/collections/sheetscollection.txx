#ifndef SHEETSCOLLOECTION_TXX
#define SHEETSCOLLOECTION_TXX

namespace Plotypus
{
    template<SheetLike T>
    T& SheetsCollection::sheetAs(const size_t i)
    {
        throwIfInvalidIndex("sheet index", i, sheets);
        return static_cast<T&>(sheet(i));
    }
}

#endif // SHEETSCOLLOECTION_TXX
