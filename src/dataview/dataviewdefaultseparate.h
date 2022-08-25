#ifndef DATAVIEWDEFAULTSEPARATE_H
#define DATAVIEWDEFAULTSEPARATE_H

#include "dataviewdefault.h"

namespace Plotypus
{
    class DataViewDefaultSeparate : public DataViewDefault
    {
        protected:
            columnViewList_t m_data;

            virtual void clearNonFunctionMembers();

            virtual void fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const;

        public:
            DataViewDefaultSeparate(const PlotStyle  style, const std::string& label = "");
            DataViewDefaultSeparate(const std::string& style, const std::string& label = "");

            // all functionality of "reset" already in dataview2d

            virtual size_t          getArity() const;       //! @todo: maybe do check: isComplete?

            std::span<double>&         data(ColumnType columnType);
            const columnViewList_t& getData() const;
            void                    setData(const columnViewList_t& newData);

            virtual bool isDummy() const;
            virtual bool isComplete() const; /** @todo move implementation to dataview2d as template with param nullObjectChecker
                                              *  @todo complete switch case
                                              *  @bug reports spurious false on Lines
                                              */
    };
}

#endif // DATAVIEWDEFAULTSEPARATE_H
