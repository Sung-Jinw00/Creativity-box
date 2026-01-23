/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:46:57 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:22:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

/**
 * @brief Calculates the length of a hexadecimal number, considering precision and flags.
 * 
 * Adjusts the number of zeros needed for precision and adds extra length for the '#' flag.
 * Updates the field width (`nb1`) in the formatting structure.
 * 
 * @param nb Unsigned integer to calculate the hexadecimal length for.
 * @param v Pointer to the formatting structure containing flags, width, and precision.
 * 
 * @return int Total length of the formatted hexadecimal number, including zeros and prefixes.
 */
int	ft_len_hexa(unsigned int nb, t_struct *v)
{
	int	len_hexa;

	len_hexa = 1;
	while (nb >= 16)
	{
		nb /= 16;
		len_hexa++;
	}
	v->nb1 -= len_hexa;
	if (srch_flag(v->flags, '.') && v->nb2 > len_hexa)
	{
		v->zeros = v->nb2 - len_hexa;
		len_hexa += v->zeros;
	}
	if (srch_flag(v->flags, '#'))
		len_hexa += 2;
	return (len_hexa);
}

/**
 * @brief Prints a hexadecimal number with field width and alignment when the number is non-zero.
 * 
 * Handles spacing based on field width (`nb1`) and the '-' flag for left/right alignment.
 * Calls the `hexa_print` function to output the number itself.
 * 
 * @param v Pointer to the formatting structure containing buffer, flags, width, and precision.
 * @param len_hexa Length of the formatted hexadecimal number, including zeros and prefix.
 * @param nb Unsigned integer value to print in hexadecimal.
 * @param i Index of the format specifier in the format string (used for 'x' or 'X').
 */
void	print_hexa_if_no_0(t_struct *v, int len_hexa, unsigned int nb, int i)
{
	v->nb1 -= len_hexa;
	if (!srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer[v->i++] = ' ';
	hexa_print(nb, v, v->str[i]);
	if (srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer[v->i++] = ' ';
}

/**
 * @brief Resets the temporary length of a hexadecimal number by removing added zeros and prefix.
 * 
 * Used to calculate how much additional space is needed for field width padding.
 * 
 * @param len_hexa Current length of the formatted hexadecimal number.
 * @param v Pointer to the formatting structure containing flags.
 * 
 * @return int Length after removing zeros and '#' prefix.
 */
int	reset_len_hexa(int len_hexa, t_struct *v)
{
	len_hexa -= v->zeros;
	if (srch_flag(v->flags, '#'))
		len_hexa -= 2;
	return (len_hexa);
}

/**
 * @brief Prints a hexadecimal number with all formatting applied.
 * 
 * Handles zero values, field width (`nb1`), precision (`nb2`), '0' flag, '-' flag, and '#' flag.
 * Updates the total character count in `*count`.
 * 
 * @param nb Unsigned integer value to print in hexadecimal.
 * @param v Pointer to the formatting structure containing buffer, flags, width, and precision.
 * @param i Index of the format specifier in the format string (used for 'x' or 'X').
 * @param count Pointer to the number of characters printed so far; updated by the function.
 */
void	ft_print_hexa(unsigned int nb, t_struct *v, int i, int *count)
{
	int	len_hexa;

	if (nb == 0)
	{
		ft_print_int(0, v, count);
		return ;
	}
	len_hexa = ft_len_hexa(nb, v);
	*count += len_hexa;
	len_hexa -= reset_len_hexa(len_hexa, v);
	if (v->nb1 > len_hexa)
	{
		*count += v->nb1 - len_hexa;
		if (srch_flag(v->flags, '0') && !srch_flag(v->flags, '.'))
		{
			if (v->nb1 > len_hexa)
				v->zeros += v->nb1 - len_hexa;
			hexa_print(nb, v, v->str[i]);
		}
		else
			print_hexa_if_no_0(v, len_hexa, nb, i);
	}
	else
		hexa_print(nb, v, v->str[i]);
}
