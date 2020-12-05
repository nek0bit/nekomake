#include "generic.hpp"

double generic::clamp(double value, double min, double max)
{
    return value > max ? max : value < min ? min : value;
}
