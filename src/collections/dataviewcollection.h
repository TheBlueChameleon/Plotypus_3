#ifndef DATAVIEWCOLLECTION_H
#define DATAVIEWCOLLECTION_H

namespace Plotypus
{
    //! @todo copy-adder
    //! @bug hack in clearDataView at DataViewDefaultCompound

    class DataviewCollection
    {
        protected:
            std::vector<Dataview*>          dataviews;
            const std::vector<DataviewType> allowedDataviewTypes;

            Dataview* addDataview(Dataview* dataview);

            static void clearDataview(Dataview* dataview);

        public:
            DataviewCollection(const std::vector<DataviewType>& allowedDataviewTypes);
            ~DataviewCollection();

            DataviewCollection&             reset();
            DataviewCollection&             clearDataviews();

            size_t                          getDataviewCount();
            const std::vector<Dataview*>&   getDataviews() const;

            Dataview&                       dataview(const size_t i);
            template<DataViewLike T>
            T&                              dataviewAs(const size_t i);
    };
}

#include "dataviewcollection.txx"
#endif // DATAVIEWCOLLECTION_H
