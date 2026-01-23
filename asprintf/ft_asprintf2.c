/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:22:27 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:50:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asprintf.h"

/**
 * @brief Adds a formatting flag to the structure if it is not already present.
 * 
 * This function ensures that each flag is stored only once in the flags array of the structure.
 * 
 * @param c Character representing the flag to add (e.g., '-', '+', '0', etc.).
 * @param v Pointer to the formatting structure containing the flags array.
 * 
 * @return Pointer to the updated formatting structure.
 */
t_struct	*flags(char c, t_struct *v)
{
	int	i;

	i = 0;
	if (!c)
		return (v);
	while (i < 6)
	{
		if (c == v->flags[i])
			break ;
		else if (v->flags[i] == 0)
		{
			v->flags[i] = c;
			break ;
		}
		i++;
	}
	return (v);
}

/**
 * @brief Filters the stored flags based on the type of format specifier and prioritizes certain flags.
 * 
 * This function removes conflicting or invalid flags according to standard printf behavior.
 * For example, the '0' flag is ignored when left-justify '-' is present.
 * 
 * @param i Index in the format string `v->str` corresponding to the current format specifier.
 * @param v Pointer to the formatting structure containing flags, width, and precision.
 * 
 * @return Pointer to the updated formatting structure after filtering.
 */
t_struct	*flag_filter(int i, t_struct *v)
{
	int	j;

	j = 0;
	if (v->str[i] == '%')
		while (v->flags[j] != 0)
			v->flags[j++] = 0;
	v = keep_prior_flag('0', '-', v);
	v = keep_prior_flag(' ', '+', v);
	if (srch_flag(v->flags, '0') && (v->str[i] == 'c' || v->str[i] == 's'))
		v = erase_flag('0', v);
	if (srch_flag(v->flags, '+') && !(v->str[i] == 'i' || v->str[i] == 'd'
			|| v->str[i] == 'p'))
		v = erase_flag('+', v);
	if (srch_flag(v->flags, ' ') && !(v->str[i] == 'i' || v->str[i] == 'd'
			|| v->str[i] == 'p'))
		v = erase_flag(' ', v);
	if (srch_flag(v->flags, '.') && v->str[i] == 'c')
		v = erase_flag('.', v);
	if (srch_flag(v->flags, '#') && !(v->str[i] == 'x' || v->str[i] == 'X'))
		v = erase_flag('#', v);
	return (v);
}


/**
 * @brief Parses numeric width and precision fields for a format specifier.
 * 
 * Handles explicit numeric values as well as '.' precision indicators and '*' for
 * dynamic width/precision from the variadic arguments list.
 * 
 * @param i Pointer to the current index in the format string `v->str`.
 * @param v Pointer to the formatting structure containing flags, width, and precision.
 * @param args Variadic arguments list for retrieving dynamic width/precision values.
 * 
 * @return Pointer to the updated formatting structure after parsing numeric fields.
 */
t_struct	*parse_nd_flags3(int *i, t_struct *v, va_list args)
{
	if (v->str[*i] >= '1' && v->str[*i] <= '9')
	{
		v->nb1 = ft_atoi((const char *)v->str + *i);
		while (v->str[*i] >= '0' && v->str[*i] <= '9')
			*i += 1;
	}
	if (v->str[*i] == '.')
	{
		v = flags(bonus_flag_finder(*i, v), v);
		*i += 1;
		if (v->str[*i] == '*')
		{
			v->nb2 = va_arg(args, int);
			if (v->nb2 < 0)
				v = erase_flag('.', v);
			else
				v = flags('0', v);
			*i += 1;
		}
		else
			v->nb2 = ft_atoi((const char *)v->str + *i);
		while (v->str[*i] >= '0' && v->str[*i] <= '9')
			*i += 1;
	}
	return (v);
}

/**
 * @brief Parses flags, width, and precision for a format specifier, including '*' handling.
 * 
 * Handles cases where the width or precision is provided via '*' in the format string.
 * Delegates numeric parsing to `parse_nd_flags3`.
 * 
 * @param i Pointer to the current index in the format string `v->str`.
 * @param v Pointer to the formatting structure containing flags, width, and precision.
 * @param args Variadic arguments list for retrieving dynamic width/precision values.
 * 
 * @return Pointer to the updated formatting structure after parsing flags and numeric fields.
 */
t_struct	*parse_nd_flags2(int *i, t_struct *v, va_list args)
{
	if (v->str[*i] == '*')
	{
		*i += 1;
		if (v->str[*i - 1] == '*')
			v->nb1 = va_arg(args, int);
		if (v->str[*i] == '.' && v->str[*i + 1] == '*')
		{
			v = flags(bonus_flag_finder(*i, v), v);
			v->nb2 = va_arg(args, int);
			if (v->nb2 < 0)
				v = erase_flag('.', v);
			else
				v = flags('0', v);
			*i += 2;
		}
	}
	else
		v = parse_nd_flags3(i, v, args);
	return (v);
}

/**
 * @brief Checks if the current character in the format string is a standard format specifier.
 * 
 * Recognized specifiers are: 'c', 's', 'p', 'd', 'i', 'u', 'x', 'X', '%'.
 * 
 * @param v Pointer to the formatting structure containing the format string.
 * @param i Index of the character to check in the format string `v->str`.
 * 
 * @return int Returns 1 if the character is a recognized standard format specifier, 0 otherwise.
 */
int	standard_conds(t_struct *v, int i)
{
	if (v->str[i] == 'c' || v->str[i] == 's' || v->str[i] == 'p'
		|| v->str[i] == 'd' || v->str[i] == 'i' || v->str[i] == 'u'
		|| v->str[i] == 'x' || v->str[i] == 'X' || v->str[i] == '%')
		return (1);
	return (0);
}
