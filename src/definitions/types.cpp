#include "types.h"

namespace Plotypus
{
    AxisDescriptor::AxisDescriptor() :
        type(AxisType::X)
    {}

    AxisDescriptor::AxisDescriptor(const AxisType type, const std::string& label, double rangeMin, double rangeMax) :
        type(type), labelText(label),
        rangeMin(rangeMin), rangeMax(rangeMax)
    {
        if (type == AxisType::Azimuthal)
        {
            // *INDENT-OFF*
            if (std::isnan(rangeMin)) {this->rangeMin =   0.;}
            if (std::isnan(rangeMax)) {this->rangeMax = 360.;}
            // *INDENT-ON*
        }
    }

    AxisDescriptor::AxisDescriptor(const AxisType type, double rangeMin, double rangeMax) :
        type(type), rangeMin(rangeMin), rangeMax(rangeMax)
    {
        switch (type)
        {
            case AxisType::Azimuthal:
                // *INDENT-OFF*
                if (std::isnan(rangeMin)) {this->rangeMin =   0.;}
                if (std::isnan(rangeMax)) {this->rangeMax = 360.;}
                // *INDENT-ON*
                break;
            case AxisType::Colourbar:
                labelText = "z";
                break;
            case AxisType::Radial:
                labelText = "r";
                break;
            case AxisType::X:
                labelText = "x";
                break;
            case AxisType::X2:
                labelText = "x";
                break;
            case AxisType::Y:
                labelText = "y";
                break;
            case AxisType::Y2:
                labelText = "y";
                break;
            case AxisType::Z:
                labelText = "z";
                break;
        }
    }

};
