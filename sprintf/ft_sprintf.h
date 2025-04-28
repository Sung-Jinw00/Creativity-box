/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:00:12 by locagnio          #+#    #+#             */
/*   Updated: 2024/11/04 14:00:12 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPRINTF_H
# define FT_SPRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include "libft_extras.h"

typedef struct s_struct
{
	const char	*str;
	char		*buffer;
	int			i;
	char		flags[7];
	int			nb1;
	int			nb2;
	int			zeros;
}	t_struct;

int			ft_digits(long n);
int			srch_flag(char *s, char c);
int			standard_conds(t_struct *v, int i);
int			print_this_bs(va_list args, t_struct *v);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_sprintf(char *buffer, const char *str, ...);
char		bonus_flag_finder(int i, t_struct *v);
char		*ft_putunbr_aspf(unsigned long n, t_struct *v);
void		ptr_print(size_t nb, t_struct *v);
void		ft_print_char(char c, t_struct *v, int *count);
void		ft_print_int(long nb, t_struct *v, int *count);
void		hexa_print(unsigned int nb, t_struct *v, char x);
void		ft_print_str(char *str, t_struct *v, int *count);
void		ft_print_ptr(size_t ptr, t_struct *v, int *count);
void		ft_print_uns_int(long nb, t_struct *v, int *count);
void		ft_putnbr(long n, t_struct *v, long base, long print);
void		ft_putstr(char *s, int *count, int limit, t_struct *v);
void		ft_print_hexa(unsigned int nb, t_struct *v, int i, int *count);
void		ft_print_percent(char *buffer, int *i, char percent, int *count);
t_struct	*flags(char c, t_struct *v);
t_struct	*flag_filter(int i, t_struct *v);
t_struct	*erase_flag(char erased, t_struct *v);
t_struct	*parse_nd_flags2(int *i, t_struct *v, va_list args);
t_struct	*keep_prior_flag(char erased, char prior, t_struct *v);

#endif