#ifndef STANDEAL_H_
#define STANDEAL_H_

// Statistical Anomaly Detection Algorithm

#include <cmath>
#include <vector>

#include "bounded_value.h"

class Standeal
{
public:
    Standeal();
    void set_season_length(PositiveInt _season_length);
    void set_window_size(PositiveInt _window_size);
    void set_sigmoid_threshold(ZeroToOneCoefficient _sigmoid_threshold);
    void set_alpha(ZeroToOneCoefficient _alpha);

private:
    template<typename T>
    inline double m_simple_exp_smoothing(std::vector<T> series, double alpha);
    template<typename T>
    inline T m_get_biggest_increase_in_window(std::vector<T> series);
    inline double m_sigmoid(double a, double b, double x);

    PositiveInt season_length;
    PositiveInt window_size;
    ZeroToOneCoefficient sigmoid_threshold;
    ZeroToOneCoefficient alpha;
};

#endif