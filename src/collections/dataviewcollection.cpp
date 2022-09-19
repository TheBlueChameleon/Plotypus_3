#include "dataviewcollection.h"

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
            clearDataview(dataview);
            throw UnsupportedOperationError("Cannot add Sheet of type " + getDataViewTypeName(viewType));
        }

        return dataviews.back();
    }

    void DataviewCollection::clearDataview(Dataview* dataview)
    {
        switch (dataview->getType())
        {
            case DataviewType::DataViewDefaultCompound:
                delete dynamic_cast<DataViewDefault*>(dataview);
                break;
            case DataviewType::DataViewDefaultSeparate:
                delete dynamic_cast<DataViewDefaultSeparate*>(dataview);
                break;
        }
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
            clearDataview(view);
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
