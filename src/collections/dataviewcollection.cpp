#include "dataviewcollection.h"

#include "../dataview/dataview.h"
#include "../base/util.h"

namespace Plotypus
{
    Dataview* DataviewCollection::addDataview(Dataview* dataview)
    {
        auto viewType = dataview->getType();
        if (contains(viewType, allowedDataviewTypes))
        {
            dataviews.push_back(dataview);
        }
        else
        {
            delete dataview;
            throw UnsupportedOperationError("Cannot add Sheet of type " + getDataviewTypeName(viewType));
        }

        return dataviews.back();
    }

    // ====================================================================== //

    DataviewCollection::DataviewCollection(const std::vector<DataviewType>& allowedDataviewTypes) :
        allowedDataviewTypes(allowedDataviewTypes)
    {}

    DataviewCollection::~DataviewCollection()
    {
        clearDataviews();
    }

    // ====================================================================== //

    DataviewCollection& DataviewCollection::reset()
    {
        return clearDataviews();
    }

    DataviewCollection& DataviewCollection::clearDataviews()
    {
        for (auto view : dataviews)
        {
            delete view;
        }
        dataviews.clear();

        return *this;
    }

    size_t DataviewCollection::getDataviewCount()
    {
        return dataviews.size();
    }

    const std::vector<Dataview*>& DataviewCollection::getDataviews() const
    {
        return dataviews;
    }

    Dataview& DataviewCollection::dataview(const size_t i)
    {
        throwIfInvalidIndex("dataview index", i, dataviews);
        return *(dataviews[i]);
    }
}
