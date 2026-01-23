/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:08:53 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:55:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asprintf.h"

/**
 * @brief Converts a number to hexadecimal string and writes it to buffer.
 * 
 * @param buffer Buffer pointer.
 * @param nbr Number to convert.
 * @param base String of hex digits (lower or upper case).
 * 
 * @return Updated buffer pointer.
 */
char	*ft_putnbr_base_aspf(char *buffer, unsigned int nbr, char *base)
{
	if (nbr >= 16)
		buffer = ft_putnbr_base_aspf(buffer, nbr / 16, base);
	buffer = add_char_realloc(buffer, base[nbr % 16]);
	return (buffer);
}

/**
 * @brief Prints a hexadecimal number with flags, precision, and optional '0x'/'0X'.
 * 
 * @param nb Number to print.
 * @param v Pointer to formatting structure.
 * @param x Format specifier 'x' or 'X'.
 */
void	hexa_print(unsigned int nb, t_struct *v, char x)
{
	char	*str;

	if (x == 'x' && srch_flag(v->flags, '#'))
		v->buffer = ft_strjoin_n_free(v->buffer, "0x", 1);
	else if (x == 'X' && srch_flag(v->flags, '#'))
		v->buffer = ft_strjoin_n_free(v->buffer, "0X", 1);
	while (v->zeros-- > 0)
		v->buffer = add_char_realloc(v->buffer, '0');
	if (x == 'x')
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	v->buffer = ft_putnbr_base_aspf(v->buffer, nb, str);
}

/**
 * @brief Returns the number of digits in a signed long number.
 * 
 * @param n Number to count digits.
 * 
 * @return Number of digits.
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
 * @brief Adds a character to the buffer, reallocating memory.
 * 
 * @param buffer Buffer pointer.
 * @param c Character to add.
 * 
 * @return Updated buffer pointer.
 */
char	*add_char_realloc(char *buffer, char c)
{
	int	newlen;

	newlen = ft_strlen(buffer) + 1;
	buffer = ft_upgrade_realloc(buffer, newlen);
	buffer[newlen - 1] = c;
	return (buffer);
}
