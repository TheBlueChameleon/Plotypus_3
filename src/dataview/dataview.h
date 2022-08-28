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
     *
     * @todo notitle option (suppresses key entry)
     *
     * @todo abstract autoFormat (clip to nan); quickForm only positive
     */
    class DataView
    {
        protected:
            PlotStyle       plotStyleID;
            PlotStyleFamily plotStyleFamily;

            std::string title;
            std::string plotStyle;
            std::string options = "";

            mutable std::string dataFilename = "";

            int         numberPrecision      = -1;
            std::string columnSeparatorTxt   = "\t";
            std::string columnSeparatorDat   = "\t";

            bool binaryDataOutput            = true;
            bool autoGenerateDataFilename    = true;

            virtual void clearFunctionMembers   () = 0;
            virtual void clearNonFunctionMembers() = 0;

        public:
            //! @bug call of virtual method
            DataView(const PlotStyle    plotStyleID, const std::string& label = "");
            DataView(const std::string& plotStyle, const std::string& label = "");

            virtual DataView& reset();

            const std::string&  getTitle() const;
            DataView&           setTitle(const std::string& newTitle);

            const std::string&  getPlotStyle() const;
            DataView&           setPlotStyle(const std::string& newPlotStyle);

            PlotStyleFamily     getPlotStyleFamily() const;
            DataView&           setPlotStyleFamily(PlotStyleFamily newStyleFamily);

            const PlotStyle     getPlotStyleID() const;
            virtual DataView&   setPlotStyleID(const PlotStyle newStyle);

            bool                getBinaryDataOutput() const;
            DataView&           setBinaryDataOutput(bool newBinaryDataOutput);

            const std::string&  getOptions() const;
            DataView&           setOptions(const std::string& newOptions);

            bool                getAutoGenerateDataFilename() const;
            DataView&           setAutoGenerateDataFilename(bool newAutoGenerateDataFilename);
            const std::string&  getDataFilename() const;
            DataView&           setDataFilename(const std::string& newDataFilename);

            int                 getNumberPrecision() const;
            DataView&           setNumberPrecision(int newNumberPrecision);

            const std::string&  getColumnSeparatorTxt() const;
            DataView&           setColumnSeparatorTxt(const std::string& newSeparatorTXT);
            const std::string&  getColumnSeparatorDat() const;
            DataView&           setColumnSeparatorDat(const std::string& newSeparatorDAT);

            virtual bool isFunction() const = 0;
            virtual bool isDummy   () const = 0;
            virtual bool isComplete() const = 0;

            // -------------------------------------------------------------- //
            // writers

            virtual void writeTxtData   (std::ostream& hFile)                                           const = 0;
            virtual void writeDatData   ()                                                              const = 0;
            virtual void writeScriptData(std::ostream& hFile, const StylesCollection& stylesColloction) const = 0;
    };
}

#endif // DATAVIEW_H
