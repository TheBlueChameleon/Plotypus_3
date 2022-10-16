#ifndef DATAVIEWMATRIX_H
#define DATAVIEWMATRIX_H

#include <optional>
#include <span>
#include <string>

#include "dataview.h"

#include "../definitions/types.h"

namespace Plotypus
{
    class DataviewMatrix : public Dataview
    {
        private:
            std::string func;

            std::optional<size_t> lineStyle;
            std::optional<size_t> pointStyle;

            std::string dataFormat = COLUMN_FORMAT_DEFAULT;

            virtual void clearFunctionMembers   ();

            virtual void writeDatDataAsc(std::ostream& hFile) const = 0;
            virtual void writeDatDataBin(std::ostream& hFile) const = 0;

        public:
            DataviewMatrix(const DataviewType type, const PlotStyle    plotStyleID);
            DataviewMatrix(const DataviewType type, const PlotStyle    plotStyleID, const std::string& title);
            DataviewMatrix(const DataviewType type, const std::string& plotStyle);
            DataviewMatrix(const DataviewType type, const std::string& plotStyle,   const std::string& title);

            virtual DataviewMatrix& reset();

            virtual GridDimension_t getArity() const = 0;

            const std::string&  getFunc() const;
            DataviewMatrix&     setFunc(const std::string& newFunc);

            size_t              getLineStyle() const;
            DataviewMatrix&     setLineStyle(const size_t newLineStyle);
            DataviewMatrix&     clearLineStyle();

            size_t              getPointStyle() const;
            DataviewMatrix&     setPointStyle(const size_t newPointStyle);
            DataviewMatrix&     clearPointStyle();

            const std::string&  getDataFormat() const;
            DataviewMatrix&     setDataFormat(const std::string& newDataFormat);

            virtual bool isFunction() const;

            // -------------------------------------------------------------- //
            // writers


    };

    // ====================================================================== //
}

#endif // DATAVIEWMATRIX_H
