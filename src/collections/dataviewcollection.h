#ifndef DATAVIEWCOLLECTION_H
#define DATAVIEWCOLLECTION_H

namespace Plotypus
{
    //! @todo copy-adder
    //! @bug hack in clearDataView at DataViewDefaultCompound
    class DataviewCollection
    {
        protected:
            std::vector<DataView*>          dataviews;
            const std::vector<DataViewType> allowedDataviewTypes;

            DataView* addDataview(DataView* dataview);

            static void clearDataview(DataView* dataview);

        public:
            DataviewCollection(const std::vector<DataViewType>& allowedDataviewTypes);
            ~DataviewCollection();

            DataviewCollection&             reset();
            DataviewCollection&             clearDataviews();

            size_t                          getDataviewCount();
            const std::vector<DataView*>&   getDataviews() const;

            DataView&                       dataview(const size_t i);
            template<DataViewLike T>
            T&                              dataviewAs(const size_t i);
    };
}

#include "dataviewcollection.txx"
#endif // DATAVIEWCOLLECTION_H
