/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:52:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/30 22:43:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asprintf.h"

void	ft_putstr(char *s, int *count, int limit, char **buffer)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] && i < limit)
	{
		*buffer = add_char_realloc(*buffer, s[i]);
		*count += 1;
		i++;
	}
}

char	*ft_putunbr_aspf(unsigned long n, t_struct *v)
{
	if (n > 9)
		v->buffer = ft_putunbr_aspf(n / 10, v);
	if (!(n == 0 && srch_flag(v->flags, '.') && v->nb2 == 0))
	{
		n = n % 10 + '0';
		v->buffer = add_char_realloc(v->buffer, n);
	}
	return (v->buffer);
}

void	ft_putnbr(long n, t_struct *v, long base, long print)
{
	if (n < 0)
	{
		v->buffer = add_char_realloc(v->buffer, '-');
		n = -n;
	}
	else if (srch_flag(v->flags, '+'))
		v->buffer = add_char_realloc(v->buffer, '+');
	else if (srch_flag(v->flags, ' '))
		v->buffer = add_char_realloc(v->buffer, ' ');
	while (v->zeros-- > 0)
		v->buffer = add_char_realloc(v->buffer, '0');
	while (base <= n)
	{
		print = n;
		while (print >= base)
			print /= 10;
		print = print % 10 + '0';
		v->buffer = add_char_realloc(v->buffer, print);
		base *= 10;
	}
	print = n % 10 + '0';
	if (!(n == 0 && srch_flag(v->flags, '.') && v->nb2 == 0))
		v->buffer = add_char_realloc(v->buffer, print);
}

void	ptr_print(size_t nb, t_struct *v)
{
	char	*str;
	size_t	nb_cpy;
	size_t	base;

	nb_cpy = nb;
	base = 16;
	str = "0123456789abcdef";
	if (srch_flag(v->flags, '+'))
		v->buffer = add_char_realloc(v->buffer, '+');
	else if (srch_flag(v->flags, ' '))
		v->buffer = add_char_realloc(v->buffer, ' ');
	v->buffer = ft_strjoin_n_free(v->buffer, "0x", 1);
	while (v->zeros-- > 0)
		v->buffer = add_char_realloc(v->buffer, '0');
	while (!(base > nb || base == 0))
	{
		nb_cpy = nb;
		while (nb_cpy >= base)
			nb_cpy /= 16;
		v->buffer = add_char_realloc(v->buffer, str[nb_cpy % 16]);
		base *= 16;
	}
	v->buffer = add_char_realloc(v->buffer, str[nb_cpy % 16]);
}

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
