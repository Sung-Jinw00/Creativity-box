/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:22:27 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:28:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"


/**
 * @brief Adds a flag character to the flags array if it is not already present.
 * 
 * Ensures that each flag is stored only once in the structure.
 * 
 * @param c Flag character to add ('-', '+', '0', ' ', '#', '.').
 * @param v Formatting structure containing the flags array.
 * 
 * @return Updated formatting structure with the flag added.
 */
t_struct	flags(char c, t_struct v)
{
	int	i;

	i = 0;
	if (!c)
		return (v);
	while (i < 6)
	{
		if (c == v.flags[i])
			break ;
		else if (v.flags[i] == 0)
		{
			v.flags[i] = c;
			break ;
		}
		i++;
	}
	return (v);
}

/**
 * @brief Filters and adjusts flags based on the current format specifier.
 * 
 * Removes incompatible flags (e.g., '0' for 'c'/'s', '+' for non-numeric types) and
 * enforces precedence rules (e.g., '-' overrides '0', '+' overrides ' ').
 * 
 * @param i Current index in the format string.
 * @param v Formatting structure containing flags and the format string.
 * 
 * @return Updated formatting structure after applying flag rules.
 */
t_struct	flag_filter(int i, t_struct v)
{
	int	j;

	j = 0;
	if (v.str[i] == '%')
		while (v.flags[j] != 0)
			v.flags[j++] = 0;
	v = keep_prior_flag('0', '-', v);
	v = keep_prior_flag(' ', '+', v);
	if (srch_flag(v.flags, '0') && (v.str[i] == 'c' || v.str[i] == 's'))
		v = erase_flag('0', v);
	if (srch_flag(v.flags, '+') && !(v.str[i] == 'i' || v.str[i] == 'd'
			|| v.str[i] == 'p'))
		v = erase_flag('+', v);
	if (srch_flag(v.flags, ' ') && !(v.str[i] == 'i' || v.str[i] == 'd'
			|| v.str[i] == 'p'))
		v = erase_flag(' ', v);
	if (srch_flag(v.flags, '.') && v.str[i] == 'c')
		v = erase_flag('.', v);
	if (srch_flag(v.flags, '#') && !(v.str[i] == 'x' || v.str[i] == 'X'))
		v = erase_flag('#', v);
	return (v);
}

/**
 * @brief Parses numeric width and precision after a format specifier.
 * 
 * Handles digits, '.', and '*' to set `nb1` (width) and `nb2` (precision) in the structure.
 * Also updates flags according to bonus flags like '.' and '0'.
 * 
 * @param i Pointer to the current index in the format string; updated as characters are processed.
 * @param v Formatting structure containing flags, width, and precision.
 * @param args Variable argument list for values corresponding to '*' width/precision specifiers.
 * 
 * @return Updated formatting structure with parsed width, precision, and flags.
 */
t_struct	parse_nd_flags3(int *i, t_struct v, va_list args)
{
	if (v.str[*i] >= '1' && v.str[*i] <= '9')
	{
		v.nb1 = ft_atoi((const char *)v.str + *i);
		while (v.str[*i] >= '0' && v.str[*i] <= '9')
			*i += 1;
	}
	if (v.str[*i] == '.')
	{
		v = flags(bonus_flag_finder(*i, v), v);
		*i += 1;
		if (v.str[*i] == '*')
		{
			v.nb2 = va_arg(args, int);
			if (v.nb2 < 0)
				v = erase_flag('.', v);
			else
				v = flags('0', v);
			*i += 1;
		}
		else
			v.nb2 = ft_atoi((const char *)v.str + *i);
		while (v.str[*i] >= '0' && v.str[*i] <= '9')
			*i += 1;
	}
	return (v);
}

/**
 * @brief Parses numeric width and precision, including '*' handling.
 * 
 * Delegates to `parse_nd_flags3` for digit and '.' parsing. Handles special cases
 * where width or precision is specified by '*'.
 * 
 * @param i Pointer to the current index in the format string; updated as characters are processed.
 * @param v Formatting structure containing flags, width, and precision.
 * @param args Variable argument list for values corresponding to '*' width/precision specifiers.
 * 
 * @return Updated formatting structure with parsed width, precision, and flags.
 */
t_struct	parse_nd_flags2(int *i, t_struct v, va_list args)
{
	if (v.str[*i] == '*')
	{
		*i += 1;
		if (v.str[*i - 1] == '*')
			v.nb1 = va_arg(args, int);
		if (v.str[*i] == '.' && v.str[*i + 1] == '*')
		{
			v = flags(bonus_flag_finder(*i, v), v);
			v.nb2 = va_arg(args, int);
			if (v.nb2 < 0)
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
 * @brief Checks whether the current character in the format string is a standard specifier.
 * 
 * Recognized specifiers are: 'c', 's', 'p', 'd', 'i', 'u', 'x', 'X', '%'.
 * 
 * @param v Formatting structure containing the format string.
 * @param i Current index in the format string.
 * 
 * @return int Returns 1 if the character is a standard format specifier, 0 otherwise.
 */
int	standard_conds(t_struct v, int i)
{
	if (v.str[i] == 'c' || v.str[i] == 's' || v.str[i] == 'p' || v.str[i] == 'd'
		|| v.str[i] == 'i' || v.str[i] == 'u' || v.str[i] == 'x'
		|| v.str[i] == 'X' || v.str[i] == '%')
		return (1);
	return (0);
}
