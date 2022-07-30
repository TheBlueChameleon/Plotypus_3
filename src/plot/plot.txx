#ifndef PLOT_TXX
#define PLOT_TXX

namespace Plotypus
{
    template<DataViewLike T>
    T& Plot::dataViewAs(const size_t i)
    {
        return static_cast<T&>(dataView(i));
    }
}

#endif // PLOT_TXX
