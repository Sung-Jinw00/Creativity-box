/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:08:53 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:34:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

/**
 * @brief Compares two strings similarly to strcmp.
 *
 * @param s1 First string to compare.
 * @param s2 Second string to compare.
 * @return int 0 if strings are equal, non-zero difference otherwise. Returns 1 if either string is NULL.
 */
int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}


/**
 * @brief Recursively prints an unsigned integer in a given base.
 *
 * @param nbr Number to print.
 * @param base String representing the base characters (e.g., "0123456789abcdef").
 * @param fd File descriptor where the number will be printed.
 */
void	ft_putnbr_base(unsigned int nbr, char *base, int fd)
{
	if (nbr >= 16)
		ft_putnbr_base(nbr / 16, base, fd);
	write(fd, &base[nbr % 16], 1);
}

/**
 * @brief Prints an unsigned integer in hexadecimal format with optional "0x" or "0X" prefix.
 *
 * Supports the '#' flag for prefix, and leading zeros for precision.
 *
 * @param nb Number to print.
 * @param v Formatting structure containing flags, zeros, nb2, and fd.
 * @param x Character 'x' or 'X' to indicate lowercase or uppercase hexadecimal.
 */
void	hexa_print(unsigned int nb, t_struct v, char x)
{
	char	*str;

	if (x == 'x' && srch_flag(v.flags, '#'))
		write(v.fd, "0x", 2);
	else if (x == 'X' && srch_flag(v.flags, '#'))
		write(v.fd, "0X", 2);
	while (v.zeros-- > 0)
		write(v.fd, "0", 1);
	if (x == 'x')
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	ft_putnbr_base(nb, str, v.fd);
}

/**
 * @brief Returns the number of decimal digits in a signed long number.
 *
 * Accounts for the negative sign as an extra digit.
 *
 * @param n Number to evaluate.
 * @return int Number of digits, including sign if negative.
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
