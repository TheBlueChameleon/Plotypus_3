#ifndef DATAVIEW2DCOMPOUND_TXX
#define DATAVIEW2DCOMPOUND_TXX

#include "dataviewdefaultcompound.h"

namespace Plotypus
{
    template<class T>
    void DataViewDefaultCompound<T>::clearNonFunctionMembers()
    {
        data      = std::span<T>();
        selectors = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    }

    template<class T>
    void DataViewDefaultCompound<T>::fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const
    {
        // *INDENT-OFF*
        const T& datapoint = data[recordID];
        for (auto i : columnAssignments) {
            if (i == COLUMN_UNUSED) {continue;}         // ignore unused columns
            --i;                                        // zero based indices

            const auto& selector = selectors[i];        // fetch correct selector
            i -= missingXColumn;                        // correct for maybe missing X column

            buffer[i] = selector(datapoint);
        }
        // *INDENT-ON*
    }

    // ====================================================================== //

    template<class T>
    DataViewDefaultCompound<T>::DataViewDefaultCompound(const PlotStyle style, const std::string& label) :
        DataViewDefault(style, label)
    {}

    template<class T>
    DataViewDefaultCompound<T>::DataViewDefaultCompound(const std::string& style, const std::string& label) :
        DataViewDefault(style, label)
    {}

    // ====================================================================== //

    template<class T>
    size_t DataViewDefaultCompound<T>::getArity() const
    {
        return data.size();
    }

    template<class T>
    const std::span<T>& DataViewDefaultCompound<T>::getData() const
    {
        return data;
    }

    template<class T>
    DataViewDefaultCompound<T>& DataViewDefaultCompound<T>::setData(const std::span<T>& newDataSource)
    {
        data = newDataSource;
        return *this;
    }

    template<class T>
    DataViewDefaultCompound<T>& DataViewDefaultCompound<T>::setData(const T* newDataSource, size_t N)
    {
        data = std::span<T>(newDataSource, newDataSource + N);
        return *this;
    }

    template<class T>
    const std::array<DataSelector_t<T>, 6>& DataViewDefaultCompound<T>::getSelectors() const
    {
        return selectors;
    }

    template<class T>
    DataViewDefaultCompound<T>& DataViewDefaultCompound<T>::setSelectors(const std::array<DataSelector_t<T>, 6>& newSelectors)
    {
        selectors = newSelectors;
        for (size_t i = 0u; const auto& selector : selectors)
        {
            // *INDENT-OFF*
            if (selector) {columnAssignments[i] = ++i;}         // columnAssignments[i] = i + 1 for i in range(size)
            // *INDENT-ON*
        }
        return *this;
    }

    template<class T>
    DataViewDefaultCompound<T>& DataViewDefaultCompound<T>::setSelector(const ColumnType columnType, const DataSelector_t<T>& selector)
    {
        const auto columnID = getColumnIDOrThrow(columnType) - 1; // column IDs are 1-based...

        selectors        [columnID] = selector;
        columnAssignments[columnID] = columnID + 1;
        columnHeadlines  [columnID] = getColumnIDName(columnType);
        return *this;
    }

    template<class T>
    bool DataViewDefaultCompound<T>::isDummy() const
    {
        bool result = func.empty();
        result &= data.empty();
        for (const auto& selector : selectors)
        {
            result &= static_cast<bool>(selector);
        }
        return result;
    }

    template<class T>
    bool DataViewDefaultCompound<T>::isComplete() const
    {
        // *INDENT-OFF*
        if (isDummy())      {return true;}
        if (data.empty())   {return false;}

        const auto isNullSelector = [] (const DataSelector_t<T>& selector) {return selector == nullptr;};

        return checkColumnListOccupationVsPlotType(plotStyleID, selectors, isNullSelector);
        // *INDENT-ON*
    }
}

#endif // DATAVIEW2DCOMPOUND_TXX
