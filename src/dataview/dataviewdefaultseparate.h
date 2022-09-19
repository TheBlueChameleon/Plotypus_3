#ifndef DATAVIEWDEFAULTSEPARATE_H
#define DATAVIEWDEFAULTSEPARATE_H

#include "dataviewdefault.h"

namespace Plotypus
{
    class DataviewDefaultSeparate : public DataviewDefault
    {
        protected:
            columnViewList_t data;

            virtual void clearNonFunctionMembers();
            virtual void fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const;

        public:
            DataviewDefaultSeparate(const PlotStyle    style);
            DataviewDefaultSeparate(const PlotStyle    style, const std::string& title);
            DataviewDefaultSeparate(const std::string& style);
            DataviewDefaultSeparate(const std::string& style, const std::string& title);

            //! @todo maybe do check: isComplete?
            virtual size_t              getArity() const;

            const columnViewList_t&     getData() const;
            const std::span<double>&    getData(const ColumnType columnType) const;
            DataviewDefaultSeparate&    setData(const ColumnType columnType, const std::span<double>& newdata);

            virtual bool isDummy() const;
            virtual bool isComplete() const;
    };
}

#endif // DATAVIEWDEFAULTSEPARATE_H
