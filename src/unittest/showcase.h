#ifndef SHOWCASE_H
#define SHOWCASE_H

enum Showcases
{
    Overlays        = 1 << 0,
    Plots_2D        = 1 << 1,
    Plots_2D_maps   = 1 << 2,
    Plots_Multiplot = 1 << 3,
    Plots_3D        = 1 << 4,

    All             = -1,
};

void showcase_run(Showcases selection);

#endif // SHOWCASE_H
