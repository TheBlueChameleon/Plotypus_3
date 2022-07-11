#include "dataview2d.h"

using namespace Plotypus;

namespace Plotypus
{
    template<class T>
    DataView2D<T>::DataView2D(const std::string& label, const std::string& style, const std::string& dataColumnFormat) :
        DataView(label, style, dataColumnFormat)
    {}

    template<class T>
    void DataView2D<T>::reset()
    {
        DataView::reset();

        data        = std::span<T>();
        selector    = std::function<double (const T)>();
        func        = "";
    }

    template<class T>
    const std::span<const T>& DataView2D<T>::getData() const
    {
        return data;
    }

    template<class T>
    void DataView2D<T>::setData(const std::span<const T>& newData)
    {
        data = newData;
        func = "";
    }

    template<class T>
    const DataSelector<T>& DataView2D<T>::getSelector() const
    {
        return selector;
    }

    template<class T>
    void DataView2D<T>::setSelector(const DataSelector<T>& newSelector)
    {
        selector    = newSelector;
        func        = "";
    }

    template<class T>
    const std::string& DataView2D<T>::getFunc() const
    {
        return func;
    }

    template<class T>
    void DataView2D<T>::setFunc(const std::string& newFunc)
    {
        func        = newFunc;
        data        = std::span<T>();
        selector    = std::function<double (const T)>();
    }

    template<class T>
    int DataView2D<T>::getLineStyle() const
    {
        return lineStyle;
    }

    template<class T>
    void DataView2D<T>::setLineStyle(int newLineStyle)
    {
        lineStyle = newLineStyle;
    }
}
