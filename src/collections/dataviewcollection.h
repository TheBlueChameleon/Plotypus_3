#ifndef DATAVIEWCOLLECTION_H
#define DATAVIEWCOLLECTION_H

#include <vector>

#include "../definitions/types.h"

namespace Plotypus
{
    //! @todo copy-adder

    class Dataview;
    enum class DataviewType;

    class DataviewCollection
    {
        protected:
            std::vector<Dataview*>          dataviews;
            const std::vector<DataviewType> allowedDataviewTypes;

            Dataview* addDataview(Dataview* dataview);

        public:
            DataviewCollection(const std::vector<DataviewType>& allowedDataviewTypes);
            ~DataviewCollection();

            DataviewCollection&             reset();
            DataviewCollection&             clearDataviews();

            size_t                          getDataviewCount();
            const std::vector<Dataview*>&   getDataviews() const;

            Dataview&                       dataview(const size_t i);
            template<DataviewLike T>
            T&                              dataviewAs(const size_t i);
    };
}

#include "dataviewcollection.txx"
#endif // DATAVIEWCOLLECTION_H
