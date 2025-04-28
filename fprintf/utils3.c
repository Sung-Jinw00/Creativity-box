/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:08:53 by locagnio          #+#    #+#             */
/*   Updated: 2025/04/18 23:56:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

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

void	ft_putnbr_base(unsigned int nbr, char *base, int fd)
{
	if (nbr >= 16)
		ft_putnbr_base(nbr / 16, base, fd);
	write(fd, &base[nbr % 16], 1);
}

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
