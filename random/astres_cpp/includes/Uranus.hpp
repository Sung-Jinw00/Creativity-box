/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   URANUS.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:10:33 by marvin            #+#    #+#             */
/*   Updated: 2025/09/18 22:43:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef URANUS_HPP
# define URANUS_HPP

# include "AAstre.hpp"

# define URANUS_DIAMETER   50724.0
# define URANUS_MASS       8.6810e25

class Uranus : public AAstre
{
public:
	Uranus() : AAstre(
        "Uranus", COLOR_URANUS, GRAVITY_URANUS, MOON_URANUS,
        MASS_URANUS, DIAMETER_URANUS, WIND_URANUS, TEMP_URANUS,
        ORBITAL_SPEED_URANUS, ROTATION_URANUS
    ) {}
	~Uranus() {}
};

#endif
