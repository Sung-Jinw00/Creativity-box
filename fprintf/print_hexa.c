/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:46:57 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:30:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

/**
 * @brief Calculates the total length of a hexadecimal number with formatting.
 * 
 * Considers precision ('.') and the '#' flag. Updates the number of zeros to print
 * and adjusts field width (`nb1`) accordingly.
 * 
 * @param nb Unsigned integer to print in hexadecimal.
 * @param v Pointer to formatting structure containing flags, width, precision, and fd.
 * 
 * @return int Total number of characters the formatted hexadecimal will occupy.
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
 * @brief Prints a hexadecimal number with spaces padding when '0' flag is not used.
 * 
 * Handles left ('-') and right alignment. Adjusts width (`nb1`) before and after printing.
 * 
 * @param v Formatting structure containing flags, width, and file descriptor.
 * @param len_hexa Length of the hexadecimal number including zeros and prefixes.
 * @param nb Unsigned integer to print in hexadecimal.
 * @param i Current index in the format string to determine 'x' or 'X'.
 */
void	print_hexa_if_no_0(t_struct v, int len_hexa, unsigned int nb, int i)
{
	v.nb1 -= len_hexa;
	if (!srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
	hexa_print(nb, v, v.str[i]);
	if (srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
}

/**
 * @brief Calculates the effective length of a hexadecimal number excluding zeros and prefix.
 * 
 * Used to determine how much extra padding is needed for field width.
 * 
 * @param len_hexa Original length of the hexadecimal number including zeros and prefix.
 * @param v Formatting structure containing flags.
 * 
 * @return int Length of the hexadecimal number excluding extra zeros and '0x'/'0X' prefix.
 */
int	reset_len_hexa(int len_hexa, t_struct v)
{
	len_hexa -= v.zeros;
	if (srch_flag(v.flags, '#'))
		len_hexa -= 2;
	return (len_hexa);
}

/**
 * @brief Prints an unsigned integer in hexadecimal format with flags, width, and precision.
 * 
 * Handles '0' padding, '-' alignment, and '#' prefix. If the number is 0, delegates to
 * `ft_print_int` to handle formatting.
 * 
 * @param nb Unsigned integer to print in hexadecimal.
 * @param v Formatting structure containing flags, width, precision, and file descriptor.
 * @param i Current index in the format string to determine 'x' or 'X'.
 * @param count Pointer to the number of characters printed; updated by this function.
 */
void	ft_print_hexa(unsigned int nb, t_struct v, int i, int *count)
{
	int	len_hexa;

	if (nb == 0)
	{
		ft_print_int(0, v, count);
		return ;
	}
	len_hexa = ft_len_hexa(nb, &v);
	*count += len_hexa;
	len_hexa -= reset_len_hexa(len_hexa, v);
	if (v.nb1 > len_hexa)
	{
		*count += v.nb1 - len_hexa;
		if (srch_flag(v.flags, '0') && !srch_flag(v.flags, '.'))
		{
			if (v.nb1 > len_hexa)
				v.zeros += v.nb1 - len_hexa;
			hexa_print(nb, v, v.str[i]);
		}
		else
			print_hexa_if_no_0(v, len_hexa, nb, i);
	}
	else
		hexa_print(nb, v, v.str[i]);
}
