#ifndef COMPARE_UTILS_HPP
# define COMPARE_UTILS_HPP

# include "AAstre.hpp"
# include <string>

double	division(const double &v1, const double &v2)
{
	if (!v1)
		return v2;
	else if (!v2)
		return v1;
	else
		return std::abs(v1 / v2);
}

void compareValues(const std::string &Astre1,
				const std::string &Astre2,
				const double &v1,
				const double &v2,
				const std::string &label,
				const std::string &message)
{
    std::cout << std::fixed << std::setprecision(1);

    if (v1 < v2)
        std::cout << Astre2 << CYAN " has" << label << " " << division(v2, v1) << message << Astre1 << CYAN "." RESET;
    else if (v1 > v2)
        std::cout << Astre1 << CYAN " has" << label << " " << division(v1, v2) << message << Astre2 << CYAN "." RESET;
    else
        std::cout << Astre1 << CYAN " and " << Astre2 << CYAN " have the same " << label << "." RESET ;
    std::cout << std::endl;
}

void compareTemperature(const AAstre &astre1, const AAstre &astre2)
{
    double diff = astre1.getTemperature() - astre2.getTemperature();
    std::cout << std::fixed << std::setprecision(0);
    
    if (diff > 0)
        std::cout << astre1.getColoredName() << CYAN " is " << diff 
                  << "°C hotter than " << astre2.getColoredName() << CYAN "." RESET << std::endl;
    else if (diff < 0)
        std::cout << astre2.getColoredName() << CYAN " is " << -diff 
                  << "°C hotter than " << astre1.getColoredName() << CYAN "." RESET << std::endl;
    else
        std::cout << astre1.getColoredName() << CYAN " and " << astre2.getColoredName() 
                  << CYAN " have the same temperature." RESET << std::endl;
}

void compareAllValues(const AAstre &astre1, const AAstre &astre2)
{
    std::cout << "\n=== Comparing " << astre1.getColoredName() 
              << " and " << astre2.getColoredName() << " ===\n";
    compareValues(astre1.getColoredName(), astre2.getColoredName(),
                  astre1.getDiameter(), astre2.getDiameter(), " a diameter (km)", " times bigger than ");
    compareValues(astre1.getColoredName(), astre2.getColoredName(),
                  astre1.getMass(), astre2.getMass(), " a mass (kg)", " times bigger than ");
    compareValues(astre1.getColoredName(), astre2.getColoredName(),
                  astre1.getGravity(), astre2.getGravity(), " a gravity (G)", " times heavier than ");
    compareValues(astre1.getColoredName(), astre2.getColoredName(),
                  astre1.getMoonNb(), astre2.getMoonNb(), "", " more moons than ");
    compareValues(astre1.getColoredName(), astre2.getColoredName(),
                  astre1.getWindSpeed(), astre2.getWindSpeed(), " a wind speed (km/h)", " times faster than ");
    compareTemperature(astre1, astre2);
    compareValues(astre1.getColoredName(), astre2.getColoredName(),
                  astre1.getSunRotationSpeed(), astre2.getSunRotationSpeed(), " an orbit speed (km/s)", " times faster than ");
    compareValues(astre1.getColoredName(), astre2.getColoredName(),
                  astre1.getDayRotationSpeed(), astre2.getDayRotationSpeed(), " a day of rotation (hours)", " times faster than ");
}

#endif
