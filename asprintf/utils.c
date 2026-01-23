/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:18:33 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:53:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asprintf.h"

/**
 * @brief Keeps the prior flag in case of conflicts and removes the overridden one.
 * 
 * @param erased Flag to remove.
 * @param prior Flag that has priority.
 * @param v Pointer to formatting structure.
 * 
 * @return Updated pointer to the structure.
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
 * @brief Searches for a flag in the flags array.
 * 
 * @param s Array of flags.
 * @param c Flag character to search.
 * 
 * @return 1 if found, 0 otherwise.
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
 * @brief Erases a specific flag from the flags array.
 * 
 * @param erased Flag character to erase.
 * @param v Pointer to formatting structure.
 * 
 * @return Updated pointer to the structure.
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
 * @brief Returns the bonus flag character at a given index in the format string.
 * 
 * @param i Index in the format string.
 * @param v Pointer to formatting structure.
 * 
 * @return Flag character or 0 if none.
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
 * @brief Writes a string to the buffer with a limit and updates the count.
 * 
 * @param s String to write.
 * @param count Pointer to character count.
 * @param limit Maximum characters to write.
 * @param buffer Pointer to buffer.
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
