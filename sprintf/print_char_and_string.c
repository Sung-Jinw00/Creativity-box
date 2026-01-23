/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_and_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:45:58 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:21:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

/**
 * @brief Prints a single character with optional width and left/right alignment.
 * 
 * If a minimum field width (`nb1`) is specified, the character will be padded with spaces.
 * Supports left-aligned printing using the '-' flag.
 * 
 * @param c Character to print.
 * @param v Pointer to the formatting structure containing buffer, flags, and field width.
 * @param count Pointer to the number of characters printed so far; updated by the function.
 */
void	ft_print_char(char c, t_struct *v, int *count)
{
	if (v->nb1 > 0)
	{
		*count += v->nb1;
		if (srch_flag(v->flags, '-'))
			v->buffer[v->i++] = c;
		while (--v->nb1 > 0)
			v->buffer[v->i++] = ' ';
		if (!srch_flag(v->flags, '-'))
			v->buffer[v->i++] = c;
	}
	else
	{
		v->buffer[v->i++] = c;
		*count += 1;
	}
}

/**
 * @brief Helper function to print a string with field width and alignment.
 * 
 * Adjusts spacing based on the field width (`nb1`) and prints the string either left- or right-aligned.
 * Updates the count of characters printed.
 * 
 * @param v Pointer to the formatting structure containing buffer, flags, and field width.
 * @param print_chars Number of characters of the string to print.
 * @param str String to print.
 * @param count Pointer to the number of characters printed so far; updated by the function.
 */
void	print_str_if_field(t_struct *v, int print_chars, char *str, int *count)
{
	if (v->nb1 >= print_chars)
		*count += v->nb1 - print_chars;
	if (srch_flag(v->flags, '-'))
		ft_putstr(str, count, print_chars, v);
	v->nb1 -= print_chars;
	while (v->nb1-- > 0)
		v->buffer[v->i++] = ' ';
	if (!srch_flag(v->flags, '-'))
		ft_putstr(str, count, print_chars, v);
}

/**
 * @brief Prints a string with optional precision and field width.
 * 
 * Handles NULL strings by printing "(null)" unless precision limits it.
 * Respects precision (`nb2`) to truncate the string, field width (`nb1`) for padding,
 * and '-' flag for left alignment.
 * 
 * @param str String to print; if NULL, handled as "(null)".
 * @param v Pointer to the formatting structure containing buffer, flags, width, and precision.
 * @param count Pointer to the number of characters printed so far; updated by the function.
 */
void	ft_print_str(char *str, t_struct *v, int *count)
{
	int	print_chars;

	if (!str)
		str = "(null)";
	if (!ft_strcmp(str, "(null)") && srch_flag(v->flags, '.') && v->nb2 <= 5)
	{
		str = "";
		print_chars = 0;
	}
	else if (srch_flag(v->flags, '.')
		&& v->nb2 < (int)ft_strlen((const char *)str))
		print_chars = v->nb2;
	else
		print_chars = (int)ft_strlen((const char *)str);
	if (v->nb1 - print_chars > 0)
		print_str_if_field(v, print_chars, str, count);
	else
		ft_putstr(str, count, print_chars, v);
}

/**
 * @brief Prints a percent symbol '%' to the buffer.
 * 
 * This function handles the literal '%' format specifier.
 * 
 * @param buffer Output buffer where the percent symbol will be written.
 * @param i Pointer to the current index in the buffer; updated by the function.
 * @param percent Character '%' to print.
 * @param count Pointer to the number of characters printed so far; updated by the function.
 */
void	ft_print_percent(char *buffer, int *i, char percent, int *count)
{
	buffer[(*i)++] = percent;
	*count += 1;
}
