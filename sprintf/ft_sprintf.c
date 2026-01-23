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

#include "ft_sprintf.h"

/**
 * @brief Parses a single format specifier and prints the corresponding argument.
 * 
 * Checks the character at position `i` in the format string and calls
 * the appropriate printing function for characters, strings, pointers,
 * integers, unsigned integers, hexadecimal numbers, or the percent sign.
 * 
 * @param i Index of the format specifier in the format string.
 * @param count Pointer to an integer storing the number of characters printed so far.
 * @param v Pointer to a structure containing buffer, format string, and formatting options.
 * @param args Variable argument list containing the values to format.
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
		ft_print_percent(v->buffer, &v->i, '%', count);
}

/**
 * @brief Parses non-standard flags, width, precision, and other formatting options.
 * 
 * Processes flags, width, precision, and bonus flags. After parsing,
 * it calls the `parser` function to print the corresponding argument.
 * 
 * @param i Current index in the format string.
 * @param count Pointer to the number of characters printed so far.
 * @param v Pointer to the formatting structure.
 * @param args Variable argument list for values corresponding to '*' width/precision specifiers.
 * 
 * @return int Updated index in the format string after parsing.
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
 * @brief Processes the entire format string and prints all characters and formatted arguments.
 * 
 * Iterates through the format string. For each '%' character, it calls
 * `parse_nd_flags` to handle the format specifier; otherwise, it directly copies the
 * character to the buffer.
 * 
 * @param args Variable argument list containing values for format specifiers.
 * @param v Pointer to the formatting structure containing the format string and buffer.
 * 
 * @return int Total number of characters written to the buffer.
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
			v->buffer[v->i++] = v->str[i];
			count++;
		}
		i++;
	}
	return (count);
}

/**
 * @brief Stores the formatted result into a preallocated string like sprintf.
 * 
 * Behaves similarly to `sprintf` from the C standard library. Stores the
 * formatted output in the provided buffer.
 * 
 * @param buffer Preallocated string where the formatted output will be stored.
 * @param str Format string containing literal text and format specifiers.
 * @param ... Additional arguments corresponding to the format specifiers.
 * 
 * @return int Number of characters written to the buffer (excluding the null terminator).
 * 
 * @note The user must ensure the buffer is large enough to hold the formatted result.
 */
int	ft_sprintf(char *buffer, const char *str, ...)
{
	va_list		args;
	t_struct	v;
	int			count;

	if (!str)
		return (0);
	v = (t_struct){0};
	v.str = str;
	va_start(args, str);
	v.buffer = buffer;
	count = print_this_bs(args, &v);
	v.buffer[v.i] = 0;
	va_end(args);
	return (count);
}

/* #include <limits.h>
#include <stdio.h>

int	main(void)
{
	char buff[100];
	int d = 255;

	printf("original : %d\n", sprintf(buff, "original : test = |%p|\n", d));
	fflush(stdout);
	printf("%s", buff);
	fflush(stdout);
	printf("copie    : %d\n", ft_sprintf(buff, "copie    : test = |%p|\n", d));
	fflush(stdout);
	printf("%s", buff);
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