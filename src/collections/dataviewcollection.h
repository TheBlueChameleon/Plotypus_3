#ifndef DATAVIEWCOLLECTION_H
#define DATAVIEWCOLLECTION_H

namespace Plotypus
{
    //! @todo copy-adder
    //! @bug hack in clearDataView at DataViewDefaultCompound
    class DataViewCollection
    {
        protected:
            std::vector<DataView*>          dataViews;
            const std::vector<DataViewType> allowedDataViewTypes;

            DataView&   addDataView(DataView* dataView);

            static void clearDataView(DataView* dataView);

        public:
            DataViewCollection(const std::vector<DataViewType>& allowedDataViewTypes);
            ~DataViewCollection();

            DataViewCollection&             reset();
            DataViewCollection&             clearDataViews();

            size_t                          getDataViewCount();
            const std::vector<DataView*>&   getDataViews() const;

            DataView&                       dataView(const size_t i);
            template<DataViewLike T>
            T&                              dataViewAs(const size_t i);
    };
}

#include "dataviewcollection.txx"
#endif // DATAVIEWCOLLECTION_H
