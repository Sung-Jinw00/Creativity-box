/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:08:53 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/29 16:23:15 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

char	*ft_putnbr_base_aspf(char *buffer, int *i, unsigned int nbr, char *base)
{
	if (nbr >= 16)
		buffer = ft_putnbr_base_aspf(buffer, i, nbr / 16, base);
	buffer[(*i)++] = base[nbr % 16];
	return (buffer);
}

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
