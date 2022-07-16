#include "dataview2dcompound.h"

namespace Plotypus
{
    template<class T>
    void DataView2DCompound<T>::clearNonFunctionMembers()
    {
        data = std::span<T>();
    }

    // ====================================================================== //

    template<class T>
    DataView2DCompound<T>::DataView2DCompound(const std::string& label, const PlotStyle2D style, const std::string& dataColumnFormat) :
        DataView2D<T>(label, style, dataColumnFormat)
    {}

    template<class T>
    DataView2DCompound<T>::DataView2DCompound(const std::string& label, const std::string& style, const std::string& dataColumnFormat) :
        DataView2D<T>(label, style, dataColumnFormat)
    {}

    // ====================================================================== //

    template<class T>
    const std::span<T>& DataView2DCompound<T>::getData() const
    {
        return data;
    }

    template<class T>
    void DataView2DCompound<T>::setData(const std::span<T>& newDataSource)
    {
        data = newDataSource;
    }

    template<class T>
    const std::vector<DataSelector<T>>& DataView2DCompound<T>::getSelectors() const
    {
        return selectors;
    }

    template<class T>
    void DataView2DCompound<T>::setSelectors(const std::vector<DataSelector<T>>& newSelectors)
    {
        selectors = newSelectors;
    }
}
