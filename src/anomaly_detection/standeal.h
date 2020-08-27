#ifndef STANDEAL_H_
#define STANDEAL_H_

// Statistical Anomaly Detection Algorithm

#include <cmath>
#include <vector>

class Standeal
{
public:
    Standeal();
private:
    template<typename T>
    inline double m_simple_exp_smoothing(std::vector<T> series, double alpha);
    template<typename T>
    inline T m_get_biggest_increase_in_window(std::vector<T> series);
    inline double m_sigmoid(double a, double b, double x);
};

#endif