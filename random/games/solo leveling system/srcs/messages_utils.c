#include "../includes/the_system.h"

void	ft_readline(char *response, int str_len)
{
	char *str = {'\0'};

	bzero(response, str_len);
	str = get_next_line(0);
	if (!str)
	{
		printf("\n");
		exit(0);
	}
	strcpy(response, str);
	free(str);
	response[strcspn(response, "\n")] = '\0';
	write(1, CLEAR_SCREEN, strlen(CLEAR_SCREEN));
}

void	good_pace_print(char *str, char *return_line)
{
	int i = 0, j = 0, trigger = 0;

	while (str[i])
	{
		write(1, &str[i++], 1);
		if (!strncmp(str + i, "\033[", 2))
		{
			j = i;
			for (trigger = 2; str[j] && str[j] != 'm'; j++)
				trigger++;
		}
		if (trigger <= 0 && str[i] != '\t')
			usleep(50000);
		else
			trigger--;
		if (strcmp(return_line, "stats")
			&& (str[i - 1] != '\n' && (i > 3 && strncmp(str + i - 3, "⏰", 3))) && str[i] == '\n')
			sleep(1);
		else if (strcmp(return_line, "stats")
			&& (str[i - 1] == ',' || str[i - 1] == '!' || str[i - 1] == ':')
			&& str[i] == ' ')
			usleep(500000);
	}
	if (!strcmp(return_line, "yes"))
		printf("\n");
}
