#ifndef MERCURY_HPP
# define MERCURY_HPP

# include "AAstre.hpp"

# define MERCURY_DIAMETER  4879.0
# define MERCURY_MASS      3.3011e23

class Mercury : public AAstre
{
public:
	Mercury() : AAstre(
        "Mercury", COLOR_MERCURY, GRAVITY_MERCURY, MOON_MERCURY,
        MASS_MERCURY, DIAMETER_MERCURY, WIND_MERCURY, TEMP_MERCURY,
        ORBITAL_SPEED_MERCURY, ROTATION_MERCURY
    ) {}
	~Mercury() {}
};

#endif
