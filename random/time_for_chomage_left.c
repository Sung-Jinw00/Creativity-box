/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_for_chomage_left.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:44:21 by marvin            #+#    #+#             */
/*   Updated: 2025/08/30 14:43:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Reset all text formatting */
# ifndef RESET
#  define RESET				"\033[0m"
# endif

/* Cyan text */
# ifndef CYAN
#  define CYAN				"\033[36m"
# endif

/* Green text */
# ifndef GREEN
#  define GREEN				"\033[32m"
# endif

/* Bold text */
# ifndef BOLD
#  define BOLD				"\033[1m"
# endif

/* Underlined text */
# ifndef UNDERLINE
#  define UNDERLINE			"\033[4m"
# endif

/* Red text */
# ifndef RED
#  define RED				"\033[31m"
# endif

/* Red text */
# ifndef T_DAY
#  define T_DAY				24 * 60 * 60
# endif

#include <stdio.h>
#include <math.h>
#include <time.h>

int	get_decimal(double time)
{
	int decimal = (int)((time - (int)time) * 100);
	if (decimal % 10 == 9)
		decimal++;
	return (decimal);
}

void	time_left(int limit_d, double limit_h)
{
	if (limit_d > 65)
		limit_d = 65;
	if (limit_d <= 0 && limit_h <= 0)
		printf(BOLD UNDERLINE"\nJours restants pour le chomage :"RESET GREEN" 0d !\n"CYAN BOLD UNDERLINE"Heures restantes pour le chomage :"RESET GREEN" 0h !\n"RESET);
	else if (limit_d <= 0)
		printf(BOLD UNDERLINE"\nJours restants pour le chomage :"RESET GREEN" 0d !\n"CYAN BOLD UNDERLINE"Heures restantes pour le chomage :"RESET" %dh%02d\n"RESET, (int)limit_h, get_decimal(limit_h));
	else if (limit_h <= 0)
		printf(BOLD UNDERLINE"\nJours restants pour le chomage :"RESET" %dd\n"CYAN BOLD UNDERLINE"Heures restantes pour le chomage :"RESET GREEN" 0h !\n"RESET, limit_d);
	else
		printf(BOLD UNDERLINE"\nJours restants pour le chomage :"RESET" %dd\n"CYAN BOLD UNDERLINE"Heures restantes pour le chomage :"RESET" %dh%02d\n"RESET, limit_d, (int)limit_h, get_decimal(limit_h));
}


void print_hours_worked(char *colour, double *how, int i, int j, double nb)
{
	if (how)
	{
		printf(RESET"%s", colour);
		if (!how[i + j])
			printf("     /     ");
		else if (!get_decimal(how[i + j]))
			printf("     %dh    ", (int)how[i + j]);
		else
			printf("    %dh%02d   ", (int)how[i + j], get_decimal(how[i + j]));
		if ((int)how[i + j] >= 10)
			printf(CYAN"|");
		else
			printf(CYAN" |");
	}
	else
	{
		printf(GREEN);
		if (!get_decimal(nb))
			printf("  %dh  ", (int)nb);
		else
			printf(" %dh%02d ", (int)nb, get_decimal(nb));
		if (nb >= 10)
			printf(CYAN"|");
		else
			printf(CYAN" |");
	}
}

void	blank_print(int start_day, char **days, int i, int cur_days, double *how, double *limit_h)
{
	if (!start_day)
		return ;
	printf(CYAN"──────────────────────────────────────────────────\n");
	printf("|");
	for (int j = 0; j < 7; j++)
		printf(" "BOLD"%s"RESET CYAN" |", days[j]);
	printf("\n──────────────────────────────────────────────────\n");
	printf("|      |      |      |      |      |      |      |\n");
	printf("|");
	for (int j = 0; j < 7; j++)
	{
		if (j >= start_day)
			printf("      |");
		else if (i + j < cur_days)
			print_hours_worked(GREEN, how, i, j, 0);
		else
			print_hours_worked(RED, how, i, j, 0);
		*limit_h -= how[i + j];
		if (get_decimal(*limit_h) >= 60)
			*limit_h -= 0.40;
	}
	printf("\n|      |      |      |      |      |      |      |\n");
	i += 7;
	printf("──────────────────────────────────────────────────\n");
}

void	formated_date(char date_str[6], time_t cur_date)
{
	struct tm tm_day = *localtime(&cur_date);
	strftime(date_str, 6, "%d/%m", &tm_day);
}

void	how_much_time_left(double *how, int start_day, int cur_days, int limit_d, double limit_h, time_t cur_date)
{
	int rest_days = 0;

	if (start_day < 0)
	{
		printf(RED"Error : Invalid day.\n"RESET);
		return ;
	}
	char date_str[6] = {0};
	int i = 0;
	char *days[8] = {"Lun.", "Mar.", "Mer.", "Jeu.", "Ven.", "Sam.", "Dim.", "Total"};

	cur_days += start_day;
	while (i < cur_days)
	{
		if (!how[i] && !how[i + 1] && !how[i + 2])
			break ;
		for (int j = 0; j < 7 && i + j < cur_days; j++)
		{
			if (!how[i + j])
				rest_days++;
		}
		printf(CYAN"────────────────────────────────────────────────────────────────────────────────────────────────────\n");
		printf("|");
		for (int j = 0; j < 7; j++)
		{
			formated_date(date_str, cur_date);
			printf(" "BOLD"%s %s"RESET CYAN" |", days[j], date_str);
			cur_date += T_DAY;
		}
		printf(" "BOLD"%s"RESET CYAN" |", days[7]);
		printf("\n────────────────────────────────────────────────────────────────────────────────────────────────────\n");
		printf("|            |            |            |            |            |            |            |       |\n");
		printf("|");
		double total_h_week = 0;
		for (int j = 0; j < 7; j++)
		{
			if (i < 7 && j < start_day)
			{
				while (j++ < start_day)
					printf("      |");
				j--;
			}
			if (get_decimal(how[i + j]) >= 60)
				how[i + j] -= 0.40;
			if (i + j < cur_days)
				print_hours_worked(GREEN, how, i, j, 0);
			else
				print_hours_worked(RED, how, i, j, 0);
			limit_h -= how[i + j];
			if (get_decimal(limit_h) >= 60)
				limit_h -= 0.40;
			total_h_week += how[i + j];
			if (get_decimal(total_h_week) >= 60)
				total_h_week += 0.40;
		}
		print_hours_worked(NULL, NULL, 0, 0, total_h_week);
		printf("\n|            |            |            |            |            |            |            |       |\n");
		i += 7;
	}
	printf("────────────────────────────────────────────────────────────────────────────────────────────────────\n");
	limit_d += rest_days;
	blank_print(start_day, days, i, cur_days, how, &limit_h);
	time_left(limit_d, limit_h);
}

#include <time.h>

int	get_day_diff(void)
{
	struct tm given_date = {0};
    time_t now, given_time;
    double seconds;
    int days_diff;

	//──────────────── Change day here ────────────────//
    given_date.tm_mday = 16 - 1;       // Day
    given_date.tm_mon  = 06 - 1;       // month
    given_date.tm_year = 2025 - 1900;  // Year

    // Convertir struct tm en time_t
    given_time = mktime(&given_date);

    // Obtenir l'heure actuelle
    time(&now);

    // Calculer la différence en secondes
    seconds = difftime(now, given_time);

    // Convertir en jours
    days_diff = (int)(seconds / (60 * 60 * 24));
	return (days_diff);
}

int	day(char *s)
{
	if (s[0] == 'L' || s[0] == 'l')
		return (0);
	else if ((s[0] == 'M' || s[0] == 'm') && s[1] == 'a')
		return (1);
	else if ((s[0] == 'M' || s[0] == 'm') && s[1] == 'e')
		return (2);
	else if (s[0] == 'J' || s[0] == 'j')
		return (3);
	else if (s[0] == 'V' || s[0] == 'v')
		return (4);
	else if (s[0] == 'S' || s[0] == 's')
		return (5);
	else if (s[0] == 'D' || s[0] == 'd')
		return (6);
	return (-1);
}

time_t get_date_secs(void)
{
    struct tm start = {0};      // met tout à zéro
    start.tm_mday = 16;         // jour
    start.tm_mon  = 5;          // mois (0 = janvier, donc 5 = juin)
    start.tm_year = 2025 - 1900;// année (compte depuis 1900)
    start.tm_hour = 12;         // sécurité contre changement d’heure

    return mktime(&start);// conversion en nombre (secondes depuis 1970)
}

int	main(void)
{
	int cur_days = get_day_diff(), limit_days = 65 - cur_days;
	time_t cur_date = get_date_secs();
	double hours_of_work[98] = {
		(17 - 14 + 13 - 9), (17 - 14 + 13 - 9), (19.3 - 14), (19.3 - 14), (19 - 14), 0, 0,
		(20.35 - 14.31), 0, 0, (20.46 - 12.47), (20.42 - 14.3), (20.49 - 14.31), (20.3 - 14.3),
		(22 - 16), (22.11 - 13.51), (22.21 - 12.04), (24 - 16), 0, (22.19 - 16), 0,
		(22.09 - 16), (22.36 - 15.57), (22.46 - 16), (23.04 - 16), 0, (23.45 - 16), 0,
		(23.04 - 16.59), (23.13 - 16.59), (24.19 - 14.49), (23.40 - 15.26), 0, (22.55 - 16.59), 0,
		(23.03 - 17.03), (23.06 - 16.59), (24.20 - 17.01), (23.27 - 16), 0, (24.08 - 17), 0,
		(23.20 - 17), (23.44 - 17), (23.54 - 17), (23.56 - 17), 0, (23.53 - 17), 0,
		(24.08 - 17), (23.51 - 14.54), (24.26 - 17.1), (24.14 - 16.57), 0, (23.39 - 14.29), 0,
		(24 - 15.13), (24.03 - 17), (24.31 - 17.01), (24.01 - 17), 0, (23.34 - 16.57), 0,
		(23.27 - 17), (23.06 - 17), (22.53 - 16.59), (23.14 - 17.02), 0, (23.14 - 17.02), 0,
		(22.17 - 16), (22.1 - 16), (22.24 - 16.02), (22.21 - 16.01), (22.22 - 16.01), 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0
	}, limit_hours = 455;

	how_much_time_left(hours_of_work, day("lundi"), cur_days, limit_days, limit_hours, cur_date);
	return (0);
}
