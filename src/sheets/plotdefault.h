#ifndef PLOTDEFAULT_H
#define PLOTDEFAULT_H

#include <span>
#include <string>
#include <unordered_map>

#include "../elements/axisdescriptor.h"
#include "../dataview/dataviewdefaultcompound.h"

#include "abstractplot.h"

namespace Plotypus
{
    /**
     * @todo set equal xy / xyz
     *
     * @todo cannot splot in polar coordinate system
     *
     * @todo addView(View& other) as add Copy
     *
     * @todo adders with empty label; label alias title?
     *
     * @todo empty title/clear title variants
     */

    class PlotDefault : public AbstractPlot
    {
        protected:
            static constexpr auto allowedStyleFamiles = {PlotStyleFamily::Orthogonal2D, PlotStyleFamily::Orthogonal3D, PlotStyleFamily::Custom};

            bool mode3D = false;
            bool polar  = false;

            std::unordered_map<AxisType, AxisDescriptor> axes;

            DataviewDefaultSeparate&    addDataViewSeparate(DataviewDefaultSeparate* dataView);
            template<class T>
            DataviewDefaultCompound<T>& addDataViewCompound(DataviewDefaultCompound<T>* dataView);

            void abstractToken();

        public:
            PlotDefault();
            PlotDefault(const std::string& title);

            virtual PlotDefault& reset();

            const std::unordered_map<AxisType, AxisDescriptor>& getAxes() const;
            PlotDefault&                                 setAxes(const std::unordered_map<AxisType, AxisDescriptor>& newAxes);

            AxisDescriptor&                  axis(const AxisType axisID);
            PlotDefault&         clearAxes();
            PlotDefault&         clearAxis(const AxisType axisID);

            bool                        getMode3D() const;
            PlotDefault&         setMode3D(bool newMode3D);

            bool                        getPolar() const;
            PlotDefault&         setPolar(bool newPolar);

            DataviewDefaultSeparate&    addDataViewSeparate(                                                                const PlotStyle style = PlotStyle::Lines, const std::string& label = "");
            DataviewDefaultSeparate&    addDataViewSeparate(                                const std::span<double>& dataY, const PlotStyle style = PlotStyle::Lines, const std::string& label = "");
            DataviewDefaultSeparate&    addDataViewSeparate(const std::span<double>& dataX, const std::span<double>& dataY, const PlotStyle style = PlotStyle::Lines, const std::string& label = "");
            DataviewDefaultSeparate&    addDataViewSeparate(const std::string& func,                                        const PlotStyle style = PlotStyle::Lines, const std::string& label = "");

            template<class T>
            DataviewDefaultCompound<T>& addDataViewCompound(                          const PlotStyle style = PlotStyle::Lines, const std::string& label = "");
            template<class T>
            DataviewDefaultCompound<T>& addDataViewCompound(const std::span<T>& data, const PlotStyle style = PlotStyle::Lines, const std::string& label = "");
            template<class T>
            DataviewDefaultCompound<T>& addDataViewCompound(T* data, const size_t N,  const PlotStyle style = PlotStyle::Lines, const std::string& label = "");
            template<class T>
            DataviewDefaultCompound<T>& addDataViewCompound(const std::string& func,  const PlotStyle style = PlotStyle::Lines, const std::string& label = "");

            // -------------------------------------------------------------- //
            // writers

            virtual void writeTxtData       (std::ostream& hFile) const;

            virtual void writeDatData       () const;

            virtual void writeScriptHead    (std::ostream& hFile) const;
            virtual void writeScriptData    (std::ostream& hFile, const StylesCollection& stylesCollection) const;
            virtual void writeScriptFooter  (std::ostream& hFile, int pageNum) const;
    };
}

#include "plotdefault.txx"
#endif // PLOTDEFAULT_H
