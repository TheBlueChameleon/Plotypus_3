#ifndef DATAVIEWCOLLECTION_TXX
#define DATAVIEWCOLLECTION_TXX

namespace Plotypus
{
    template<DataViewLike T>
    T& DataviewCollection::dataviewAs(const size_t i)
    {
        return static_cast<T&>(dataview(i));
    }
}

#endif // DATAVIEWCOLLECTION_TXX
