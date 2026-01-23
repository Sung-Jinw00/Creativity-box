/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:52:22 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:34:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

/**
 * @brief Writes a string to the specified file descriptor up to a limit of characters.
 *
 * @param s The string to write.
 * @param count Pointer to the total character count; incremented by the number of characters written.
 * @param limit Maximum number of characters to write.
 * @param fd File descriptor where the string will be written.
 */
void	ft_putstr(char *s, int *count, int limit, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] && i < limit)
	{
		write(fd, &s[i], 1);
		*count += 1;
		i++;
	}
}

/**
 * @brief Recursively prints an unsigned long number to the specified file descriptor.
 *
 * Handles precision flags: if the '.' flag is set and nb2 is zero, prints nothing for 0.
 *
 * @param n The unsigned long number to print.
 * @param v Formatting structure containing flags, zeros, nb2, and fd.
 */
void	ft_putunbr(unsigned long n, t_struct v)
{
	if (n > 9)
		ft_putunbr(n / 10, v);
	if (!(n == 0 && srch_flag(v.flags, '.') && v.nb2 == 0))
	{
		n = n % 10 + '0';
		write(v.fd, &n, 1);
	}
}

/**
 * @brief Prints a signed long number to the file descriptor with formatting.
 *
 * Supports sign flags ('+', ' '), leading zeros, and precision handling.
 *
 * @param n The number to print.
 * @param v Formatting structure containing flags, zeros, nb2, and fd.
 * @param base Base used for printing (typically 10).
 * @param print Temporary variable for calculating digits.
 */
void	ft_putnbr(long n, t_struct v, long base, long print)
{
	if (n < 0)
	{
		write(v.fd, "-", 1);
		n = -n;
	}
	else if (srch_flag(v.flags, '+'))
		write(v.fd, "+", 1);
	else if (srch_flag(v.flags, ' '))
		write(v.fd, " ", 1);
	while (v.zeros-- > 0)
		write(v.fd, "0", 1);
	while (base <= n)
	{
		print = n;
		while (print >= base)
			print /= 10;
		print = print % 10 + '0';
		write(v.fd, &print, 1);
		base *= 10;
	}
	print = n % 10 + '0';
	if (!(n == 0 && srch_flag(v.flags, '.') && v.nb2 == 0))
		write(v.fd, &print, 1);
}

/**
 * @brief Prints a pointer in hexadecimal format with "0x" prefix.
 *
 * Supports flags '+' and ' ', and leading zeros for precision.
 *
 * @param nb The pointer value to print.
 * @param v Formatting structure containing flags, zeros, nb2, and fd.
 */
void	ptr_print(size_t nb, t_struct v)
{
	char	*str;
	size_t	nb_cpy;
	size_t	base;

	nb_cpy = nb;
	base = 16;
	str = "0123456789abcdef";
	if (srch_flag(v.flags, '+'))
		write(v.fd, "+", 1);
	else if (srch_flag(v.flags, ' '))
		write(v.fd, " ", 1);
	write(v.fd, "0x", 2);
	while (v.zeros-- > 0)
		write(v.fd, "0", 1);
	while (!(base > nb || base == 0))
	{
		nb_cpy = nb;
		while (nb_cpy >= base)
			nb_cpy /= 16;
		write(v.fd, &str[nb_cpy % 16], 1);
		base *= 16;
	}
	write(v.fd, &str[nb % 16], 1);
}

/**
 * @brief Returns the length of a null-terminated string.
 *
 * @param s The string whose length is computed.
 * @return size_t The length of the string; returns 0 if s is NULL.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
