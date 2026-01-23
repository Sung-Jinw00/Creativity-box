/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:08:53 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:26:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

/**
 * @brief Recursively prints an unsigned integer in a given base to a buffer.
 * 
 * Used for hexadecimal printing with lowercase or uppercase digits.
 * 
 * @param buffer Output buffer where the number will be written.
 * @param i Pointer to the current index in the buffer; updated by the function.
 * @param nbr Unsigned integer to print.
 * @param base String representing the digits of the numeric base (e.g., "0123456789abcdef").
 * 
 * @return char* Pointer to the buffer after printing.
 */
char	*ft_putnbr_base_aspf(char *buffer, int *i, unsigned int nbr, char *base)
{
	if (nbr >= 16)
		buffer = ft_putnbr_base_aspf(buffer, i, nbr / 16, base);
	buffer[(*i)++] = base[nbr % 16];
	return (buffer);
}

/**
 * @brief Prints an unsigned integer in hexadecimal format with optional "0x"/"0X" prefix.
 * 
 * Handles '#' flag for prefix, '0' padding using the `zeros` field, and uppercase/lowercase output.
 * 
 * @param nb Unsigned integer to print in hexadecimal.
 * @param v Pointer to the formatting structure containing buffer, flags, and zeros.
 * @param x Format specifier character ('x' for lowercase, 'X' for uppercase).
 */
void	hexa_print(unsigned int nb, t_struct *v, char x)
{
	char	*str;

	if (x == 'x' && srch_flag(v->flags, '#'))
	{
		v->buffer[v->i++] = '0';
		v->buffer[v->i++] = 'x';
	}
	else if (x == 'X' && srch_flag(v->flags, '#'))
	{
		v->buffer[v->i++] = '0';
		v->buffer[v->i++] = 'X';
	}
	while (v->zeros-- > 0)
		v->buffer[v->i++] = '0';
	if (x == 'x')
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	v->buffer = ft_putnbr_base_aspf(v->buffer, &v->i, nb, str);
}


/**
 * @brief Counts the number of digits in a signed long integer.
 * 
 * Includes space for the sign if the number is negative.
 * 
 * @param n Signed long integer to count digits for.
 * 
 * @return int Number of digits including sign if negative.
 */
int	ft_digits(long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

/**
 * @brief Compares two strings for equality.
 * 
 * Returns 0 if both strings are equal, a positive or negative value if they differ.
 * Handles NULL pointers: returns 0 if both are NULL, 1 if only one is NULL.
 * 
 * @param s1 First string to compare.
 * @param s2 Second string to compare.
 * 
 * @return int 0 if strings are equal, non-zero otherwise.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	else if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
