#ifndef JUPITER_HPP
# define JUPITER_HPP

# include "AAstre.hpp"

# define JUPITER_DIAMETER  139820.0
# define JUPITER_MASS      1.8982e27

class Jupiter : public AAstre
{
public:
	Jupiter() : AAstre(
        "Jupiter", COLOR_JUPITER, GRAVITY_JUPITER, MOON_JUPITER,
        MASS_JUPITER, DIAMETER_JUPITER, WIND_JUPITER, TEMP_JUPITER,
        ORBITAL_SPEED_JUPITER, ROTATION_JUPITER
    ) {}
	~Jupiter() {}
};

#endif
