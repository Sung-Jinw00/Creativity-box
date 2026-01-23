/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:18:33 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:25:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

/**
 * @brief Removes the later occurrence of a flag when two conflicting flags exist.
 * 
 * Keeps the prior flag and erases the subsequent occurrence from the flags array.
 * 
 * @param erased Character representing the flag to potentially remove.
 * @param prior Character representing the flag that has priority.
 * @param v Pointer to the formatting structure containing the flags array.
 * 
 * @return Pointer to the updated formatting structure.
 */
t_struct	*keep_prior_flag(char erased, char prior, t_struct *v)
{
	int	j;
	int	save;

	j = 0;
	save = 0;
	while (v->flags[j])
	{
		if (v->flags[j] == erased || v->flags[j] == prior)
			save = j++;
		if (v->flags[j] == erased || v->flags[j] == prior)
		{
			if (v->flags[save] == erased)
				j = save;
			while (v->flags[j] != '\0')
			{
				v->flags[j] = v->flags[j + 1];
				j++;
			}
			break ;
		}
		j++;
	}
	return (v);
}

/**
 * @brief Searches for a specific flag character in a flag string.
 * 
 * @param s String containing active flags.
 * @param c Character representing the flag to search for.
 * 
 * @return int Returns 1 if the flag is found, 0 otherwise.
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
 * @brief Removes a specific flag character from the flags array.
 * 
 * Shifts all subsequent flags to fill the gap after removal.
 * 
 * @param erased Character representing the flag to remove.
 * @param v Pointer to the formatting structure containing the flags array.
 * 
 * @return Pointer to the updated formatting structure.
 */
t_struct	*erase_flag(char erased, t_struct *v)
{
	int	j;

	j = 0;
	while (v->flags[j])
	{
		if (v->flags[j] == erased)
		{
			while (v->flags[j] != '\0')
			{
				v->flags[j] = v->flags[j + 1];
				j++;
			}
			break ;
		}
		j++;
	}
	return (v);
}

/**
 * @brief Determines which bonus flag is present at a specific index in the format string.
 * 
 * Checks for '-', '0', '.', '#', ' ', or '+' and returns the corresponding character.
 * 
 * @param i Index of the character to check in the format string.
 * @param v Pointer to the formatting structure containing the format string.
 * 
 * @return char The detected flag character, or 0 if no recognized flag is found.
 */
char	bonus_flag_finder(int i, t_struct *v)
{
	if (v->str[i] == '-')
		return ('-');
	else if (v->str[i] == '0')
		return ('0');
	else if (v->str[i] == '.')
		return ('.');
	else if (v->str[i] == '#')
		return ('#');
	else if (v->str[i] == ' ')
		return (' ');
	else if (v->str[i] == '+')
		return ('+');
	else
		return (0);
}

/**
 * @brief Converts a string of digits into an integer.
 * 
 * Handles optional leading whitespace and '+' or '-' signs.
 * 
 * @param nptr Pointer to the null-terminated string to convert.
 * 
 * @return int The integer value represented by the string.
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
