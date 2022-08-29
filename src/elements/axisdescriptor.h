#ifndef AXISDESCRIPTOR_H
#define AXISDESCRIPTOR_H

namespace Plotypus
{
    /**
     * @brief used to compactly describe an axis of a plot
     */

    struct AxisDescriptor
    {
        public:
            using locatedTicsLabel_t = std::pair<std::string, double>;

        private:
            AxisType                        type;

            std::optional<std::string>      labelText;
            std::optional<std::string>      labelFont;
            std::optional<std::string>      labelColor;
            std::optional<std::string>      labelOptions;

            std::optional<double>           rangeMin            = 0.;
            std::optional<double>           rangeMax;
            std::optional<std::string>      rangeOptions;

            bool                            tics                = true;
            bool                            ticsAuto            = true;
            std::optional<double>           ticsStart;
            std::optional<double>           ticsEnd;
            std::optional<double>           ticsIncrement;
            std::optional<std::string>      ticsFormatstring;
            std::vector<locatedTicsLabel_t> ticsLabels;
            bool                            ticsLogscale        = false;
            std::optional<std::string>      ticsFont;
            std::optional<std::string>      ticsTextColor;
            std::optional<std::string>      ticsOptions;

            bool                            minorTics           = false;
            std::optional<size_t>           minorTicsIntervals;

            bool                            gridMajor;
            std::optional<std::string>      gridMajorOptions;
            bool                            gridMinor;
            std::optional<std::string>      gridMinorOptions;

            std::string generateRangeString (const std::optional<double>& min, const std::optional<double>& max) const;
            std::string generateTicsSequence(const std::optional<double>& min, const std::optional<double>& increment, const std::optional<double>& max,
                                             const std::optional<double>& rangeMin, const std::optional<double>& rangeMax) const;
            std::string generateTicsList    (const std::vector<AxisDescriptor::locatedTicsLabel_t>& tics, bool add) const;

            void writeAxisLabel (std::ostream& hFile, const std::string& axisName) const;
            void writeAxisRange (std::ostream& hFile, const std::string& axisName) const;
            void writeAxisTics  (std::ostream& hFile, const std::string& axisName) const;
            void writeAxisGrid  (std::ostream& hFile, const std::string& axisName, bool off = false) const;

        public:
            AxisDescriptor();       //! @todo make construct undefined axis
            AxisDescriptor(const AxisType type,                           double rangeMin = OPTIONAL_DOUBLE_DEFAULT, double rangeMax = OPTIONAL_DOUBLE_DEFAULT);
            AxisDescriptor(const AxisType type, const std::string& label, double rangeMin = OPTIONAL_DOUBLE_DEFAULT, double rangeMax = OPTIONAL_DOUBLE_DEFAULT);

            std::string     getLabelText() const;
            AxisDescriptor& setLabelText(const std::string& newLabelText);
            AxisDescriptor& clearLabelText();

            std::string     getLabelFont() const;
            AxisDescriptor& setLabelFont(const std::string& newLabelFont);
            AxisDescriptor& clearLabelFont();

            std::string     getLabelColor() const;
            AxisDescriptor& setLabelColor(const std::string& newLabelColor);
            AxisDescriptor& clearLabelColor();

            std::string     getLabelOptions() const;
            AxisDescriptor& setLabelOptions(const std::string& newLabelOptions);
            AxisDescriptor& clearLabelOptions();

            double          getRangeMin() const;
            AxisDescriptor& setRangeMin(double newRangeMin);
            AxisDescriptor& clearRangeMin();

            double          getRangeMax() const;
            AxisDescriptor& setRangeMax(double newRangeMax);
            AxisDescriptor& clearRangeMax();

            std::string     getRangeOptions() const;
            AxisDescriptor& setRangeOptions(const std::string& newRangeOptions);
            AxisDescriptor& clearRangeOptions();

            bool            getTics() const;
            AxisDescriptor& setTics(bool newTics);

            bool            getTicsAuto() const;
            AxisDescriptor& setTicsAuto(bool newTicsAuto);

            double          getTicsStart() const;
            AxisDescriptor& setTicsStart(double newTicsStart);
            AxisDescriptor& clearTicsStart();

            double          getTicsEnd() const;
            AxisDescriptor& setTicsEnd(double newTicsEnd);
            AxisDescriptor& clearTicsEnd();

            double          getTicsIncrement() const;
            AxisDescriptor& setTicsIncrement(double newTicsIncrement);
            AxisDescriptor& clearTicsIncrement();

            std::string     getTicsFormatstring() const;
            AxisDescriptor& setTicsFormatstring(const std::string& newTicsFormatstring);
            AxisDescriptor& clearTicsFormatstring();

            const std::vector<locatedTicsLabel_t>& getTicsLabels() const;
            AxisDescriptor& setTicsLabels(const std::vector<locatedTicsLabel_t>& newTicsLabels);
            AxisDescriptor& clearTicsLabels();

            bool            getTicsLogscale() const;
            AxisDescriptor& setTicsLogscale(bool newTicsLogscale);

            std::string     getTicsFont() const;
            AxisDescriptor& setTicsFont(const std::string& newTicsFont);
            AxisDescriptor& clearTicsFont();

            std::string     getTicsOptions() const;
            AxisDescriptor& setTicsOptions(const std::string& newTicsOptions);
            AxisDescriptor& clearTicsOptions();

            bool            getMinorTics() const;
            AxisDescriptor& setMinorTics(bool newMinorTics);

            size_t          getMinorTicsIntervals() const;
            AxisDescriptor& setMinorTicsIntervals(size_t newMinorTicsIntervals);
            AxisDescriptor& clearMinorTicsIntervals();

            bool            getGridMajor() const;
            AxisDescriptor& setGridMajor(bool newGridMajor);

            std::string     getGridMajorOptions() const;
            AxisDescriptor& setGridMajorOptions(const std::string& newGridMajorOptions);
            AxisDescriptor& clearGridMajorOptions();

            bool            getGridMinor() const;
            AxisDescriptor& setGridMinor(bool newGridMinor);

            std::string     getGridMinorOptions() const;
            AxisDescriptor& setGridMinorOptions(const std::string& newGridMinorOptions);
            AxisDescriptor& clearGridMinorOptions();

            // -------------------------------------------------------------- //
            // writers

            void writeAxisDescriptor(std::ostream& hFile) const;
            void writeUnsetCommands (std::ostream& hFile) const;
    };
}

#endif // AXISDESCRIPTOR_H
