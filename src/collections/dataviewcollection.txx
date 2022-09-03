#ifndef DATAVIEWCOLLECTION_TXX
#define DATAVIEWCOLLECTION_TXX

namespace Plotypus
{
    template<DataViewLike T>
    T& DataViewCollection::dataViewAs(const size_t i)
    {
        return static_cast<T&>(dataView(i));
    }
}

#endif // DATAVIEWCOLLECTION_TXX
