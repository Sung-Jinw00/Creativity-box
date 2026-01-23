/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:52:22 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:25:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

/**
 * @brief Writes a string to the buffer up to a specified limit.
 * 
 * Updates the buffer index and the total character count. Stops at the limit or null terminator.
 * 
 * @param s String to print.
 * @param count Pointer to the number of characters printed so far; updated by the function.
 * @param limit Maximum number of characters to print from the string.
 * @param v Pointer to the formatting structure containing the buffer and current index.
 */
void	ft_putstr(char *s, int *count, int limit, t_struct *v)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] && i < limit)
	{
		v->buffer[v->i++] = s[i];
		*count += 1;
		i++;
	}
}

/**
 * @brief Recursively prints an unsigned long integer to the buffer.
 * 
 * Considers the '.' precision flag to skip printing zero when precision is 0.
 * 
 * @param n Unsigned long integer to print.
 * @param v Pointer to the formatting structure containing the buffer, flags, and zeros.
 * 
 * @return char* Pointer to the buffer after printing.
 */
char	*ft_putunbr_aspf(unsigned long n, t_struct *v)
{
	if (n > 9)
		v->buffer = ft_putunbr_aspf(n / 10, v);
	if (!(n == 0 && srch_flag(v->flags, '.') && v->nb2 == 0))
	{
		n = n % 10 + '0';
		v->buffer[v->i++] = n;
	}
	return (v->buffer);
}

/**
 * @brief Prints a signed long integer to the buffer with optional base and leading zeros.
 * 
 * Handles negative numbers, '+' and ' ' flags, and leading zeros based on precision.
 * 
 * @param n Long integer to print.
 * @param v Pointer to the formatting structure containing buffer, flags, and zeros.
 * @param base Numeric base to use for printing (usually 10).
 * @param print Temporary variable used for calculation (should be initialized to 0).
 */
void	ft_putnbr(long n, t_struct *v, long base, long print)
{
	if (n < 0)
	{
		v->buffer[v->i++] = '-';
		n = -n;
	}
	else if (srch_flag(v->flags, '+'))
		v->buffer[v->i++] = '+';
	else if (srch_flag(v->flags, ' '))
		v->buffer[v->i++] = ' ';
	while (v->zeros-- > 0)
		v->buffer[v->i++] = '0';
	while (base <= n)
	{
		print = n;
		while (print >= base)
			print /= 10;
		print = print % 10 + '0';
		v->buffer[v->i++] = print;
		base *= 10;
	}
	print = n % 10 + '0';
	if (!(n == 0 && srch_flag(v->flags, '.') && v->nb2 == 0))
		v->buffer[v->i++] = print;
}

/**
 * @brief Prints a pointer value in hexadecimal format with "0x" prefix and optional flags.
 * 
 * Handles '+' and ' ' flags, field width padding using `zeros`, and hexadecimal conversion.
 * 
 * @param nb Pointer value to print.
 * @param v Pointer to the formatting structure containing buffer, flags, and zeros.
 */
void	ptr_print(size_t nb, t_struct *v)
{
	char	*str;
	size_t	nb_cpy;
	size_t	base;

	nb_cpy = nb;
	base = 16;
	str = "0123456789abcdef";
	if (srch_flag(v->flags, '+'))
		v->buffer[v->i++] = '+';
	else if (srch_flag(v->flags, ' '))
		v->buffer[v->i++] = ' ';
	v->buffer[v->i++] = '0';
	v->buffer[v->i++] = 'x';
	while (v->zeros-- > 0)
		v->buffer[v->i++] = '0';
	while (!(base > nb || base == 0))
	{
		nb_cpy = nb;
		while (nb_cpy >= base)
			nb_cpy /= 16;
		v->buffer[v->i++] = str[nb_cpy % 16];
		base *= 16;
	}
	v->buffer[v->i++] = str[nb_cpy % 16];
}

/**
 * @brief Computes the length of a null-terminated string.
 * 
 * Returns 0 if the string pointer is NULL.
 * 
 * @param s Pointer to the string.
 * 
 * @return size_t Number of characters in the string (excluding the null terminator).
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
