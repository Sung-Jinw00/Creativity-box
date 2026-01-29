#ifndef MARS_HPP
# define MARS_HPP

# include "AAstre.hpp"

# define MARS_DIAMETER     6779.0
# define MARS_MASS         6.4171e23

class Mars : public AAstre
{
public:
	Mars() : AAstre(
        "Mars", COLOR_MARS, GRAVITY_MARS, MOON_MARS,
        MASS_MARS, DIAMETER_MARS, WIND_MARS, TEMP_MARS,
        ORBITAL_SPEED_MARS, ROTATION_MARS
    ) {}
	~Mars() {}
};

#endif
