/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:02:22 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:32:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

/**
 * @brief Calculates the total length of an unsigned integer when printed.
 * 
 * Considers the precision ('.') and updates the number of zeros (`v->zeros`) to pad.
 * Handles negative numbers by converting them to their unsigned representation.
 * 
 * @param nb The unsigned integer to print (may be negative if originally signed casted).
 * @param v Pointer to the formatting structure containing flags, width, precision, and zeros.
 * 
 * @return int Total number of characters the formatted unsigned integer will occupy.
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
 * @brief Prints an unsigned integer with spaces padding when '0' flag is not used.
 * 
 * Handles left ('-') and right alignment based on flags and width (`nb1`), 
 * and prints leading zeros if precision requires them.
 * 
 * @param v Formatting structure containing flags, width, zeros, and file descriptor.
 * @param len_unb Total length of the number including zeros.
 * @param nb The unsigned integer to print.
 */
void	print_unb_if_no_0(t_struct v, int len_unb, long nb)
{
	v.nb1 -= len_unb;
	if (!srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
	while (v.zeros-- > 0)
		write(v.fd, "0", 1);
	ft_putunbr(nb, v);
	if (srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
}

/**
 * @brief Prints an unsigned integer with flags, width, and precision applied.
 * 
 * Handles '0' padding, '-' alignment, precision padding with zeros,
 * and updates the character count.
 * Delegates to `print_unb_if_no_0` if '0' flag is not used.
 * Converts negative numbers to unsigned representation.
 * 
 * @param nb The unsigned integer to print (may be negative if casted from signed).
 * @param v Formatting structure containing flags, width, precision, zeros, and file descriptor.
 * @param count Pointer to the number of characters printed; updated by this function.
 */
void	ft_print_uns_int(long nb, t_struct v, int *count)
{
	int	len_unb;

	len_unb = ft_len_unb(nb, &v);
	*count += len_unb;
	if (nb < 0)
		nb += (long)INT_MAX * 2 + 2;
	if (v.nb1 > len_unb)
	{
		*count += v.nb1 - len_unb;
		if (srch_flag(v.flags, '0') && !srch_flag(v.flags, '.'))
		{
			v.zeros += v.nb1 - len_unb;
			while (v.zeros-- > 0)
				write(v.fd, "0", 1);
			ft_putunbr(nb, v);
		}
		else
			print_unb_if_no_0(v, len_unb, nb);
	}
	else
	{
		while (v.zeros-- > 0)
			write(v.fd, "0", 1);
		ft_putunbr(nb, v);
	}
}
