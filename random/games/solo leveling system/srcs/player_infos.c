#include "../includes/the_system.h"

int	get_password(char *password, char *filepath)
{
	int		fd;
	char	*str;

	fd = open(filepath, O_RDONLY, 0777);
	while ((str = get_next_line(fd)) != NULL)
	{
		if (!strncmp(PASSWORD, str, strlen(PASSWORD)))
		{
			if (!strncmp(password, str + 11, strlen(password)))
			{
				free(str);
				printf(GREEN"Password successfully entered !\n"CYAN);
				return (sleep(1), close(fd), 0);
			}
			else
			{
				good_pace_print("\t"RED"INVALID PASSWORD, PLEASE TRY AGAIN :"RESET CYAN" ", "no\n");
				return (close(fd), 1);
			}
		}
		free(str);
	}
	printf(RED"Error : issue finding password in file.\n\n"CYAN);
	return (close(fd), 1);
}

void	write_base_stats(FILE *fd)
{
	fprintf(fd, "____________\n");
	fprintf(fd, JOB "NONE\n");
	fprintf(fd, LEVEL "1\n");
	fprintf(fd, FATIGUE "0\n");
	fprintf(fd, TITLE "NONE\n");
	fprintf(fd, "____________\n");
	fprintf(fd, HP "100\n");
	fprintf(fd, MP "10\n");
	fprintf(fd, "____________\n");
	fprintf(fd, STRENGHT "10\n");
	fprintf(fd, HEALTH "10\n");
	fprintf(fd, AGILITY "10\n");
	fprintf(fd, INTELLIGENCE "10\n");
	fprintf(fd, SENSE "10\n");
	fprintf(fd, "____________\n");
	fprintf(fd, POINTS "0\n");
}
