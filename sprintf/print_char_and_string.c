/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_and_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:45:58 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/29 16:18:21 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

void	ft_print_char(char c, t_struct *v, int *count)
{
	if (v->nb1 > 0)
	{
		*count += v->nb1;
		if (srch_flag(v->flags, '-'))
			v->buffer[v->i++] = c;
		while (--v->nb1 > 0)
			v->buffer[v->i++] = ' ';
		if (!srch_flag(v->flags, '-'))
			v->buffer[v->i++] = c;
	}
	else
	{
		v->buffer[v->i++] = c;
		*count += 1;
	}
}

void	print_str_if_field(t_struct *v, int print_chars, char *str, int *count)
{
	if (v->nb1 >= print_chars)
		*count += v->nb1 - print_chars;
	if (srch_flag(v->flags, '-'))
		ft_putstr(str, count, print_chars, v);
	v->nb1 -= print_chars;
	while (v->nb1-- > 0)
		v->buffer[v->i++] = ' ';
	if (!srch_flag(v->flags, '-'))
		ft_putstr(str, count, print_chars, v);
}

void	ft_print_str(char *str, t_struct *v, int *count)
{
	int	print_chars;

	if (!str)
		str = "(null)";
	if (!ft_strcmp(str, "(null)") && srch_flag(v->flags, '.') && v->nb2 <= 5)
	{
		str = "";
		print_chars = 0;
	}
	else if (srch_flag(v->flags, '.')
		&& v->nb2 < (int)ft_strlen((const char *)str))
		print_chars = v->nb2;
	else
		print_chars = (int)ft_strlen((const char *)str);
	if (v->nb1 - print_chars > 0)
		print_str_if_field(v, print_chars, str, count);
	else
		ft_putstr(str, count, print_chars, v);
}

void	ft_print_percent(char *buffer, int *i, char percent, int *count)
{
	buffer[(*i)++] = percent;
	*count += 1;
}
