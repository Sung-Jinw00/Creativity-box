/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gym_track.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:40:05 by marvin            #+#    #+#             */
/*   Updated: 2025/08/01 17:16:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>

typedef enum s_police
{
	WORKOUT_NAME,
	BODY_PART,
	EXERCICE
} t_police;

typedef struct s_gym_progression
{
	t_police police;
	char *exercice;
	double *weight_progression;
	int *reps;
	int *sets;
} t_gym_progression;

/* Bold text */
# ifndef BOLD
#  define BOLD				"\033[1m"
# endif

/* Underlined text */
# ifndef UNDERLINE
#  define UNDERLINE			"\033[4m"
# endif

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

/* Red text */
# ifndef RED
#  define RED				"\033[31m"
# endif

/* Magenta text */
# ifndef MAGENTA
#  define MAGENTA			"\033[35m"
# endif

/* Yellow text */
# ifndef YELLOW
#  define YELLOW			"\033[33m"
# endif

/* Black text */
# ifndef BLACK
#  define BLACK				"\033[30m"
# endif

/* Black text */
# ifndef BW
#  define BW				82.7
# endif

void	should_decimal_be_printed(double val, char *color, char *unit)
{
	if (val != (int)val)
		printf(BOLD"%s%.2f%s" RESET, color, val, unit);
	else
		printf(BOLD"%s%d%s"RESET, color, (int)val, unit);
}

int utf8_strlen(const char *s)
{
    int len = 0;

    while (*s)
	{
        unsigned char c = (unsigned char)*s;
        if ((c & 0xC0) != 0x80) // Si ce n'est pas un octet de continuation
            len++;
        s++;
    }
    return (len);
}

void	display_stats(t_gym_progression track[])
{
	for (int i = 0; track[i].exercice; i++)
	{
		if (track[i].police == WORKOUT_NAME)
		{
			if (i != 0)
				printf(BLACK BOLD "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n\n" RESET);
			printf(CYAN BOLD UNDERLINE "%s"RESET CYAN" :\n" RESET, track[i].exercice);
		}
		else if (track[i].police == BODY_PART)
			printf(RED BOLD"    * %s :\n" RESET, track[i].exercice);
		else if (track[i].police == EXERCICE)
		{
			printf(CYAN "        - "UNDERLINE "%s"RESET CYAN" :" RESET, track[i].exercice);
			if (!track[i].weight_progression[1])
				printf(BOLD" pdcx");
			else
				printf(BOLD" %gkgx", track[i].weight_progression[1]);
			printf("%dx%d" RESET GREEN", strenght increased by ", track[i].reps[1], track[i].sets[1]);
			if (!track[i].weight_progression[0])
			{
				track[i].weight_progression[0] += BW;
				track[i].weight_progression[1] += BW;
			}
			double new_volume = track[i].weight_progression[1] * track[i].reps[1] * track[i].sets[1];
			double old_volume = track[i].weight_progression[0] * track[i].reps[0] * track[i].sets[0];
			double overall_w_diff = new_volume - old_volume;
			double strenght_diff = overall_w_diff * 100 / old_volume;
			should_decimal_be_printed(strenght_diff, MAGENTA, "%");
			printf(GREEN", thus, the overall weight lifted increased by ");
			should_decimal_be_printed(overall_w_diff, YELLOW, "kgs");
			printf(".\n\n" RESET);
		}
	}
}

int main(void)
{
	t_gym_progression track[] = {
		{BODY_PART, "Dos", NULL, NULL, NULL},
		{EXERCICE, "Tractions",
				(double[]){0, 10, -1},
				(int[]){5, 8, -1},
				(int[]){4, 4, -1}},
		{EXERCICE, "Tirage vertical",
				(double[]){65, 100, -1},
				(int[]){10, 10, -1},
				(int[]){4, 4, -1}},

		{BODY_PART, "Pecs", NULL, NULL, NULL},
		{EXERCICE, "Développé couché",
				(double[]){48, 84, -1},
				(int[]){10, 8, -1},
				(int[]){4, 4, -1}},
		{EXERCICE, "Développé machine",
				(double[]){30, 66, -1},
				(int[]){10, 10, -1},
				(int[]){4, 4, -1}},

		{BODY_PART, "Deltoides", NULL, NULL, NULL},
		{EXERCICE, "Développé militaire",
				(double[]){24, 60, -1},
				(int[]){10, 6, -1},
				(int[]){4, 4, -1}},
		{EXERCICE, "élévations latérales",
				(double[]){16, 40, -1},
				(int[]){10, 10, -1},
				(int[]){4, 4, -1}},

		{BODY_PART, "Trapezes", NULL, NULL, NULL},
		{EXERCICE, "Tirage poulie",
				(double[]){40, 59, -1},
				(int[]){10, 10, -1},
				(int[]){4, 4, -1}},
		{EXERCICE, "Shrugs",
				(double[]){40, 80, -1},
				(int[]){10, 10, -1},
				(int[]){4, 4, -1}},

		{BODY_PART, "Triceps", NULL, NULL, NULL},
		{EXERCICE, "Extensions poulie 1 bras",
				(double[]){7.5, 27, -1},
				(int[]){10, 8, -1},
				(int[]){3, 3, -1}},

		{BODY_PART, "Biceps", NULL, NULL, NULL},
		{EXERCICE, "Curl pupitre 1 bras",
				(double[]){8, 20, -1},
				(int[]){10, 10, -1},
				(int[]){3, 3, -1}},
		{EXERCICE, "Tirage vertical 1 bras",
				(double[]){35, 45, -1},
				(int[]){10, 7, -1},
				(int[]){3, 3, -1}},
/* 
		{BODY_PART, "Jambes", NULL, NULL, NULL},
		{EXERCICE, "Romanian Deadlift",
				(double[]){50, 55, -1},
				(int[]){10, 10, -1},
				(int[]){4, 4, -1}},
		{EXERCICE, "Squats",
				(double[]){0, 100, -1},
				(int[]){10, 7, -1},
				(int[]){4, 4, -1}},
		{EXERCICE, "Deadlift",
				(double[]){90, 100, -1},
				(int[]){10, 10, -1},
				(int[]){4, 4, -1}},

		{BODY_PART, "Mollets", NULL, NULL, NULL},
		{EXERCICE, "Extensions presse",
				(double[]){60, 160, -1},
				(int[]){10, 12, -1},
				(int[]){3, 3, -1}}, */
		{0}
	};
	display_stats(track);
	return (0);
}