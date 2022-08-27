#ifndef PLOTORTHOGONALAXES_H
#define PLOTORTHOGONALAXES_H

#include <span>
#include <string>
#include <unordered_map>

#include "../dataview/dataviewdefaultcompound.h"

#include "plot.h"

namespace Plotypus
{
    /**
     * @todo set equal xy / xyz
     */

    class PlotOrthogonalAxes : public Plot
    {
        protected:
            static constexpr auto allowedStyleFamiles = {PlotStyleFamily::Orthogonal2D, PlotStyleFamily::Orthogonal3D, PlotStyleFamily::Custom};

            std::unordered_map<AxisType, AxisDescriptor> axes;

            bool mode3D = false;
            bool polar  = false;

            static std::string generateRangeString (double min,                   double max);
            static std::string generateTicsSequence(double min, double increment, double max, double rangeMin, double rangeMax);
            static std::string generateTicsList(const std::vector<locatedTicsLabel_t>& tics, bool add);

            static void writeAxisLabel(std::ostream& hFile, const std::string& axisName, const AxisDescriptor& axis);
            static void writeAxisRange(std::ostream& hFile, const std::string& axisName, const AxisDescriptor& axis);
            static void writeAxisTics (std::ostream& hFile, const std::string& axisName, const AxisDescriptor& axis);

        public:
            PlotOrthogonalAxes(const std::string& title);
            ~PlotOrthogonalAxes();

            virtual PlotOrthogonalAxes& reset();

            const std::unordered_map<AxisType, AxisDescriptor>& getAxes() const;
            PlotOrthogonalAxes&                                 setAxes(const std::unordered_map<AxisType, AxisDescriptor>& newAxes);

            AxisDescriptor&                  axis(const AxisType axisID);
            PlotOrthogonalAxes&         clearAxes();
            PlotOrthogonalAxes&         clearAxis(const AxisType axisID);

            AxisDescriptor&             xAxis();
            AxisDescriptor&             yAxis();

            bool                        getMode3D() const;
            PlotOrthogonalAxes&         setMode3D(bool newMode3D);

            bool                        getPolar() const;
            PlotOrthogonalAxes&         setPolar(bool newPolar);

            DataViewDefaultSeparate&    addDataViewSeparate(DataViewDefaultSeparate* dataView);
            DataViewDefaultSeparate&    addDataViewSeparate(                                                                const PlotStyle style = PlotStyle::Lines, const std::string& label = "");
            DataViewDefaultSeparate&    addDataViewSeparate(                                const std::span<double>& dataY, const PlotStyle style = PlotStyle::Lines, const std::string& label = "");
            DataViewDefaultSeparate&    addDataViewSeparate(const std::span<double>& dataX, const std::span<double>& dataY, const PlotStyle style = PlotStyle::Lines, const std::string& label = "");
            DataViewDefaultSeparate&    addDataViewSeparate(const std::string& func,                                        const PlotStyle style = PlotStyle::Lines, const std::string& label = "");

            template<class T>
            DataViewDefaultCompound<T>& addDataViewCompound(DataViewDefaultCompound<T>* dataView);
            template<class T>
            DataViewDefaultCompound<T>& addDataViewCompound(                                                                const PlotStyle style = PlotStyle::Lines, const std::string& label = "");
            template<class T>
            DataViewDefaultCompound<T>& addDataViewCompound(const std::span<T>& data, const DataSelector_t<T>& selectorY,   const PlotStyle style = PlotStyle::Lines, const std::string& label = "");
            template<class T>
            DataViewDefaultCompound<T>& addDataViewCompound(T* data, const size_t N, const DataSelector_t<T>& selectorY,    const PlotStyle style = PlotStyle::Lines, const std::string& label = "");
            template<class T>
            DataViewDefaultCompound<T>& addDataViewCompound(const std::string& func,                                        const PlotStyle style = PlotStyle::Lines, const std::string& label = "");

            // -------------------------------------------------------------- //
            // writers

            virtual void writeTxtData       (std::ostream& hFile) const;

            virtual void writeDatData       () const;

            virtual void writeScriptHead    (std::ostream& hFile) const;
            virtual void writeScriptData    (std::ostream& hFile, const StylesCollection& stylesColloction) const;
            virtual void writeScriptFooter  (std::ostream& hFile, int pageNum) const;

            static void writeAxisDescriptor(std::ostream& hFile, const AxisDescriptor& axis);
    };
}

#include "plotorthogonalaxes.txx"
#endif // PLOTORTHOGONALAXES_H
