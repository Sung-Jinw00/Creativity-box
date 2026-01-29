/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Venus.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:10:33 by marvin            #+#    #+#             */
/*   Updated: 2025/09/19 01:17:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VENUS_HPP
# define VENUS_HPP

# include "AAstre.hpp"

# define VENUS_DIAMETER    12104.0
# define VENUS_MASS        4.8675e24

class Venus : public AAstre
{
public:
	Venus() : AAstre(
        "Venus", COLOR_VENUS, GRAVITY_VENUS, MOON_VENUS,
        MASS_VENUS, DIAMETER_VENUS, WIND_VENUS, TEMP_VENUS,
        ORBITAL_SPEED_VENUS, ROTATION_VENUS
    ) {}
	~Venus() {}
};

#endif
