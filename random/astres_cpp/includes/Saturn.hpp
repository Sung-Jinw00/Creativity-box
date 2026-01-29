#ifndef SATURN_HPP
# define SATURN_HPP

# include "AAstre.hpp"

# define SATURN_DIAMETER   116460.0
# define SATURN_MASS       5.6834e26

class Saturn : public AAstre
{
public:
	Saturn() : AAstre(
        "Saturn", COLOR_SATURN, GRAVITY_SATURN, MOON_SATURN,
        MASS_SATURN, DIAMETER_SATURN, WIND_SATURN, TEMP_SATURN,
        ORBITAL_SPEED_SATURN, ROTATION_SATURN
    ) {}
	~Saturn() {}
};

#endif
