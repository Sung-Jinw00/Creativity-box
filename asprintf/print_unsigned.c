/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:02:22 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:52:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asprintf.h"

/**
 * @brief Calculates the length of an unsigned integer including precision and flags.
 * 
 * @param nb Unsigned integer.
 * @param v Pointer to formatting structure.
 * 
 * @return Length in characters.
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
 * @brief Handles printing of unsigned integers when '0' flag is not set.
 * 
 * @param v Pointer to formatting structure.
 * @param len_unb Length of the number representation.
 * @param nb Unsigned integer to print.
 */
void	print_unb_if_no_0(t_struct *v, int len_unb, long nb)
{
	v->nb1 -= len_unb;
	if (!srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer = add_char_realloc(v->buffer, ' ');
	while (v->zeros-- > 0)
		v->buffer = add_char_realloc(v->buffer, '0');
	ft_putunbr_aspf(nb, v);
	if (srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer = add_char_realloc(v->buffer, ' ');
}

/**
 * @brief Prints an unsigned integer with proper flags, width, and precision.
 * 
 * @param nb Unsigned integer to print.
 * @param v Pointer to formatting structure.
 * @param count Pointer to the total characters printed.
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
				v->buffer = add_char_realloc(v->buffer, '0');
			ft_putunbr_aspf(nb, v);
		}
		else
			print_unb_if_no_0(v, len_unb, nb);
	}
	else
	{
		while (v->zeros-- > 0)
			v->buffer = add_char_realloc(v->buffer, '0');
		ft_putunbr_aspf(nb, v);
	}
}
