/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAstre.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:10:23 by marvin            #+#    #+#             */
/*   Updated: 2025/09/19 01:31:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAstre.hpp"

AAstre::AAstre()
    : _name(""), _color(""), _gravity(0), _moonNb(0),
      _mass(0), _diameter(0), _windSpeed(0), _temperature(0),
      _sunRotationSpeed(0), _dayRotationSpeed(0) {}

AAstre::AAstre(const std::string& name, const std::string& color,
               double gravity, int moonNb, double mass, double diameter,
               double windSpeed, double temperature,
               double sunRotationSpeed, double dayRotationSpeed)
    : _name(name), _color(color), _gravity(gravity), _moonNb(moonNb),
      _mass(mass), _diameter(diameter),
      _windSpeed(windSpeed), _temperature(temperature),
      _sunRotationSpeed(sunRotationSpeed), _dayRotationSpeed(dayRotationSpeed)
{
	if (diameter <= 0)
		throw InvalidDiameterException();
	if (mass <= 0)
		throw InvalidMassException();
	if (gravity < 0)
		throw InvalidGravityException();
	if (moonNb < 0)
		throw InvalidMoonNbException();
	if (windSpeed < 0)
		throw InvalidWindSpeedException();
	if (temperature < ABSOLUTE_ZERO)
		throw InvalidTemperatureException();
	if (sunRotationSpeed < 0)
		throw InvalidRotationException();
	if (!dayRotationSpeed)
		throw InvalidDayRotationException();
}

AAstre::AAstre(const AAstre &other)
{
	*this = other;
}

AAstre& AAstre::operator=(const AAstre &astre)
{
	if (this != &astre)
	{
		this->_diameter = astre._diameter;
		this->_mass = astre._mass;
	}
	return *this;
}

AAstre::~AAstre() {}

const char* AAstre::InvalidGravityException::what() const throw()
{
	return RED "Gravity cannot be negative !" RESET;
}

const char* AAstre::InvalidMoonNbException::what() const throw()
{
	return RED "Number of moons cannot be negative !" RESET;
}

const char* AAstre::InvalidWindSpeedException::what() const throw()
{
	return RED "Wind speed cannot be negative !" RESET;
}

const char* AAstre::InvalidTemperatureException::what() const throw()
{
	return RED "Temperature cannot be below absolute zero !" RESET;
}

const char* AAstre::InvalidRotationException::what() const throw()
{
	return RED "Rotation speed cannot be negative !" RESET;
}

const char* AAstre::InvalidDayRotationException::what() const throw()
{
	return RED "Day rotation speed must be positive !" RESET;
}

std::string	AAstre::getColoredName(void) const
{
	return _color + _name + RESET;
}

std::string AAstre::getName() const
{
	return _name;
}

std::string AAstre::getColor() const
{
	return _color;
}

double AAstre::getGravity() const
{
	return _gravity;
}

int AAstre::getMoonNb() const
{
	return _moonNb;
}

double AAstre::getMass() const
{
	return _mass;
}

double AAstre::getDiameter() const
{
	return _diameter;
}

double AAstre::getWindSpeed() const
{
	return _windSpeed;
}

double AAstre::getTemperature() const
{
	return _temperature;
}

double AAstre::getSunRotationSpeed() const
{
	return _sunRotationSpeed;
}

double AAstre::getDayRotationSpeed() const
{
	return _dayRotationSpeed;
}

const char* AAstre::InvalidDiameterException::what() const throw()
{
    return RED "Diameter has to be positive !" RESET;
}

const char* AAstre::InvalidMassException::what() const throw()
{
    return RED "Mass has to be positive !" RESET;
}


std::ostream& operator<<(std::ostream& os, AAstre &astre)
{
	os << astre.getColoredName() << " details:\n"
	   << BRIGHT_CYAN "  Diameter      : " RESET << std::fixed << std::setprecision(1) << astre.getDiameter() << " km\n"
	   << BRIGHT_CYAN "  Mass          : " RESET << std::scientific << std::setprecision(3) << astre.getMass() << " kg\n"
	   << BRIGHT_CYAN "  Gravity       : " RESET << std::fixed << std::setprecision(2) << astre.getGravity() << " G\n"
	   << BRIGHT_CYAN "  Moons         : " RESET << astre.getMoonNb() << "\n"
	   << BRIGHT_CYAN "  Wind Speed    : " RESET << astre.getWindSpeed() << " km/h\n"
	   << BRIGHT_CYAN "  Temperature   : " RESET << astre.getTemperature() << " °C\n"
	   << BRIGHT_CYAN "  Orbit Speed   : " RESET << astre.getSunRotationSpeed() << " km/s\n"
	   << BRIGHT_CYAN "  Day Rotation  : " RESET << astre.getDayRotationSpeed() << " hours\n";

	return os;
}
