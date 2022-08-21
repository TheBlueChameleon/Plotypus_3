#ifndef DATAVIEWDEFAULT_H
#define DATAVIEWDEFAULT_H

#include <array>
#include <concepts>
#include <span>
#include <string>
#include <vector>

#include "dataview.h"

namespace Plotypus
{
    class DataViewDefault : public DataView
    {
        protected:
            std::string func;

            size_t lineStyle  = STYLE_ID_DEFAULT;
            size_t pointStyle = STYLE_ID_DEFAULT;

            columnAssignmentList_t columnAssignments = {COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED};
            columnFormatList_t     columnFormats     = {COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT};
            columnFormatList_t     columnHeadlines   = {};

            virtual void clearFunctionMembers();
            virtual void fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const = 0;

            void writeDatDataAsc(std::ostream& hFile, std::vector<double>& lineBuffer, bool missingXColumn) const;
            void writeDatDataBin(std::ostream& hFile, std::vector<double>& lineBuffer, bool missingXColumn) const;

            void writeUsingSpecification(std::ostream& hFile) const;

        public:
            DataViewDefault(const PlotStyle    style, const std::string& label = "");
            DataViewDefault(const std::string& style, const std::string& label = "");

            virtual void reset();
            virtual void setStyleID(const PlotStyle newStyle);

            virtual size_t      getArity() const = 0;

            const std::string&  getFunc() const;
            void                setFunc(const std::string& newFunc);

            size_t              getLineStyle() const;
            void                setLineStyle(size_t newLineStyle);

            size_t&             columnAssignment(const size_t       columnID);
            size_t&             columnAssignment(const ColumnType   columnType);
            std::string&        columnFormat    (const size_t       columnID);
            std::string&        columnFormat    (const ColumnType   columnType);
            std::string&        columnHeadline  (const size_t       columnID);
            std::string&        columnHeadline  (const ColumnType   columnType);

            virtual bool isFunction() const;
            virtual size_t getColumnID(const ColumnType columnType) const;

            // -------------------------------------------------------------- //
            // writers

            virtual void writeTxtData   (std::ostream& hFile) const;
            virtual void writeDatData   ()                    const;
            virtual void writeScriptData(std::ostream& hFile, const StylesCollection& stylesColloction) const;
    };
}

#endif // DATAVIEWDEFAULT_H
