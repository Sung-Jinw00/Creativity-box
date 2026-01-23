/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:22:27 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:20:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

/**
 * @brief Adds a flag character to the structure if not already present.
 * 
 * Iterates through the flag array in the structure and adds the given flag
 * character in the first available position.
 * 
 * @param c Character representing the flag to add.
 * @param v Pointer to the formatting structure containing current flags.
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
 * @brief Filters incompatible flags based on the current format specifier.
 * 
 * Removes or adjusts flags depending on the type of argument being formatted.
 * For example, '0' is removed for strings and characters, '+' is removed for
 * non-integer types, and so on.
 * 
 * @param i Index of the current character in the format string.
 * @param v Pointer to the formatting structure containing flags and format string.
 * 
 * @return Pointer to the updated formatting structure.
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
 * @brief Parses numeric width and precision specifications, including dot ('.') modifiers.
 * 
 * Handles numbers, '.', and '*' in the format string to set the width (nb1) and precision (nb2)
 * in the structure. Calls bonus_flag_finder to set special flags if needed.
 * 
 * @param i Pointer to the current index in the format string. This value may be updated.
 * @param v Pointer to the formatting structure containing current flags and width/precision.
 * @param args Variable argument list for '*' width/precision values.
 * 
 * @return Pointer to the updated formatting structure.
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
 * @brief Parses numeric width, precision, and '*' flags in the format string.
 * 
 * Handles '*' as width or precision, or delegates to parse_nd_flags3 for numeric values.
 * Updates the nb1 and nb2 fields in the structure according to parsed values.
 * 
 * @param i Pointer to the current index in the format string. This value may be updated.
 * @param v Pointer to the formatting structure containing flags and width/precision.
 * @param args Variable argument list for '*' width/precision values.
 * 
 * @return Pointer to the updated formatting structure.
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
 * @brief Checks if the character at the current index is a standard format specifier.
 * 
 * Standard specifiers include: 'c', 's', 'p', 'd', 'i', 'u', 'x', 'X', '%'.
 * 
 * @param v Pointer to the formatting structure containing the format string.
 * @param i Index of the character to check in the format string.
 * 
 * @return int Returns 1 if the character is a standard specifier, 0 otherwise.
 */
int	standard_conds(t_struct *v, int i)
{
	if (v->str[i] == 'c' || v->str[i] == 's' || v->str[i] == 'p'
		|| v->str[i] == 'd' || v->str[i] == 'i' || v->str[i] == 'u'
		|| v->str[i] == 'x' || v->str[i] == 'X' || v->str[i] == '%')
		return (1);
	return (0);
}
