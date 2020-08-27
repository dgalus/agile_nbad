#ifndef BOUNDED_VALUE_H_
#define BOUNDED_VALUE_H_

#include <limits>
#include <stdexcept>
#include <sstream>
#include <iostream>

template<typename T, T Vmin, T Vmax>
struct BoundedValue
{
    T value;

    BoundedValue() = delete;

    BoundedValue(T value)
    {
        if(value < Vmin || value > Vmax)
            throw std::range_error(
                "Value must be greater than or equal to "
                + std::to_string(Vmin)
                + " and less then or equal to "
                + std::to_string(Vmax) + "."
            );
        this->value = value;
    }

    operator T() const {
        return this->value;
    }
};

typedef BoundedValue<unsigned int, 0, std::numeric_limits<unsigned int>::max()> PositiveInt;

struct ZeroToOneCoefficient
{
	double value;

    ZeroToOneCoefficient() = delete;

	ZeroToOneCoefficient(double value)
	{
		if(value < 0 || value > 1)
            throw std::range_error(
                "Value must be greater than or equal to 0"
                " and less then or equal to 1."
            );
        this->value = value;
	}

	operator double() const {
        return this->value;
    }
};

#endif