#ifndef SHOWCASE_H
#define SHOWCASE_H

enum Showcases
{
    Overlays        = 1 << 0,
    Plots_2D        = 1 << 1,
    Plots_2D_maps   = 1 << 2,

    All             = -1,
};

void showcase_run(Showcases selection);

#endif // SHOWCASE_H
