#ifndef REPORT_TXX
#define REPORT_TXX

namespace Plotypus
{
    template<SheetLike T>
    T& Report::sheetAs(const size_t i)
    {
        return static_cast<T&>(sheet(i));
    }
}

#endif // REPORT_TXX
