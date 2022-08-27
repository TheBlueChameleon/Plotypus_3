#ifndef DATAVIEWDEFAULTCOMPOUND_H
#define DATAVIEWDEFAULTCOMPOUND_H

#include <iomanip>

#include "dataviewdefault.h"

namespace Plotypus
{
    template<class T>
    class DataViewDefaultCompound : public DataViewDefault
    {
        protected:
            std::span<T>                        data;
            std::array<DataSelector_t<T>, 6>    selectors;

            virtual void clearNonFunctionMembers();

            virtual void fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const;

        public:
            DataViewDefaultCompound(const PlotStyle  style, const std::string& label = "");
            DataViewDefaultCompound(const std::string& style, const std::string& label = "");

            virtual size_t                          getArity() const;

            const std::span<T>&                     getData() const;
            void                                    setData(const std::span<T>& newDataSource);
            void                                    setData(const T* newDataSource, size_t N);

            const std::array<DataSelector_t<T>, 6>& getSelectors() const;
            void                                    setSelectors(const std::array<DataSelector_t<T>, 6>& newSelectors);
            void                                    setSelector (const ColumnType columnType, const DataSelector_t<T>& selector);

            virtual bool isDummy() const;
            virtual bool isComplete() const;
    };
}

#include "dataviewdefaultcompound.txx"
#endif // DATAVIEWDEFAULTCOMPOUND_H
