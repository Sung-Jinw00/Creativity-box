#ifndef EARTH_HPP
# define EARTH_HPP

# include "AAstre.hpp"

# define EARTH_DIAMETER    12742.0
# define EARTH_MASS        5.97237e24

class Earth : public AAstre
{
public:
	Earth() : AAstre(
        "Earth", COLOR_EARTH, GRAVITY_EARTH, MOON_EARTH,
        MASS_EARTH, DIAMETER_EARTH, WIND_EARTH, TEMP_EARTH,
        ORBITAL_SPEED_EARTH, ROTATION_EARTH
    ) {}
	~Earth() {}
};

#endif
