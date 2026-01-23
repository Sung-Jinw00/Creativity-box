/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:48:01 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:31:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

/**
 * @brief Prints a null pointer as "(nil)" with field width and alignment.
 * 
 * Handles left ('-') and right alignment based on flags and adjusts `nb1` width.
 * 
 * @param v Formatting structure containing flags, width, precision, and file descriptor.
 * @param count Pointer to the number of characters printed; updated by this function.
 */
void	ft_null_ptr(t_struct v, int *count)
{
	char	*nil;

	nil = "(nil)";
	if (v.nb1 - 5 > 0 && !ft_strcmp(nil, "(nil)"))
	{
		if (v.nb1 >= 5)
			*count += v.nb1 - 5;
		if (srch_flag(v.flags, '-'))
			ft_putstr(nil, count, 5, v.fd);
		v.nb1 -= 5;
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
		if (!srch_flag(v.flags, '-'))
			ft_putstr(nil, count, 5, v.fd);
	}
	else
		ft_putstr(nil, count, 5, v.fd);
}

/**
 * @brief Calculates the total length of a pointer when printed in hexadecimal with "0x".
 * 
 * Considers precision ('.') and optional space or plus flags. Updates the number of zeros to print.
 * 
 * @param ptr Pointer value to print.
 * @param v Pointer to formatting structure containing flags, width, precision, and zeros.
 * 
 * @return int Total number of characters the formatted pointer will occupy.
 */
int	ft_len_ptr(size_t ptr, t_struct *v)
{
	int	len_ptr;

	len_ptr = 1;
	while (ptr >= 16)
	{
		ptr /= 16;
		len_ptr++;
	}
	len_ptr += (int)ft_strlen("0x");
	if (srch_flag(v->flags, '.') && v->nb2 > len_ptr - 2)
	{
		v->zeros = v->nb2 - (len_ptr - 2);
		len_ptr += v->zeros;
	}
	if (srch_flag(v->flags, ' ') || srch_flag(v->flags, '+'))
		len_ptr++;
	return (len_ptr);
}

/**
 * @brief Prints a pointer value with spaces padding when '0' flag is not used.
 * 
 * Handles left ('-') and right alignment. Adjusts width (`nb1`) before and after printing.
 * 
 * @param v Formatting structure containing flags, width, and file descriptor.
 * @param len_ptr Length of the pointer including zeros and "0x" prefix.
 * @param ptr Pointer value to print.
 */
void	print_ptr_if_no_0(t_struct v, int len_ptr, size_t ptr)
{
	v.nb1 -= len_ptr;
	if (!srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
	ptr_print(ptr, v);
	if (srch_flag(v.flags, '-'))
		while (v.nb1-- > 0)
			write(v.fd, " ", 1);
}

/**
 * @brief Prints a pointer value in hexadecimal format with flags, width, and precision.
 * 
 * If the pointer is NULL, delegates to `ft_null_ptr`. Handles '0' padding, '-' alignment,
 * and the "0x" prefix.
 * 
 * @param ptr Pointer value to print.
 * @param v Formatting structure containing flags, width, precision, and file descriptor.
 * @param count Pointer to the number of characters printed; updated by this function.
 */
void	ft_print_ptr(size_t ptr, t_struct v, int *count)
{
	int	len_ptr;

	if (!ptr)
	{
		ft_null_ptr(v, count);
		return ;
	}
	len_ptr = ft_len_ptr(ptr, &v);
	*count += len_ptr;
	if (v.nb1 > len_ptr)
	{
		*count += v.nb1 - len_ptr;
		if (srch_flag(v.flags, '0'))
		{
			v.zeros += v.nb1 - len_ptr;
			ptr_print(ptr, v);
		}
		else
			print_ptr_if_no_0(v, len_ptr, ptr);
	}
	else
		ptr_print(ptr, v);
}
