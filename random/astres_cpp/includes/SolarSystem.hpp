/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SolarSystem.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:50:04 by marvin            #+#    #+#             */
/*   Updated: 2025/09/22 16:32:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLARSYSTEM_HPP
# define SOLARSYSTEM_HPP

# include "Sun.hpp"
# include "Mercury.hpp"
# include "Venus.hpp"
# include "Earth.hpp"
# include "Mars.hpp"
# include "Jupiter.hpp"
# include "Saturn.hpp"
# include "Uranus.hpp"
# include "Neptune.hpp"

# include <vector>
# include <memory>
# include <algorithm>

# define PRINT_SORTED(getter, unit) \
	for (std::vector<AAstre*>::iterator it = astres.begin(); it != astres.end(); ++it) \
	{ \
		AAstre* a = *it; \
		std::ios oldState(NULL); \
        oldState.copyfmt(std::cout); \
		if (label == LABEL_TEMPERATURE) \
		{ \
			std::cout << a->getColoredName() << CYAN " : " RESET \
					  << std::fixed << std::setprecision(0) \
					  << a->getter() << " " unit "\n"; \
		} \
		else \
		{ \
			std::cout << a->getColoredName() << CYAN " : " RESET \
					  << a->getter() << " " unit "\n"; \
		} \
		std::cout.copyfmt(oldState); \
	}

# define LABEL_DIAMETER      "diameter"
# define LABEL_MASS          "mass"
# define LABEL_GRAVITY       "gravity"
# define LABEL_MOONS         "moons"
# define LABEL_WIND_SPEED    "wind speed"
# define LABEL_TEMPERATURE   "temperature"
# define LABEL_ORBIT_SPEED   "orbit speed"
# define LABEL_DAY_ROTATION  "day of rotation"

class SolarSystem
{
private:
	std::vector<AAstre*> astres;

public:
	SolarSystem()
	{}
	~SolarSystem()
	{
		for (size_t i = 0; i < astres.size(); ++i)
			delete astres[i];
		astres.clear(); // facultatif, pour vider le vector
	}

	// Ajouter un astre
	void addAstre(AAstre* astre)
	{
		astres.push_back(astre);
	}

	// Afficher tous les astres
	void display() const
	{
		for (size_t i = 0; i < astres.size(); ++i)
		{
			std::cout << "==============\n"
					<< astres[i]->getColoredName()
					<< CYAN "\nDiameter : " RESET << std::setprecision(3) << astres[i]->getDiameter() << " km"
					<< CYAN "\nMass : " RESET << std::setprecision(3) << astres[i]->getMass() << " kg"
					<< CYAN "\nGravity : " RESET << std::setprecision(2) << astres[i]->getGravity() << " G"
					<< CYAN "\nMoons : " RESET << astres[i]->getMoonNb()
					<< CYAN "\nWind speed : " RESET << std::setprecision(1) << astres[i]->getWindSpeed() << " km/h"
					<< CYAN "\nTemperature : " RESET << std::setprecision(1) << astres[i]->getTemperature() << " °C"
					<< CYAN "\nOrbital speed : " RESET << std::setprecision(2) << astres[i]->getSunRotationSpeed() << " km/s"
					<< CYAN "\nDay length : " RESET << std::setprecision(2) << astres[i]->getDayRotationSpeed() << " h\n"
					<< RESET << std::endl;
		}
	}

	static bool compareDiameter(AAstre* a, AAstre* b)
	{
		return a->getDiameter() > b->getDiameter();
	}

	static bool compareMass(AAstre* a, AAstre* b)
	{
		return a->getMass() > b->getMass();
	}

	static bool compareGravity(AAstre* a, AAstre* b)
	{
		return a->getGravity() > b->getGravity();
	}

	static bool compareMoonNb(AAstre* a, AAstre* b)
	{
		return a->getMoonNb() > b->getMoonNb();
	}

	static bool compareWindSpeed(AAstre* a, AAstre* b)
	{
		return a->getWindSpeed() > b->getWindSpeed();
	}

	static bool compareTemperature(AAstre* a, AAstre* b)
	{
		return a->getTemperature() > b->getTemperature();
	}

	static bool compareOrbitSpeed(AAstre* a, AAstre* b)
	{
		return a->getSunRotationSpeed() > b->getSunRotationSpeed();
	}

	static bool compareDayRotation(AAstre* a, AAstre* b)
	{
		return a->getDayRotationSpeed() > b->getDayRotationSpeed();
	}

	void sortBy(std::string label)
	{
		for (size_t i = 0; i < label.size(); ++i)
			label[i] = std::tolower(label[i]);

		std::cout << "=== sort by " << label << " ===\n";

		if (label == LABEL_DIAMETER)
		{
			std::sort(astres.begin(), astres.end(), compareDiameter);
			PRINT_SORTED(getDiameter, "km");
		}
		else if (label == LABEL_MASS)
		{
			std::sort(astres.begin(), astres.end(), compareMass);
			PRINT_SORTED(getMass, "kg");
		}
		else if (label == LABEL_GRAVITY)
		{
			std::sort(astres.begin(), astres.end(), compareGravity);
			PRINT_SORTED(getGravity, "G");
		}
		else if (label == LABEL_MOONS)
		{
			std::sort(astres.begin(), astres.end(), compareMoonNb);
			PRINT_SORTED(getMoonNb, "moons");
		}
		else if (label == LABEL_WIND_SPEED)
		{
			std::sort(astres.begin(), astres.end(), compareWindSpeed);
			PRINT_SORTED(getWindSpeed, "km/h");
		}
		else if (label == LABEL_TEMPERATURE)
		{
			std::sort(astres.begin(), astres.end(), compareTemperature);
			PRINT_SORTED(getTemperature, "°C");
		}
		else if (label == LABEL_ORBIT_SPEED)
		{
			std::sort(astres.begin(), astres.end(), compareOrbitSpeed);
			PRINT_SORTED(getSunRotationSpeed, "km/s");
		}
		else if (label == LABEL_DAY_ROTATION)
		{
			std::sort(astres.begin(), astres.end(), compareDayRotation);
			PRINT_SORTED(getDayRotationSpeed, "hours");
		}
		else
			std::cerr << RED "Unknown label : " << label << RESET << std::endl;

		std::cout << std::endl;
	}

	const std::vector<AAstre*>& getAstres() const
	{
		return astres;
	}
};

#endif