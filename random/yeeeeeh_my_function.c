/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_len_rep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:18:12 by marvin            #+#    #+#             */
/*   Updated: 2025/04/14 21:18:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/**
 * If you want to clear what the terminal display, use this :
 * clear
 * 
 * If you want to use the function you need to compile it with this :
 * cc (function_name).c
 * 
 * And execute it with this :
 * ./a.out (cylinder_height) (cylinder_divizor) (height_letters) (nb_lines) (barcode_height)
 * 
 * If you have any doubts, just do :
 * ./a.out
 * it will display the prompt on how to use the function.
 * 
 * 
 * Here are the formulas if you want to use them to :
 * - find the right cylinder height :
 * 		right_height_cylinder = ((height_letters * nb_lines) + barcode_height) * cylinder_divizor
 * - find the result without a bar code :
 * 		result = ((cylinder_height / cylinder_divizor) - (height_letters * nb_lines)) / (nb_lines + 1)
 * - find the result with a bar code :
 * 		result = ((cylinder_height / cylinder_divizor) - (height_letters * nb_lines + barcode_height)) / (nb_lines + 2)
 */

typedef	struct s_datas
{
	double cylinder_height;
	int cylinder_divizor;
	double height_letters;
	int nb_lines;
	double barcode_height;
}	t_datas;

#define UNDERLINE     "\033[4m"
#define RESET         "\033[0m"

void	usage(void)
{
	printf(UNDERLINE"The function needs 5 values :\n"RESET);
	printf("1) The cylinder's height in milimeters.\n");
	printf("2) The cylinder's divizor.\n");
	printf("3) The height of the text in milimeters.\n");
	printf("4) The number of lines.\n");
	printf("5) (Optionnal) The barcode height in milimeters.\n");
}

double	find_len_rep(t_datas data)
{
	double len_one_rep, total_height_text, empty_space_left, answer;

	if (!data.cylinder_height)
		return (printf("No cylinder.\n"), 0);
	if (data.cylinder_divizor <= 0)
		return (printf("Division by zero or a negative number.\n"), 0);
	len_one_rep = data.cylinder_height / data.cylinder_divizor;
	printf("Len_one_rep = cylinder_height / cylinder_divizor\n");
	printf("\t    = %.3f / %d\n", data.cylinder_height, data.cylinder_divizor);
	printf("\t    = %.3f mm\n\n", len_one_rep);
	total_height_text = (data.height_letters * data.nb_lines) + data.barcode_height;
	printf("Total_height_text = (height_letters * nb_lines) + barcode_height\n");
	printf("\t\t  = (%.3f * %d) + %.3f\n", data.height_letters, data.nb_lines, data.barcode_height);
	printf("\t\t  = %.3f mm\n\n", total_height_text);
	empty_space_left = len_one_rep - total_height_text;
	printf("Empty_space_left = len_one_sep - total_height_text\n");
	printf("\t\t = %.3f - %.3f\n", len_one_rep, total_height_text);
	printf("\t\t = %.3f mm\n\n", empty_space_left);
	if (empty_space_left < 0)
		return (printf("Negative space left, the cylinder should be at least"),
			printf(" %.3f mm high\nto fit the text!\n",
				total_height_text * data.cylinder_divizor), 0);
	if (data.barcode_height)
	{
		answer = empty_space_left / (data.nb_lines + 2);
		printf("Space left between lines = empty_space_left / (nb_lines + 2)\n");
		printf("\t\t\t = %.3f / (%d + 2)\n", empty_space_left, data.nb_lines);
		printf("\t\t\t = %.3f mm\n\n", answer);
		return (empty_space_left / (data.nb_lines + 2));
	}
	answer = empty_space_left / (data.nb_lines + 1);
	printf("Space left between lines = empty_space_left / (nb_lines + 1)\n");
	printf("\t\t\t = %.3f / (%d + 1)\n", empty_space_left, data.nb_lines);
	printf("\t\t\t = %.3f mm\n\n", answer);
	return (empty_space_left / (data.nb_lines + 1));
}

int main(int ac, char **av)
{
	t_datas data = (t_datas){0};

	if (ac == 5 || ac == 6)
	{
		data.cylinder_height = atof(av[1]);
		data.cylinder_divizor = atoi(av[2]);
		if (data.cylinder_divizor < 1)
			data.cylinder_divizor = 1;
		data.height_letters = atof(av[3]);
		data.nb_lines = atoi(av[4]);
		if (data.nb_lines < 0)
			data.nb_lines = 0;
		if (ac == 6)
			data.barcode_height = atof(av[5]);

		printf(UNDERLINE"Datas :\n"RESET"1) Cylinder_height = %.3f mm\n2) Cylinder_divizor = %d\n3) Height_letters = %.3f mm\n4) Nb_lines = %d\n5) Barcode_height = %.3f mm\n\n\n\n",
			data.cylinder_height, data.cylinder_divizor, data.height_letters, data.nb_lines, data.barcode_height);
			printf(UNDERLINE"Calculations :\n"RESET);
			double answer = find_len_rep(data);
		if (answer)
			printf("Answer = %.3f mm\n", answer);
	}
	else
		return (usage(), 1);
	return (0);
}
