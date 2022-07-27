#ifndef DATAVIEW2DCOMPOUND_H
#define DATAVIEW2DCOMPOUND_H

#include "dataview2d.h"

namespace Plotypus
{
    template<class T>
    class DataView2DCompound : public DataView2D
    {
        protected:
            std::span<T>                        data;
            std::array<DataSelector_t<T>, 6>    selectors;

            virtual void clearNonFunctionMembers();

            virtual void fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const;

        public:
            DataView2DCompound(const PlotStyle2D  style, const std::string& label = "");
            DataView2DCompound(const std::string& style, const std::string& label = "");

            // all functionality of "reset" already in dataview2d

            virtual size_t                          getArity() const;

            const std::span<T>&                     getData() const;
            void                                    setData(const std::span<T>& newDataSource);
            void                                    setData(const T* newDataSource, size_t N);

            const std::array<DataSelector_t<T>, 6>& getSelectors() const;
            void                                    setSelectors(const std::array<DataSelector_t<T>, 6>& newSelectors);
            void                                    setSelector (const ColumnTypes column, const DataSelector_t<T>& selector);

            virtual bool isDummy() const;
            virtual bool isComplete() const;
    };
}

#include "dataview2dcompound.txx"
#endif // DATAVIEW2DCOMPOUND_H
