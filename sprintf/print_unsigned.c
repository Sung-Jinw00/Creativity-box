/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:02:22 by locagnio          #+#    #+#             */
/*   Updated: 2025/03/29 16:17:05 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

int	ft_len_unb(long nb, t_struct *v)
{
	int	len_unb;

	if (nb == 0 && srch_flag(v->flags, '.') && v->nb2 == 0)
		return (0);
	if (nb < 0)
		nb += (long)INT_MAX * 2 + 2;
	len_unb = ft_digits(nb);
	if (srch_flag(v->flags, '.') && v->nb2 > len_unb)
	{
		v->zeros = v->nb2 - len_unb;
		len_unb += v->zeros;
	}
	return (len_unb);
}

void	print_unb_if_no_0(t_struct *v, int len_unb, long nb)
{
	v->nb1 -= len_unb;
	if (!srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer[v->i++] = ' ';
	while (v->zeros-- > 0)
		v->buffer[v->i++] = '0';
	ft_putunbr_aspf(nb, v);
	if (srch_flag(v->flags, '-'))
		while (v->nb1-- > 0)
			v->buffer[v->i++] = ' ';
}

void	ft_print_uns_int(long nb, t_struct *v, int *count)
{
	int	len_unb;

	len_unb = ft_len_unb(nb, v);
	*count += len_unb;
	if (nb < 0)
		nb += (long)INT_MAX * 2 + 2;
	if (v->nb1 > len_unb)
	{
		*count += v->nb1 - len_unb;
		if (srch_flag(v->flags, '0') && !srch_flag(v->flags, '.'))
		{
			v->zeros += v->nb1 - len_unb;
			while (v->zeros-- > 0)
				v->buffer[v->i++] = '0';
			ft_putunbr_aspf(nb, v);
		}
		else
			print_unb_if_no_0(v, len_unb, nb);
	}
	else
	{
		while (v->zeros-- > 0)
			v->buffer[v->i++] = '0';
		ft_putunbr_aspf(nb, v);
	}
}
