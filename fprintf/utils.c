/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:18:33 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:33:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

/**
 * @brief Keeps the prior flag when two conflicting flags exist.
 * 
 * This function ensures that in case of conflicting flags (e.g., '0' and '-'),
 * the prior flag in the order of appearance is preserved, and the later conflicting
 * flag is erased from the flags array.
 * 
 * @param erased The flag that might be removed.
 * @param prior The flag that should take precedence if both exist.
 * @param v The formatting structure containing the flags array.
 * 
 * @return t_struct Updated formatting structure with the conflicting flag removed if necessary.
 */
t_struct	keep_prior_flag(char erased, char prior, t_struct v)
{
	int	j;
	int	save;

	j = 0;
	save = 0;
	while (v.flags[j])
	{
		if (v.flags[j] == erased || v.flags[j] == prior)
			save = j++;
		if (v.flags[j] == erased || v.flags[j] == prior)
		{
			if (v.flags[save] == erased)
				j = save;
			while (v.flags[j] != '\0')
			{
				v.flags[j] = v.flags[j + 1];
				j++;
			}
			break ;
		}
		j++;
	}
	return (v);
}

/**
 * @brief Checks whether a specific flag exists in a string.
 * 
 * @param s The string containing flags.
 * @param c The flag character to search for.
 * 
 * @return int 1 if the flag is found, 0 otherwise.
 */
int	srch_flag(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Erases a specific flag from the flags array in the formatting structure.
 * 
 * @param erased The flag character to remove.
 * @param v The formatting structure containing the flags array.
 * 
 * @return t_struct Updated formatting structure with the flag removed.
 */
t_struct	erase_flag(char erased, t_struct v)
{
	int	j;

	j = 0;
	while (v.flags[j])
	{
		if (v.flags[j] == erased)
		{
			while (v.flags[j] != '\0')
			{
				v.flags[j] = v.flags[j + 1];
				j++;
			}
			break ;
		}
		j++;
	}
	return (v);
}

/**
 * @brief Determines if the character at index i of the format string is a "bonus" flag.
 * 
 * Recognized bonus flags: '-', '0', '.', '#', ' ', '+'.
 * 
 * @param i Index in the format string.
 * @param v The formatting structure containing the format string.
 * 
 * @return char The flag character if found, or 0 if none of the bonus flags match.
 */
char	bonus_flag_finder(int i, t_struct v)
{
	if (v.str[i] == '-')
		return ('-');
	else if (v.str[i] == '0')
		return ('0');
	else if (v.str[i] == '.')
		return ('.');
	else if (v.str[i] == '#')
		return ('#');
	else if (v.str[i] == ' ')
		return (' ');
	else if (v.str[i] == '+')
		return ('+');
	else
		return (0);
}

/**
 * @brief Converts a string to an integer.
 * 
 * Handles optional leading whitespace and '+'/'-' signs.
 * Stops parsing at the first non-digit character.
 * 
 * @param nptr The input string representing the number.
 * 
 * @return int The converted integer value.
 */
int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}
