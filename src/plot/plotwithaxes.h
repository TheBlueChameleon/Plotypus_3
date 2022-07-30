#ifndef PLOT_WITH_AXES_H
#define PLOT_WITH_AXES_H

#include <span>
#include <string>
#include <unordered_map>

#include "../dataview/dataview2dcompound.h"

#include "plot.h"

namespace Plotypus
{
    /**
     * @todo set equal xy / xyz
     */

    class PlotWithAxes : public Plot
    {
        protected:
            std::unordered_map<AxisType, AxisDescriptor> axes;

            bool polar = false;

            static std::string generateRangeString (double min,                   double max);
            static std::string generateTicsSequence(double min, double increment, double max, double rangeMin, double rangeMax);
            static std::string generateTicsList(const std::vector<locatedTicsLabel_t>& tics, bool add);

            static void writeAxisLabel(std::ostream& hFile, const std::string& axisName, const AxisDescriptor& axis);
            static void writeAxisRange(std::ostream& hFile, const std::string& axisName, const AxisDescriptor& axis);
            static void writeAxisTics (std::ostream& hFile, const std::string& axisName, const AxisDescriptor& axis);

        public:
            PlotWithAxes(const std::string& title);
            ~PlotWithAxes();

            virtual void reset();

            const std::unordered_map<AxisType, AxisDescriptor>& getAxes() const;
            void                                                setAxes(const std::unordered_map<AxisType, AxisDescriptor>& newAxes);

            AxisDescriptor&      axis(const AxisType axisID);
            void            clearAxes();
            void            clearAxis(const AxisType axisID);

            AxisDescriptor&         xAxis();
            AxisDescriptor&         yAxis();

            bool                    getPolar() const;
            void                    setPolar(bool newPolar);

            template<class T>
            DataView2DCompound<T>&  addDataViewCompound(DataView2DCompound<T>* dataView);
            template<class T>
            DataView2DCompound<T>&  addDataViewCompound(const PlotStyle2D style = PlotStyle2D::Lines, const std::string& label = "");
            template<class T>
            DataView2DCompound<T>&  addDataViewCompound(const std::span<T>& data, const DataSelector_t<T>& selectorY, const PlotStyle2D style = PlotStyle2D::Lines, const std::string& label = "");
            template<class T>
            DataView2DCompound<T>&  addDataViewCompound(T* data, const size_t N, const DataSelector_t<T>& selectorY, const PlotStyle2D style = PlotStyle2D::Lines, const std::string& label = "");
            template<class T>
            DataView2DCompound<T>&  addDataViewCompound(const std::string& func, const PlotStyle2D style = PlotStyle2D::Lines, const std::string& label = "");

            // -------------------------------------------------------------- //
            // writers

            virtual void preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const;

            virtual void writeTxtData       (std::ostream& hFile) const;

            virtual void writeDatData() const;

            virtual void writeScriptHead    (std::ostream& hFile) const;
            virtual void writeScriptData    (std::ostream& hFile, const StylesCollection& stylesColloction) const;  //! @todo detect 3d mode: plot ~> splot
            virtual void writeScriptFooter  (std::ostream& hFile, int pageNum) const;               //! @todo tidy up axes

            void writeAxisDescriptor(std::ostream& hFile, const AxisDescriptor& axis) const;
    };
}

#include "plotwithaxes.txx"
#endif // PLOT_WITH_AXES_H
