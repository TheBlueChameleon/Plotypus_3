#ifndef DATAVIEWDEFAULTCOMPOUND_H
#define DATAVIEWDEFAULTCOMPOUND_H

#include "dataviewdefault.h"

namespace Plotypus
{
    /**
     * @brief foo bar
     */

    template<class T>
    class DataviewDefaultCompound : public DataviewDefault
    {
        protected:
            std::span<T>                        data;
            std::array<DataSelector_t<T>, 6>    selectors;

            virtual void clearNonFunctionMembers();
            virtual void fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const;

        public:
            DataviewDefaultCompound(const PlotStyle    style);
            DataviewDefaultCompound(const PlotStyle    style, const std::string& label);
            DataviewDefaultCompound(const std::string& style);
            DataviewDefaultCompound(const std::string& style, const std::string& label);

            virtual size_t                          getArity() const;

            const std::span<T>&                     getData() const;
            DataviewDefaultCompound&                setData(const std::span<T>& newDataSource);
            DataviewDefaultCompound&                setData(const T* newDataSource, size_t N);

            const std::array<DataSelector_t<T>, 6>& getSelectors() const;
            DataviewDefaultCompound&                setSelectors(const std::array<DataSelector_t<T>, 6>& newSelectors);
            DataviewDefaultCompound&                setSelector (const ColumnType columnType, const DataSelector_t<T>& selector);

            virtual bool isDummy() const;
            virtual bool isComplete() const;
    };
}

#include "dataviewdefaultcompound.txx"
#endif // DATAVIEWDEFAULTCOMPOUND_H
