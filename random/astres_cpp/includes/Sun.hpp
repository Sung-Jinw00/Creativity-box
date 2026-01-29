/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sun.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 22:44:53 by marvin            #+#    #+#             */
/*   Updated: 2025/09/19 01:42:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUN_HPP
# define SUN_HPP

# include "AAstre.hpp"

# define SUN_DIAMETER   1391400.0
# define SUN_MASS       1.989e30

class Sun : public AAstre
{
public:
	Sun() : AAstre(
        "the Sun", COLOR_SUN, GRAVITY_SUN, MOON_SUN,
        MASS_SUN, DIAMETER_SUN, WIND_SUN, TEMP_SUN,
        0.0, ROTATION_SUN
    ) {}
	~Sun() {}
};

#endif
