/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:02:22 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:24:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

/**
 * @brief Calculates the total length of an unsigned integer for printing.
 * 
 * Considers precision (`nb2`) to add leading zeros. Negative values are
 * converted to their unsigned representation.
 * Updates the `zeros` field in the formatting structure if precision requires padding.
 * 
 * @param nb Integer value to calculate the length for (treated as unsigned).
 * @param v Pointer to the formatting structure containing flags, width, and precision.
 * 
 * @return int Total length of the formatted number including leading zeros.
 */
int	ft_len_unb(long nb, t_struct *v)
{
	int	len_unb;

	if (nb == 0 && srch_flag(v->flags, '.') && v->nb2 == 0)
		return (0);
	if (nb < 0)
		nb += (long)INT_MAX * 2 + 2;
	len_unb = ft_digits(nb);
	if (srch_flag(v->flags, '.') && v->nb2 > len_unb)
	{
		v->zeros = v->nb2 - len_unb;
		len_unb += v->zeros;
	}
	return (len_unb);
}

/**
 * @brief Prints an unsigned integer with field width and alignment when the '0' flag is not set.
 * 
 * Handles spacing based on field width (`nb1`) and '-' flag for left/right alignment.
 * Adds leading zeros based on the `zeros` field. Calls `ft_putunbr_aspf` to output the number.
 * 
 * @param v Pointer to the formatting structure containing buffer, flags, width, and precision.
 * @param len_unb Length of the formatted number including leading zeros.
 * @param nb Unsigned integer value to print.
 */
void	print_unb_if_no_0(t_struct *v, int len_unb, long nb)
{
	v->nb1 -= len_unb;
	if (!srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer[v->i++] = ' ';
	while (v->zeros-- > 0)
		v->buffer[v->i++] = '0';
	ft_putunbr_aspf(nb, v);
	if (srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer[v->i++] = ' ';
}

/**
 * @brief Prints an unsigned integer with all formatting applied.
 * 
 * Handles negative values as their unsigned equivalents, field width (`nb1`), precision (`nb2`),
 * '0' flag, and '-' flag. Updates the total character count in `*count`.
 * 
 * @param nb Integer value to print (treated as unsigned).
 * @param v Pointer to the formatting structure containing buffer, flags, width, and precision.
 * @param count Pointer to the number of characters printed so far; updated by the function.
 */
void	ft_print_uns_int(long nb, t_struct *v, int *count)
{
	int	len_unb;

	len_unb = ft_len_unb(nb, v);
	*count += len_unb;
	if (nb < 0)
		nb += (long)INT_MAX * 2 + 2;
	if (v->nb1 > len_unb)
	{
		*count += v->nb1 - len_unb;
		if (srch_flag(v->flags, '0') && !srch_flag(v->flags, '.'))
		{
			v->zeros += v->nb1 - len_unb;
			while (v->zeros-- > 0)
				v->buffer[v->i++] = '0';
			ft_putunbr_aspf(nb, v);
		}
		else
			print_unb_if_no_0(v, len_unb, nb);
	}
	else
	{
		while (v->zeros-- > 0)
			v->buffer[v->i++] = '0';
		ft_putunbr_aspf(nb, v);
	}
}
