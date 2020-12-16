#pragma once

struct Transition
{
    Transition() = default;
    Transition(double value, double threshold);

    void update();
    double get() const;

    double value;
    double threshold;
private:
    double at;
};
