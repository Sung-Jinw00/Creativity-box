/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:43:49 by marvin            #+#    #+#             */
/*   Updated: 2025/09/22 16:23:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SolarSystem.hpp"
#include "Compare.hpp"

int main(void)
{
	try
	{
		SolarSystem system;

		system.addAstre(new Sun());
		system.addAstre(new Mercury());
		system.addAstre(new Venus());
		system.addAstre(new Earth());
		system.addAstre(new Mars());
		system.addAstre(new Jupiter());
		system.addAstre(new Saturn());
		system.addAstre(new Uranus());
		system.addAstre(new Neptune());

		system.display();
		std::cout << std::endl;

		system.sortBy(LABEL_MASS);

		system.sortBy(LABEL_DIAMETER);

		system.sortBy(LABEL_TEMPERATURE);
		
		system.sortBy(LABEL_GRAVITY);

		system.sortBy(LABEL_MOONS);

		Sun sun;
		Earth earth;

		compareAllValues(sun, earth);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
