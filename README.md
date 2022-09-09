# Plotypus

Plotypus is a C++ frontend for the gnuplot graphing tool. It takes contiguous data sequences of arbitrary format (e.g. std::vector<some_struct>) as input and creates both, data files and gnuplot scripts that visualize these data.
Access to commonly used features are (or will be) faciliated by special calls, enabling you to focus on your simulation.

A not even minimal example:

```
struct datapoint_t {
    double x;
    double y;
    double errY;
};

std::vector<datapoint_t> runSimulation() {
   std::vector<datapoint_t> result;
   
   /* your simulation here */
   
   return result;
}

void writePlotPDF(const std::vector<datapoint_t>& data) {
    Plotypus::Report report = Plotypus::Report(Plotypus::FileType::Pdf);
    
    using compound_selector_t = Plotypus::DataSelector_t<datapoint_t>;
    compound_selector_t compoundSelectorX    = [] (const datapoint_t& datapoint) {return datapoint.x;};
    compound_selector_t compoundSelectorY    = [] (const datapoint_t& datapoint) {return datapoint.y;};
    compound_selector_t compoundSelectorErrY = [] (const datapoint_t& datapoint) {return datapoint.errY;};
    
    auto& sheet1 = report.addPlotOrthogonalAxes("line plot (cartesian)");

    sheet1
        .addDataViewCompound<datapoint_t>(Plotypus::PlotStyle::YErrorLines, "Simulation Result")
        .setData(data)
        .setSelector(Plotypus::ColumnType::X,      compoundSelectorX)
        .setSelector(Plotypus::ColumnType::Y,      compoundSelectorY)
        .setSelector(Plotypus::ColumnType::DeltaY, compoundSelectorErrY);
    
    sheet1.addDataViewCompound<compound_t>("[0:pi] sin(x)", PlotStyle::Lines, "Sine Wave");
    
    sheet1.addLabel("some special symbols: " + SYMBOL_FORALL + SYMBOL_ALPHA + SYMBOL_DOT + "5" + SYMBOL_HBAR, .70, .20);
    
    report.writeDat();
    report.writeScript();
}
```
