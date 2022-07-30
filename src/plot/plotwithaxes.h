#ifndef PLOT_WITH_AXES_H
#define PLOT_WITH_AXES_H

#include <fstream>
#include <span>
#include <string>
#include <vector>

#include "../dataview/dataview2dcompound.h"

#include "plot.h"

namespace Plotypus
{
    class PlotWithAxes : public Plot
    {
        protected:
            AxisDescriptor          m_xAxis = AxisDescriptor("x");
            AxisDescriptor          m_yAxis = AxisDescriptor("y");

            bool                    polar = false;

            static std::string generateRangeString (double min,                   double max);
            static std::string generateTicsSequence(double min, double increment, double max, double rangeMin, double rangeMax);
            static std::string generateTicsList(const std::vector<locatedTicsLabel_t>& tics, bool add);

        public:
            PlotWithAxes(const std::string& title);
            ~PlotWithAxes();

            virtual void reset();

            AxisDescriptor&     xAxis();
            AxisDescriptor&     yAxis();

            bool                getPolar() const;
            void                setPolar(bool newPolar);

            template<class T>
            DataView2DCompound<T>& addDataViewCompound(DataView2DCompound<T>* dataView);
            template<class T>
            DataView2DCompound<T>& addDataViewCompound(const PlotStyle2D style = PlotStyle2D::Lines, const std::string& label = "");
            template<class T>
            DataView2DCompound<T>& addDataViewCompound(const std::span<T>& data, const DataSelector_t<T>& selectorY, const PlotStyle2D style = PlotStyle2D::Lines, const std::string& label = "");
            template<class T>
            DataView2DCompound<T>& addDataViewCompound(T* data, const size_t N, const DataSelector_t<T>& selectorY, const PlotStyle2D style = PlotStyle2D::Lines, const std::string& label = "");
            template<class T>
            DataView2DCompound<T>& addDataViewCompound(const std::string& func, const PlotStyle2D style = PlotStyle2D::Lines, const std::string& label = "");

            // -------------------------------------------------------------- //
            // writers

            virtual void preprocessSheet(const std::string& autoDataFilename, const std::string& extension) const;

            virtual void writeTxtData       (std::ostream& hFile) const;

            virtual void writeDatData() const;

            virtual void writeScriptHead    (std::ostream& hFile) const;
            virtual void writeScriptData    (std::ostream& hFile, const StylesCollection& stylesColloction) const;
            virtual void writeScriptFooter  (std::ostream& hFile, int pageNum) const;

            void writeAxisDescriptor(std::ostream& hFile, const std::string& axis, const AxisDescriptor& label) const;
    };
}

#include "plotwithaxes.txx"
#endif // PLOT_WITH_AXES_H
