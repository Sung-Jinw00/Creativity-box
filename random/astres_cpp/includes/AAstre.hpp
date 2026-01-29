#ifndef AASTRE_HPP
# define AASTRE_HPP

# include <iostream>
# include <iomanip>
# include <exception>

# include "metrics.hpp"

class AAstre
{
private:
	const std::string	_name;
	const std::string	_color;
	double				_gravity;
	int					_moonNb;
	double				_mass;
	double				_diameter;
	double				_windSpeed;
	double				_temperature;
	double				_sunRotationSpeed;
	double				_dayRotationSpeed;

	AAstre();
public:
	AAstre(const std::string& name, const std::string& color,
	   double gravity, int moonNb, double mass, double diameter,
	   double windSpeed, double temperature,
	   double sunRotationSpeed, double dayRotationSpeed);
	AAstre(const AAstre& other);
	AAstre& operator=(const AAstre &astre);
	virtual ~AAstre() = 0;

	class InvalidDiameterException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class InvalidMassException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class InvalidGravityException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class InvalidMoonNbException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class InvalidWindSpeedException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class InvalidTemperatureException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class InvalidRotationException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class InvalidDayRotationException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

		// Getters pour accéder aux propriétés
	std::string	getName() const;
	std::string	getColor() const;
	double		getGravity() const;
	int			getMoonNb() const;
	double		getMass() const;
	double		getDiameter() const;
	double		getWindSpeed() const;
	double		getTemperature() const;
	double		getSunRotationSpeed() const;
	double		getDayRotationSpeed() const;

	// Getter pour afficher le nom avec sa couleur
	virtual std::string getColoredName() const;

};

std::ostream& operator<<(std::ostream& os, AAstre &astre);

#endif