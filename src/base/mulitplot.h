#ifndef MULITPLOT_H
#define MULITPLOT_H

#include <optional>
#include <set>
#include <string>

#include "../definitions/types.h"
#include "../sheets/sheet.h"

namespace Plotypus
{

    //! @todo most of the layout-commands
    //! @todo add size/origin on Sheet
    //! @todo add convenience non-uniform grid creators aka arrangeX
    //! @todo lock adding overlays (as positioning cannot be distinguished from in-frame); maybe add boolean 'locked' to OverlaysCollection

    class MulitPlot : public Sheet, public SheetsCollection
    {
        protected:
            static constexpr std::initializer_list<SheetType> allowedSheetTypes = {SheetType::Sheet,
                                                                                   SheetType::PlotOrthogonalAxis,
                                                                                   SheetType::PlotRadialAxes
                                                                                  };

            // note: optional string 'title' present from Sheet

            std::optional<MultiplotLayout_t>    layout;
            std::set<size_t>                    blanks; // triggers "set multiplot next"

            std::optional<std::string>          options;

            std::string                         frameSeparatorTxt   = "--------------------------------------------------------------------------------\n";

        public:
            MulitPlot(const std::string& title);

            MulitPlot&          reset();

            MultiplotLayout_t   getLayout() const;
            MulitPlot&          setLayout(const MultiplotLayout_t& newLayout);
            MulitPlot&          clearLayout();

            GridPosition_t      getGridDimensions() const;
            MulitPlot&          setGridDimensions(const GridPosition_t& newGridDimensions);

            StackingOrder       getStackingOrder() const;
            MulitPlot&          setStackingOrder(const StackingOrder newStackingOrder);

            StackingDirection   getStackingDirection() const;
            MulitPlot&          setStackingDirection(const StackingDirection newStackingDirection);

            Margins_t           getMargins() const;
            MulitPlot&          setMargins(const Margins_t& newMargins);
            MulitPlot&          clearMargins();

            MultiplotSpacing_t  getSpacing() const;
            MulitPlot&          setSpacing(const MultiplotSpacing_t& newSpacing);
            MulitPlot&          clearSpacing();

            std::string         getOptions() const;
            MulitPlot&          setOptions(const std::string& newOptions);
            MulitPlot&          clearOptions();

            const std::string&  getFrameSeparatorTxt() const;
            void                setFrameSeparatorTxt(const std::string& newFrameSeparatorTxt);

            // -------------------------------------------------------------- //
            // writers

            virtual void preprocessSheet(const std::string& autoFilenameBase, const std::string& extension) const;

            virtual void writeTxtHead       (std::ostream& hFile) const;
            virtual void writeTxtData       (std::ostream& hFile) const;

            virtual void writeDatData() const;

            virtual void writeScriptHead    (std::ostream& hFile) const;
            virtual void writeScriptData    (std::ostream& hFile, const StylesCollection& stylesCollection) const;
            virtual void writeScriptFooter  (std::ostream& hFile, const int pageNum) const;
    };
}

#endif // MULITPLOT_H
