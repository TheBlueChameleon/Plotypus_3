#ifndef SHOWCASE_H
#define SHOWCASE_H

enum Showcases
{
    Overlays = 1 << 0,
    Plots_2D = 1 << 1,

    All = -1,
};

void showcase_run(Showcases selection);

void showcase_all();
void showcase_overlays();
void showcase_2D_plots();

#endif // SHOWCASE_H
