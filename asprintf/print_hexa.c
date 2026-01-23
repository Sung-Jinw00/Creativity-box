/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:46:57 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:51:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asprintf.h"

/**
 * @brief Calculates the length of a hexadecimal number including precision and '#' flag.
 * 
 * @param nb Unsigned integer to measure.
 * @param v Pointer to formatting structure.
 * 
 * @return Length in characters of the hex representation.
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
 * @brief Handles printing of hexadecimal number with field width and alignment.
 * 
 * @param v Pointer to formatting structure.
 * @param len_hexa Length of the hex number including precision and '#' flag.
 * @param nb Unsigned integer to print.
 * @param i Index of format character ('x' or 'X') in the format string.
 */
void	print_hexa_if_no_0(t_struct *v, int len_hexa, unsigned int nb, int i)
{
	v->nb1 -= len_hexa;
	if (!srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer = add_char_realloc(v->buffer, ' ');
	hexa_print(nb, v, v->str[i]);
	if (srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer = add_char_realloc(v->buffer, ' ');
}

/**
 * @brief Adjusts length accounting for zeros and '#' flag for hex printing.
 * 
 * @param len_hexa Length calculated.
 * @param v Pointer to formatting structure.
 * 
 * @return Adjusted length.
 */
int	reset_len_hexa(int len_hexa, t_struct *v)
{
	len_hexa -= v->zeros;
	if (srch_flag(v->flags, '#'))
		len_hexa -= 2;
	return (len_hexa);
}

/**
 * @brief Prints a hexadecimal number with proper flags, width, and precision.
 * 
 * @param nb Unsigned integer to print.
 * @param v Pointer to formatting structure.
 * @param i Index in the format string for 'x' or 'X'.
 * @param count Pointer to the total characters printed.
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
