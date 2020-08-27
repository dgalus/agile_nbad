#include "standeal.h"

Standeal::Standeal()
{ }

template<typename T>
inline
double Standeal::m_simple_exp_smoothing(std::vector<T> series, double alpha)
{
    std::vector<double> result;
    result.push_back(series.at(0));
    for (auto it = series.begin() + 1; it < series.end(); it++)
    {
        result.push_back(
            alpha * (*it) + (1 - alpha) * (*result.rbegin())
        );
    }
    return *result.rbegin();
}

template<typename T>
inline
T Standeal::m_get_biggest_increase_in_window(std::vector<T> series)
{
    T inc = 0;
    for (auto it = series.begin(); it < series.end()-1; it++)
        if ((*(it+1)) - (*it) > inc)
            inc = (*(it+1)) - (*it);
    return inc;
}

inline
double Standeal::m_sigmoid(double a, double b, double x)
{
    try {
        return 1. / (1 + std::exp(-1 * a * (x - b)));
    } catch(std::exception ex) {
        return 0;
    }
}