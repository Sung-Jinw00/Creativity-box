/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:48:01 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:52:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asprintf.h"

/**
 * @brief Prints a null pointer representation "(nil)" with field width.
 * 
 * @param v Pointer to formatting structure.
 * @param count Pointer to the total characters printed.
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
			ft_putstr(nil, count, 5, &v->buffer);
		v->nb1 -= 5;
		while (v->nb1-- > 0)
			v->buffer = add_char_realloc(v->buffer, ' ');
		if (!srch_flag(v->flags, '-'))
			ft_putstr(nil, count, 5, &v->buffer);
	}
	else
		ft_putstr(nil, count, 5, &v->buffer);
}

/**
 * @brief Calculates the length of a pointer representation including "0x" and precision.
 * 
 * @param ptr Pointer value.
 * @param v Pointer to formatting structure.
 * 
 * @return Length in characters.
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
 * @brief Handles printing of a pointer when '0' flag is not set.
 * 
 * @param v Pointer to formatting structure.
 * @param len_ptr Length of the pointer representation.
 * @param ptr Pointer value to print.
 */
void	print_ptr_if_no_0(t_struct *v, int len_ptr, size_t ptr)
{
	v->nb1 -= len_ptr;
	if (!srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer = add_char_realloc(v->buffer, ' ');
	ptr_print(ptr, v);
	if (srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer = add_char_realloc(v->buffer, ' ');
}

/**
 * @brief Prints a pointer value with "0x", flags, width, and precision.
 * 
 * @param ptr Pointer value.
 * @param v Pointer to formatting structure.
 * @param count Pointer to the total characters printed.
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
