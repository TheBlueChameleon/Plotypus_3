#ifndef PLOT_H
#define PLOT_H

#include <vector>

#include "../definitions/types.h"
#include "../definitions/styles.h"
#include "../base/sheet.h"

namespace Plotypus
{
    class Plot : public Sheet
    {
        private:

        public:
            Plot(const std::string& title);
    };

}
#endif // PLOT_H
