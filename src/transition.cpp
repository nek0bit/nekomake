#include "transition.hpp"

Transition::Transition(double value, double threshold)
    : value{value}, threshold{threshold}, at{value}
{}

void Transition::update()
{
    at += (value - at) * threshold;
}

double Transition::get() const
{
    return at;
}
