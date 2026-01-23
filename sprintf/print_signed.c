/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:01:22 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:23:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

/**
 * @brief Calculates the total length of a signed integer for printing.
 * 
 * Considers the sign, number of digits, precision (`nb2`) for leading zeros,
 * and flags (' ' or '+') that may add extra space. Updates the `zeros` field
 * in the formatting structure if precision requires padding.
 * 
 * @param nb Signed integer to calculate the length for.
 * @param v Pointer to the formatting structure containing flags, width, and precision.
 * 
 * @return int Total length of the formatted number including sign, zeros, and extra flag space.
 */
int	ft_len_nb(long nb, t_struct *v)
{
	int	len_nb;
	int	sign;

	len_nb = 0;
	sign = 0;
	if (nb == 0 && srch_flag(v->flags, '.') && v->nb2 == 0)
		return (0);
	if (nb < 0)
	{
		nb = -nb;
		sign = 1;
		len_nb++;
	}
	len_nb += ft_digits(nb);
	if ((srch_flag(v->flags, ' ') || srch_flag(v->flags, '+')) && sign != 1)
	{
		len_nb++;
		sign++;
	}
	if (srch_flag(v->flags, '.') && v->nb2 > len_nb - sign)
	{
		v->zeros = v->nb2 - (len_nb - sign);
		len_nb += v->zeros;
	}
	return (len_nb);
}

/**
 * @brief Prints a signed integer with field width and alignment when the '0' flag is not set.
 * 
 * Handles spacing based on the field width (`nb1`) and '-' flag for left/right alignment.
 * Calls `ft_putnbr` to output the number itself.
 * 
 * @param v Pointer to the formatting structure containing buffer, flags, width, and precision.
 * @param len_nb Length of the formatted number including sign and zeros.
 * @param nb Signed integer value to print.
 */
void	print_nb_if_no_0(t_struct *v, int len_nb, long nb)
{
	v->nb1 -= len_nb;
	if (!srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer[v->i++] = ' ';
	ft_putnbr(nb, v, 10, 0);
	if (srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer[v->i++] = ' ';
}

/**
 * @brief Prints a signed integer with all formatting applied.
 * 
 * Handles field width (`nb1`), precision (`nb2`), '0' flag, '-' flag, and sign/space flags.
 * Updates the total character count in `*count`.
 * 
 * @param nb Signed integer value to print.
 * @param v Pointer to the formatting structure containing buffer, flags, width, and precision.
 * @param count Pointer to the number of characters printed so far; updated by the function.
 */
void	ft_print_int(long nb, t_struct *v, int *count)
{
	int	len_nb;

	len_nb = ft_len_nb(nb, v);
	*count += len_nb;
	if (v->nb1 > len_nb)
	{
		*count += v->nb1 - len_nb;
		if (srch_flag(v->flags, '0') && !srch_flag(v->flags, '.'))
		{
			v->zeros += v->nb1 - len_nb;
			ft_putnbr(nb, v, 10, 0);
		}
		else
			print_nb_if_no_0(v, len_nb, nb);
	}
	else
		ft_putnbr(nb, v, 10, 0);
}
