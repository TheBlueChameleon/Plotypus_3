#ifndef DATAVIEW2D_H
#define DATAVIEW2D_H

#include <concepts>
#include <span>
#include <string>
#include <vector>

#include "../definitions/types.h"

#include "dataview.h"

namespace Plotypus
{
    class DataView2D : public DataView
    {
        protected:
            /*! @todo using clause
             *      for that, use a std::array<size_t, N> columnAssignmentList and a new enum in types.h
             *      enum gives named indices for columnAssignmentList
             *      columnAssignmentList tells where in data file to look for respective content
             *      requires constant for <not assigned> => magic constant = unsigned(-1)
             */

            std::string func;

            int lineStyle  = -1;
            int pointStyle = -1;

            virtual void clearFunctionMembers();
            virtual void clearNonFunctionMembers() = 0;

            void writeDatDataAsc(std::ostream& hFile) const;
            void writeDatDataBin(std::ostream& hFile) const;

        public:
            DataView2D(const std::string& label, const PlotStyle2D  style);
            DataView2D(const std::string& label, const std::string& style);

            virtual void reset();

            const std::string&          getFunc() const;
            void                        setFunc(const std::string& newFunc);

            int                         getLineStyle() const;
            void                        setLineStyle(int newLineStyle);

            virtual size_t getColumnID(const ColumnTypes columnType) const;

            virtual void fetchData(std::vector<double>& buffer, size_t recordID) const = 0;

            // -------------------------------------------------------------- //
            // writers

            virtual void writeDatData () const;
            virtual void writeScriptData (std::ostream& hFile) const;
    };
}

#endif // DATAVIEW2D_H
