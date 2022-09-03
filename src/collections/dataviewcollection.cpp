#include "dataviewcollection.h"

namespace Plotypus
{
    DataView* DataViewCollection::addDataView(DataView* dataView)
    {
        auto viewType = dataView->getType();
        if (contains(viewType, allowedDataViewTypes))
        {
            dataViews.push_back(dataView);
        }
        else
        {
            clearDataView(dataView);
            throw UnsupportedOperationError("Cannot add Sheet of type " + getDataViewTypeName(viewType));
        }

        return dataViews.back();
    }

    void DataViewCollection::clearDataView(DataView* dataView)
    {
        switch (dataView->getType())
        {
            case DataViewType::DataViewDefaultCompound:
                delete dynamic_cast<DataViewDefault*>(dataView);
                break;
            case DataViewType::DataViewDefaultSeparate:
                delete dynamic_cast<DataViewDefaultSeparate*>(dataView);
                break;
        }
    }

    // ====================================================================== //

    DataViewCollection::DataViewCollection(const std::vector<DataViewType>& allowedDataViewTypes) :
        allowedDataViewTypes(allowedDataViewTypes)
    {}

    DataViewCollection::~DataViewCollection()
    {
        clearDataViews();
    }

    // ====================================================================== //

    DataViewCollection& DataViewCollection::reset()
    {
        return clearDataViews();
    }

    DataViewCollection& DataViewCollection::clearDataViews()
    {
        for (auto view : dataViews)
        {
            clearDataView(view);
        }
        dataViews.clear();

        return *this;
    }

    size_t DataViewCollection::getDataViewCount()
    {
        return dataViews.size();
    }

    const std::vector<DataView*>& DataViewCollection::getDataViews() const
    {
        return dataViews;
    }

    DataView& DataViewCollection::dataView(const size_t i)
    {
        throwIfInvalidIndex("dataview index", i, dataViews);
        return *(dataViews[i]);
    }
}
