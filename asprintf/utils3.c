/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:08:53 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/30 22:44:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asprintf.h"

char	*ft_putnbr_base_aspf(char *buffer, unsigned int nbr, char *base)
{
	if (nbr >= 16)
		buffer = ft_putnbr_base_aspf(buffer, nbr / 16, base);
	buffer = add_char_realloc(buffer, base[nbr % 16]);
	return (buffer);
}

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

char	*add_char_realloc(char *buffer, char c)
{
	int	newlen;

	newlen = ft_strlen(buffer) + 1;
	buffer = ft_upgrade_realloc(buffer, newlen);
	buffer[newlen - 1] = c;
	return (buffer);
}
