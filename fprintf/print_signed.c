/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:01:22 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:32:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

/**
 * @brief Calculates the total length of a signed integer when printed.
 * 
 * Considers the sign, flags ('+' or ' '), and precision ('.').
 * Updates the number of zeros (`v->zeros`) to print if precision requires padding.
 * 
 * @param nb The signed integer to print.
 * @param v Pointer to the formatting structure containing flags, width, precision, and zeros.
 * 
 * @return int Total number of characters the formatted integer will occupy.
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
 * @brief Prints a signed integer with spaces padding when '0' flag is not used.
 * 
 * Handles left ('-') and right alignment based on flags and width (`nb1`).
 * 
 * @param v Formatting structure containing flags, width, and file descriptor.
 * @param len_nb Total length of the number including zeros and sign.
 * @param nb The signed integer to print.
 */
void	print_nb_if_no_0(t_struct v, int len_nb, long nb)
{
	v.nb1 -= len_nb;
	if (!srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
	ft_putnbr(nb, v, 10, 0);
	if (srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
}

/**
 * @brief Prints a signed integer with flags, width, and precision applied.
 * 
 * Handles '0' padding, '-' alignment, '+' and ' ' flags, and updates the character count.
 * Delegates to `print_nb_if_no_0` if '0' flag is not used.
 * 
 * @param nb The signed integer to print.
 * @param v Formatting structure containing flags, width, precision, and file descriptor.
 * @param count Pointer to the number of characters printed; updated by this function.
 */
void	ft_print_int(long nb, t_struct v, int *count)
{
	int	len_nb;

	len_nb = ft_len_nb(nb, &v);
	*count += len_nb;
	if (v.nb1 > len_nb)
	{
		*count += v.nb1 - len_nb;
		if (srch_flag(v.flags, '0') && !srch_flag(v.flags, '.'))
		{
			v.zeros += v.nb1 - len_nb;
			ft_putnbr(nb, v, 10, 0);
		}
		else
			print_nb_if_no_0(v, len_nb, nb);
	}
	else
		ft_putnbr(nb, v, 10, 0);
}
