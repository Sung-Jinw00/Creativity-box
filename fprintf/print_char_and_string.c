/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_and_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:45:58 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:30:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

/**
 * @brief Prints a single character with optional width and left/right alignment.
 * 
 * Supports the '-' flag for left-alignment. Pads with spaces if the width (`nb1`) is greater than 1.
 * 
 * @param c Character to print.
 * @param v Formatting structure containing flags, width, and file descriptor.
 * @param count Pointer to the number of characters printed; updated by this function.
 */
void	ft_print_char(char c, t_struct v, int *count)
{
	if (v.nb1 > 0)
	{
		*count += v.nb1;
		if (srch_flag(v.flags, '-'))
			write(v.fd, &c, 1);
		while (--v.nb1 > 0)
			write(v.fd, " ", 1);
		if (!srch_flag(v.flags, '-'))
			write(v.fd, &c, 1);
	}
	else
	{
		write(v.fd, &c, 1);
		*count += 1;
	}
}

/**
 * @brief Helper function to print a string when a field width is specified.
 * 
 * Handles left-alignment ('-') and pads with spaces. Prints at most `print_chars` characters
 * from the string.
 * 
 * @param v Formatting structure containing flags, width, and file descriptor.
 * @param print_chars Maximum number of characters to print from the string.
 * @param str String to print.
 * @param count Pointer to the number of characters printed; updated by this function.
 */
void	print_str_if_field(t_struct v, int print_chars, char *str, int *count)
{
	if (v.nb1 >= print_chars)
		*count += v.nb1 - print_chars;
	if (srch_flag(v.flags, '-'))
		ft_putstr(str, count, print_chars, v.fd);
	v.nb1 -= print_chars;
	while (v.nb1-- > 0)
		write(v.fd, " ", 1);
	if (!srch_flag(v.flags, '-'))
		ft_putstr(str, count, print_chars, v.fd);
}

/**
 * @brief Prints a string with optional width, precision, and left/right alignment.
 * 
 * Supports the '-' flag for left-alignment and '.' for precision. Prints "(null)" if the
 * string pointer is NULL, respecting precision rules.
 * 
 * @param str String to print.
 * @param v Formatting structure containing flags, width, precision, and file descriptor.
 * @param count Pointer to the number of characters printed; updated by this function.
 */
void	ft_print_str(char *str, t_struct v, int *count)
{
	int	print_chars;

	if (!str)
		str = "(null)";
	if (!ft_strcmp(str, "(null)") && srch_flag(v.flags, '.') && v.nb2 <= 5)
	{
		str = "";
		print_chars = 0;
	}
	else if (srch_flag(v.flags, '.')
		&& v.nb2 < (int)ft_strlen((const char *)str))
		print_chars = v.nb2;
	else
		print_chars = (int)ft_strlen((const char *)str);
	if (v.nb1 - print_chars > 0)
		print_str_if_field(v, print_chars, str, count);
	else
		ft_putstr(str, count, print_chars, v.fd);
}

/**
 * @brief Prints the '%' character.
 * 
 * Simply writes '%' to the specified file descriptor and increments the character count.
 * 
 * @param percent Character to print (always '%').
 * @param count Pointer to the number of characters printed; updated by this function.
 * @param fd File descriptor where the character will be written.
 */
void	ft_print_percent(char percent, int *count, int fd)
{
	write(fd, &percent, 1);
	*count += 1;
}
