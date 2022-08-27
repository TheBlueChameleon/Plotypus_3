#ifndef DATAVIEWDEFAULTSEPARATE_H
#define DATAVIEWDEFAULTSEPARATE_H

#include "dataviewdefault.h"

namespace Plotypus
{
    class DataViewDefaultSeparate : public DataViewDefault
    {
        protected:
            columnViewList_t data;

            virtual void clearNonFunctionMembers();

            virtual void fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const;

        public:
            DataViewDefaultSeparate(const PlotStyle  style, const std::string& label = "");
            DataViewDefaultSeparate(const std::string& style, const std::string& label = "");

            virtual size_t              getArity() const;       //! @todo: maybe do check: isComplete?

            //std::span<double>&         data(ColumnType columnType);
            const columnViewList_t&     getData() const;
            const std::span<double>&    getData(ColumnType columnType) const;
            DataViewDefaultSeparate&    setData(ColumnType columnType, const std::span<double>& newdata);

            virtual bool isDummy() const;
            virtual bool isComplete() const;
    };
}

#endif // DATAVIEWDEFAULTSEPARATE_H
