#ifndef DATAVIEW2DCOMPOUND_H
#define DATAVIEW2DCOMPOUND_H

#include "dataview2d.h"

namespace Plotypus
{
    template<class T>
    class DataView2DCompound : public DataView2D
    {
        protected:
            std::span<T>                    data;
            std::array<DataSelector<T>, 6>  selectors;

            virtual void clearNonFunctionMembers();

        public:
            DataView2DCompound(const PlotStyle2D  style, const std::string& label = "");
            DataView2DCompound(const std::string& style, const std::string& label = "");

            virtual void reset();

            const std::span<T>&                     getData() const;
            void                                    setData(const std::span<T>& newDataSource);

            const std::array<DataSelector<T>, 6>&   getSelectors() const;
            void                                    setSelectors(const std::array<DataSelector<T>, 6>& newSelectors);
            void                                    setSelector (const ColumnTypes column, const DataSelector<T>& selector);

            virtual bool isDummy() const;
            virtual bool isComplete() const;

            virtual void fetchData(std::vector<double>& buffer, size_t recordID) const; //! @todo implement
    };
}

#include "dataview2dcompound.txx"
#endif // DATAVIEW2DCOMPOUND_H
