#ifndef NEPTUNE_HPP
# define NEPTUNE_HPP

# include "AAstre.hpp"

# define NEPTUNE_DIAMETER  49244.0
# define NEPTUNE_MASS      1.02413e26

class Neptune : public AAstre
{
public:
	Neptune() : AAstre(
        "Neptune", COLOR_NEPTUNE, GRAVITY_NEPTUNE, MOON_NEPTUNE,
        MASS_NEPTUNE, DIAMETER_NEPTUNE, WIND_NEPTUNE, TEMP_NEPTUNE,
        ORBITAL_SPEED_NEPTUNE, ROTATION_NEPTUNE
    ) {}
	~Neptune() {}
};

#endif
