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
    template<class T>
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

            void fetchData(std::vector<double>& buffer, size_t recordID) const; //! @todo implement; consider making this public; probably virtual abstract

            void writeDatDataAsc(std::ostream& hFile) const;
            void writeDatDataBin(std::ostream& hFile) const;

        public:
            DataView2D(const std::string& label, const PlotStyle2D  style, const std::string& dataColumnFormat = "#");
            DataView2D(const std::string& label, const std::string& style, const std::string& dataColumnFormat = "#");

            virtual void reset();

            const std::string&          getFunc() const;
            void                        setFunc(const std::string& newFunc);

            int                         getLineStyle() const;
            void                        setLineStyle(int newLineStyle);

            virtual bool isDummy() const;
            virtual bool isComplete() const; //! @todo update

            virtual size_t getColumnID(const ColumnTypes columnType) const;

            // -------------------------------------------------------------- //
            // writers

            virtual void writeDatData () const;
            virtual void writeScriptData (std::ostream& hFile) const;
    };
}

#include "dataview2d.txx"
#endif // DATAVIEW2D_H
