/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:05:11 by locagnio          #+#    #+#             */
/*   Updated: 2025/01/20 15:38:21 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asprintf.h"

/**
 * @brief Parses the format type and calls the corresponding print function.
 * 
 * Checks the character at index `i` in the format string and prints the
 * corresponding argument based on its format specifier (char, string,
 * pointer, integer, unsigned, hex, or percent).
 * 
 * @param i Index in the format string `v->str`.
 * @param count Pointer to the counter of written characters.
 * @param v Pointer to the structure containing the format string, buffer, and flags.
 * @param args Variadic argument list.
 */
void	parser(int i, int *count, t_struct *v, va_list args)
{
	if (v->str[i] == 'c')
		ft_print_char((char)va_arg(args, int), v, count);
	else if (v->str[i] == 's')
		ft_print_str(va_arg(args, char *), v, count);
	else if (v->str[i] == 'p')
		ft_print_ptr((size_t)va_arg(args, void *), v, count);
	else if (v->str[i] == 'd' || v->str[i] == 'i')
		ft_print_int(va_arg(args, int), v, count);
	else if (v->str[i] == 'u')
		ft_print_uns_int(va_arg(args, int), v, count);
	else if (v->str[i] == 'x' || v->str[i] == 'X')
		ft_print_hexa(va_arg(args, int), v, i, count);
	else if (v->str[i] == '%')
		ft_print_percent(&v->buffer, '%', count);
}

/**
 * @brief Parses flags, width, and precision for a given format specifier.
 * 
 * Processes characters after a '%' to detect flags, field width, precision,
 * and variable arguments. Adjusts the formatting structure accordingly and
 * then calls the parser for the actual type.
 * 
 * @param i Current index in the format string `v->str`.
 * @param count Pointer to the character count.
 * @param v Pointer to the structure storing flags, width, precision, and buffer.
 * @param args Variadic argument list.
 * 
 * @return The index in the format string after the current format specifier.
 */
int	parse_nd_flags(int i, int *count, t_struct *v, va_list args)
{
	while (!standard_conds(v, i))
	{
		if ((v->str[i] >= '1' && v->str[i] <= '9') || v->str[i] == '.'
			|| v->str[i] == '*')
			v = parse_nd_flags2(&i, v, args);
		else
		{
			v = flags(bonus_flag_finder(i, v), v);
			i += 1;
		}
	}
	if (v->nb1 < 0)
	{
		v = flags('-', v);
		v->nb1 = -v->nb1;
	}
	v = flag_filter(i, v);
	parser(i, count, v, args);
	return (i);
}

/**
 * @brief Iterates over the format string and prints characters or formats.
 * 
 * Goes through `v->str` and appends literal characters to the buffer.
 * When a '%' is found, it calls parse_nd_flags to handle the format specifier.
 * 
 * @param args Variadic argument list.
 * @param v Pointer to the formatting structure with buffer and flags.
 * 
 * @return Total number of characters written to the buffer.
 */
int	print_this_bs(va_list args, t_struct *v)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (v->str[i])
	{
		if (v->str[i] == '%')
			i = parse_nd_flags(i + 1, &count, v, args);
		else
		{
			v->buffer = add_char_realloc(v->buffer, v->str[i]);
			count++;
		}
		i++;
	}
	return (count);
}

/**
 * @brief Main function similar to printf but allocates a dynamic buffer.
 * 
 * Formats the input string with the provided arguments and writes the result
 * to a dynamically allocated buffer. The user is responsible for freeing
 * the buffer after use.
 * 
 * @param buffer Pointer to a pointer to char. The function allocates and fills this buffer.
 * @param str Format string (like printf).
 * @param ... Variadic arguments corresponding to the format specifiers.
 * 
 * @return Number of characters written into the buffer.
 */
int	ft_asprintf(char **buffer, const char *str, ...)
{
	va_list		args;
	t_struct	v;
	int			count;

	if (!str)
		return (0);
	v = (t_struct){0};
	v.str = str;
	va_start(args, str);
	count = print_this_bs(args, &v);
	*buffer = v.buffer;
	va_end(args);
	return (count);
}

/* #include <limits.h>
#include <stdio.h>

int	main(void)
{
	char *buff = NULL;
	char str[] = "Yes do it after minishell maybe in your vacations";

	printf("original : %d\n", asprintf(&buff, "original : test = |%s|\n", str));
	fflush(stdout);
	printf("%s", buff);
	fflush(stdout);
	free(buff);
	printf("copie    : %d\n", ft_asprintf(&buff, "copie    : test = |%s|\n",
	str));
	fflush(stdout);
	printf("%s", buff);
	free(buff);
	printf("\n\n\n");
	return (0);
} */

/*
"%#-76.67x%-178c%#126.17x%-178.97%%-80.63i" ,2705358650u,-128,4292242043u,
-156704363
"%-26.85u%+#100.2%%#0130.74x%#59.63X%086x" ,602620792u,1774300267u,835967277u
,2887108754u
"%64.79u%#168.142x%110c" ,1663238694u,2980990023u,-98
"%--99p%94.103s%181.150x% 21d%+16.%" ,17804030627542756824lu,"\n#\fj<Oil\ft7\
tj&^|ddD80t\nIL+,",184469023u,1795574960
"%#73.181X%--47.192X" ,3720784993u,3491116485u
"%-#88.82x" ,3532279970u
"%#196.53X" ,3130516526u
"%  130.137%%#102.18x%059.56u%#167.193X" ,2661836307u,3540858512u,1574239099u
"% 171.152d%p%0197.33u%0+#131.71%" ,2055571139,6109035435017027490lu,
1457993623u
"%98p%147p%#43.85x%++197.126i%195.u" ,17422923310524768300lu,
8561336791391148915lu,839088623u,-1692713526,2802635555u
"%.80s% # 177.44%%#093.105X" ,"Nhfxl\\f}EJyv:>\tgq7kFZ&VUM",392767992u
"%#38.119x%120p%155c%-147.d" ,4216448853u,12423865882424705706lu,-98,
-1967106559
"%48c%-#184.95X%185p" ,48,856683944u,9125943193160606356lu */