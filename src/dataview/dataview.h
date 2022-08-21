#ifndef DATAVIEW_H
#define DATAVIEW_H

#include <string>

#include "../definitions/constants.h"

namespace Plotypus
{
    class StylesCollection;

    /**
     * @todo introduce subtypes:
     *  DataViewMatrixFlat, DataViewMatrix2D; with 2nd level subtypes for compound/separate?
     */
    class DataView
    {
        protected:
            PlotStyle styleID;

            std::string title;
            std::string style;
            std::string options = "";

            mutable std::string dataFilename = "";

            int         numberPrecision    = -1;
            std::string columnSeparatorTxt = "\t";
            std::string columnSeparatorDat = "\t";

            bool binaryDataOutput         = true;
            bool autoGenerateDataFilename = true;

            virtual void clearFunctionMembers   () = 0;
            virtual void clearNonFunctionMembers() = 0;

        public:
            DataView(const PlotStyle    style, const std::string& label = "");
            DataView(const std::string& style, const std::string& label = "");

            virtual void reset();

            const std::string&  getTitle() const;
            void                setTitle(const std::string& newTitle);

            const std::string&  getStyle() const;
            void                setStyle(const std::string& newStyle);

            const PlotStyle     getStyleID() const;
            virtual void        setStyleID(const PlotStyle newStyle);

            bool                getBinaryDataOutput() const;
            void                setBinaryDataOutput(bool newBinaryDataOutput);

            const std::string&  getOptions() const;
            void                setOptions(const std::string& newOptions);

            bool                getAutoGenerateDataFilename() const;
            void                setAutoGenerateDataFilename(bool newAutoGenerateDataFilename);
            const std::string&  getDataFilename() const;
            void                setDataFilename(const std::string& newDataFilename) const;

            int                 getNumberPrecision() const;
            void                setNumberPrecision(int newNumberPrecision);

            const std::string&  getColumnSeparatorTxt() const;
            void                setColumnSeparatorTxt(const std::string& newSeparatorTXT);
            const std::string&  getColumnSeparatorDat() const;
            void                setColumnSeparatorDat(const std::string& newSeparatorDAT);

            virtual bool isFunction() const = 0;
            virtual bool isDummy   () const = 0;
            virtual bool isComplete() const = 0;

            virtual size_t getColumnID(const ColumnType columnType) const = 0;

            // -------------------------------------------------------------- //
            // writers

            virtual void writeTxtData   (std::ostream& hFile)                                           const = 0;
            virtual void writeDatData   ()                                                              const = 0;
            virtual void writeScriptData(std::ostream& hFile, const StylesCollection& stylesColloction) const = 0;
    };
}

#endif // DATAVIEW_H
