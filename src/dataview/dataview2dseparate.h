#ifndef DATAVIEW2DSEPARATE_H
#define DATAVIEW2DSEPARATE_H

#include "dataview2d.h"

namespace Plotypus
{
    class DataView2DSeparate : public DataView2D
    {
        protected:
            columnViewList_t m_data;

            virtual void clearNonFunctionMembers();

            virtual void fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const;

        public:
            DataView2DSeparate(const PlotStyle2D  style, const std::string& label = "");
            DataView2DSeparate(const std::string& style, const std::string& label = "");

            // all functionality of "reset" already in dataview2d

            virtual size_t          getArity() const;       //! @todo: maybe do check: isComplete?

            std::span<double>&         data(ColumnType columnType);
            const columnViewList_t& getData() const;
            void                    setData(const columnViewList_t& newData);

            virtual bool isDummy() const;
            virtual bool isComplete() const;
    };
}

#endif // DATAVIEW2DSEPARATE_H
