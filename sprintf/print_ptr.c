/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:48:01 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:23:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

/**
 * @brief Prints a null pointer as "(nil)" with optional field width and alignment.
 * 
 * If the field width (`nb1`) is greater than 5, pads with spaces according to the '-' flag.
 * Updates the character count in `*count`.
 * 
 * @param v Pointer to the formatting structure containing buffer, flags, and width.
 * @param count Pointer to the number of characters printed so far; updated by the function.
 */
void	ft_null_ptr(t_struct *v, int *count)
{
	char	*nil;

	nil = "(nil)";
	if (v->nb1 - 5 > 0 && !ft_strcmp(nil, "(nil)"))
	{
		if (v->nb1 >= 5)
			*count += v->nb1 - 5;
		if (srch_flag(v->flags, '-'))
			ft_putstr(nil, count, 5, v);
		v->nb1 -= 5;
		while (v->nb1-- > 0)
			v->buffer[v->i++] = ' ';
		if (!srch_flag(v->flags, '-'))
			ft_putstr(nil, count, 5, v);
	}
	else
		ft_putstr(nil, count, 5, v);
}

/**
 * @brief Calculates the length of a pointer in hexadecimal notation, including the "0x" prefix.
 * 
 * Considers precision (`nb2`) to add leading zeros and optional ' ' or '+' flags for extra length.
 * Updates the `zeros` field in the formatting structure if needed.
 * 
 * @param ptr Pointer value to calculate the length for.
 * @param v Pointer to the formatting structure containing flags, width, and precision.
 * 
 * @return int Total length of the formatted pointer including prefix, zeros, and extra flags.
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
 * @brief Prints a non-null pointer with field width and alignment when the '0' flag is not set.
 * 
 * Adjusts spacing based on the field width (`nb1`) and '-' flag. Calls `ptr_print` to output the pointer.
 * 
 * @param v Pointer to the formatting structure containing buffer, flags, width, and precision.
 * @param len_ptr Length of the formatted pointer, including prefix and leading zeros.
 * @param ptr Pointer value to print.
 */
void	print_ptr_if_no_0(t_struct *v, int len_ptr, size_t ptr)
{
	v->nb1 -= len_ptr;
	if (!srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer[v->i++] = ' ';
	ptr_print(ptr, v);
	if (srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer[v->i++] = ' ';
}

/**
 * @brief Prints a pointer with all formatting applied, including null pointer handling.
 * 
 * Handles field width (`nb1`), precision (`nb2`), '0' flag, and '-' flag. Updates the total character
 * count in `*count`.
 * 
 * @param ptr Pointer value to print.
 * @param v Pointer to the formatting structure containing buffer, flags, width, and precision.
 * @param count Pointer to the number of characters printed so far; updated by the function.
 */
void	ft_print_ptr(size_t ptr, t_struct *v, int *count)
{
	int	len_ptr;

	if (!ptr)
	{
		ft_null_ptr(v, count);
		return ;
	}
	len_ptr = ft_len_ptr(ptr, v);
	*count += len_ptr;
	if (v->nb1 > len_ptr)
	{
		*count += v->nb1 - len_ptr;
		if (srch_flag(v->flags, '0'))
		{
			v->zeros += v->nb1 - len_ptr;
			ptr_print(ptr, v);
		}
		else
			print_ptr_if_no_0(v, len_ptr, ptr);
	}
	else
		ptr_print(ptr, v);
}
