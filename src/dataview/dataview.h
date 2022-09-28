#ifndef DATAVIEW_H
#define DATAVIEW_H

#include <optional>
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
     *
     * @todo rename plotStyle -> plotStyleName; plotStyleID -> plotStyle.
     */
    class Dataview
    {
        protected:
            const DataviewType          type;

            PlotStyle                   plotStyleID;
            PlotStyleFamily             plotStyleFamily;

            std::optional<std::string>  title;
            std::string                 plotStyle;
            std::optional<std::string>  options;

            mutable std::string         dataFilename;

            int                         numberPrecision             = -1;
            std::string                 columnSeparatorTxt          = "\t";
            std::string                 columnSeparatorDat          = "\t";

            bool                        binaryDataOutput            = true;
            bool                        autoGenerateDataFilename    = true;

            virtual void clearFunctionMembers   () = 0;
            virtual void clearNonFunctionMembers() = 0;

        public:
            Dataview(const DataviewType type, const PlotStyle    plotStyleID);
            Dataview(const DataviewType type, const PlotStyle    plotStyleID, const std::string& title);
            Dataview(const DataviewType type, const std::string& plotStyle);
            Dataview(const DataviewType type, const std::string& plotStyle,   const std::string& title);

            virtual Dataview&   reset();

            DataviewType        getType() const;

            const std::string   getTitle() const;
            Dataview&           setTitle(const std::string& newTitle);
            Dataview&           clearTitle();

            const std::string&  getPlotStyle() const;
            Dataview&           setPlotStyle(const std::string& newPlotStyle);

            PlotStyleFamily     getPlotStyleFamily() const;
            Dataview&           setPlotStyleFamily(PlotStyleFamily newStyleFamily);

            const PlotStyle     getPlotStyleID() const;
            Dataview&           setPlotStyleID(const PlotStyle newStyle);

            const std::string   getOptions() const;
            Dataview&           setOptions(const std::string& newOptions);
            Dataview&           clearOptions();

            bool                getAutoGenerateDataFilename() const;
            Dataview&           setAutoGenerateDataFilename(bool newAutoGenerateDataFilename);
            const std::string&  getDataFilename() const;
            Dataview&           setDataFilename(const std::string& newDataFilename);

            int                 getNumberPrecision() const;
            Dataview&           setNumberPrecision(int newNumberPrecision);

            const std::string&  getColumnSeparatorTxt() const;
            Dataview&           setColumnSeparatorTxt(const std::string& newSeparatorTXT);
            const std::string&  getColumnSeparatorDat() const;
            Dataview&           setColumnSeparatorDat(const std::string& newSeparatorDAT);

            bool                getBinaryDataOutput() const;
            Dataview&           setBinaryDataOutput(bool newBinaryDataOutput);

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
