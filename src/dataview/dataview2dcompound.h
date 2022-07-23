#ifndef DATAVIEW2DCOMPOUND_H
#define DATAVIEW2DCOMPOUND_H

#include "dataview2d.h"

namespace Plotypus
{
    template<class T>
    class DataView2DCompound : public DataView2D
    {
            /**
             * @todo consider making T require iterable, and make data simply an iterable.
             *      if doing that change, make sure this does not require lots of copying.
             *      would probably require to internally store iterators and make the code a lot harder on the eyes...
             *      would require fetchData to take a T::iterator instead of size_t recordID
             *      has issues with permanence (end need not remain the last element, for example)
             */

        protected:
            std::span<T>                        data;
            std::array<DataSelector_t<T>, 6>    selectors;

            virtual void clearNonFunctionMembers();

            virtual void fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const;

        public:
            DataView2DCompound(const PlotStyle2D  style, const std::string& label = "");
            DataView2DCompound(const std::string& style, const std::string& label = "");

            virtual void reset();

            virtual size_t                          getArity() const;

            const std::span<T>&                     getData() const;
            void                                    setData(const std::span<T>& newDataSource);
            void                                    setData(const T* newDataSource, size_t N);

            const std::array<DataSelector_t<T>, 6>&   getSelectors() const;
            void                                    setSelectors(const std::array<DataSelector_t<T>, 6>& newSelectors);
            void                                    setSelector (const ColumnTypes column, const DataSelector_t<T>& selector);

            virtual bool isDummy() const;
            virtual bool isComplete() const;
    };
}

#include "dataview2dcompound.txx"
#endif // DATAVIEW2DCOMPOUND_H
