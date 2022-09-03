#ifndef DATAVIEWDEFAULT_H
#define DATAVIEWDEFAULT_H

#include <array>
#include <concepts>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "dataview.h"

namespace Plotypus
{
    //! @todo cannot splot in polar coordinate system
    class DataViewDefault : public DataView
    {
        protected:
            bool variablePointSize  = false;
            bool variablePointType  = false;
            bool variablePointColor = false;

            std::string func;

            std::optional<size_t> lineStyle;
            std::optional<size_t> pointStyle;

            columnAssignmentList_t columnAssignments = {COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED, COLUMN_UNUSED};
            columnFormatList_t     columnFormats     = {COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT, COLUMN_FORMAT_DEFAULT};
            columnFormatList_t     columnHeadlines   = {};

            virtual void clearFunctionMembers();
            virtual void fetchData(std::vector<double>& buffer, size_t recordID, bool missingXColumn) const = 0;

            void writeDatDataAsc(std::ostream& hFile, std::vector<double>& lineBuffer, bool missingXColumn) const;
            void writeDatDataBin(std::ostream& hFile, std::vector<double>& lineBuffer, bool missingXColumn) const;

            void writeUsingSpecification(std::ostream& hFile) const;

            size_t getColumnIDOrThrow(const ColumnType columnType);

            void postSetColumnActions(const ColumnType columnType);
            void makePlusMinusFormat();

        public:
            DataViewDefault(const DataViewType type, const PlotStyle    plotStyleID);
            DataViewDefault(const DataViewType type, const PlotStyle    plotStyleID, const std::string& title);
            DataViewDefault(const DataViewType type, const std::string& plotStyle);
            DataViewDefault(const DataViewType type, const std::string& plotStyle,   const std::string& title);

            virtual DataViewDefault& reset();

            virtual DataViewDefault& setPlotStyleID(const PlotStyle newPlotStyle);

            virtual size_t      getArity() const = 0;

            const std::string&  getFunc() const;
            DataViewDefault&    setFunc(const std::string& newFunc);

            size_t              getLineStyle() const;
            DataViewDefault&    setLineStyle(size_t newLineStyle);
            DataViewDefault&    clearLineStyle();

            size_t              getPointStyle() const;
            DataViewDefault&    setPointStyle(size_t newPointStyle);
            DataViewDefault&    clearPointStyle();

            size_t&             columnAssignment(const size_t       columnID);
            size_t&             columnAssignment(const ColumnType   columnType);
            std::string&        columnFormat    (const size_t       columnID);
            std::string&        columnFormat    (const ColumnType   columnType);
            std::string&        columnHeadline  (const size_t       columnID);
            std::string&        columnHeadline  (const ColumnType   columnType);

            bool                getVariablePointSize() const;
            DataViewDefault&    setVariablePointSize(bool newVariablePointSize);
            bool                getVariablePointType() const;
            DataViewDefault&    setVariablePointType(bool newVariablePointType);
            bool                getVariablePointColor() const;
            DataViewDefault&    setVariablePointColor(bool newVariablePointColor);

            virtual bool isFunction() const;

            // -------------------------------------------------------------- //
            // writers

            virtual void writeTxtData   (std::ostream& hFile) const;
            virtual void writeDatData   ()                    const;
            virtual void writeScriptData(std::ostream& hFile, const StylesCollection& stylesColloction) const;
    };
}

#endif // DATAVIEWDEFAULT_H
