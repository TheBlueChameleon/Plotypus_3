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
    class DataviewDefault : public Dataview
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

            void writeTxtHeadlines(std::ostream& hFile) const;

            void writeDatDataAsc(std::ostream& hFile, std::vector<double>& lineBuffer, bool missingXColumn) const;
            void writeDatDataBin(std::ostream& hFile, std::vector<double>& lineBuffer, bool missingXColumn) const;

            void writeUsingSpecification(std::ostream& hFile) const;

            size_t getColumnIDOrThrow(const ColumnType columnType);

            void postSetColumnActions(const ColumnType columnType);
            void makePlusMinusFormat();

        public:
            DataviewDefault(const DataviewType type, const PlotStyle    plotStyleID);
            DataviewDefault(const DataviewType type, const PlotStyle    plotStyleID, const std::string& title);
            DataviewDefault(const DataviewType type, const std::string& plotStyle);
            DataviewDefault(const DataviewType type, const std::string& plotStyle,   const std::string& title);

            virtual DataviewDefault& reset();

            virtual DataviewDefault& setPlotStyleID(const PlotStyle newPlotStyle);

            virtual size_t      getArity() const = 0;

            const std::string&  getFunc() const;
            DataviewDefault&    setFunc(const std::string& newFunc);

            size_t              getLineStyle() const;
            DataviewDefault&    setLineStyle(const size_t newLineStyle);
            DataviewDefault&    clearLineStyle();

            size_t              getPointStyle() const;
            DataviewDefault&    setPointStyle(const size_t newPointStyle);
            DataviewDefault&    clearPointStyle();

            DataviewDefault&    setColumnAssignment(const size_t       columnIndex, const size_t newSourceColumn);
            DataviewDefault&    setColumnAssignment(const ColumnType   columnType, const size_t newSourceColumn);
            const size_t&       getColumnAssignment(const size_t       columnIndex) const;
            const size_t&       getColumnAssignment(const ColumnType   columnType)  const;

            DataviewDefault&    setColumnFormat    (const size_t       columnIndex, const std::string& newFormat);
            DataviewDefault&    setColumnFormat    (const ColumnType   columnType, const std::string& newFormat);
            const std::string&  getColumnFormat    (const size_t       columnIndex) const;
            const std::string&  getColumnFormat    (const ColumnType   columnType)  const;

            DataviewDefault&    setColumnHeadline  (const size_t       columnIndex, const std::string& newHeadline);
            DataviewDefault&    setColumnHeadline  (const ColumnType   columnType, const std::string& newHeadline);
            const std::string&  getColumnHeadline  (const size_t       columnIndex) const;
            const std::string&  getColumnHeadline  (const ColumnType   columnType) const;

            bool                getVariablePointSize() const;
            DataviewDefault&    setVariablePointSize(bool newVariablePointSize);
            bool                getVariablePointType() const;
            DataviewDefault&    setVariablePointType(bool newVariablePointType);
            bool                getVariablePointColor() const;
            DataviewDefault&    setVariablePointColor(bool newVariablePointColor);

            virtual bool isFunction() const;

            // -------------------------------------------------------------- //
            // writers

            virtual void writeTxtData   (std::ostream& hFile) const;
            virtual void writeDatData   ()                    const;
            virtual void writeScriptData(std::ostream& hFile, const StylesCollection& stylesColloction) const;
    };
}

#endif // DATAVIEWDEFAULT_H
