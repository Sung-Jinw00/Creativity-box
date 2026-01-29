#include "../includes/the_system.h"

void	message_box(void)
{
	good_pace_print(CYAN"\tNO MESSAGES TO READ...\n\n"RESET, "no");
}

void	update_daily_quest(void)
{
	good_pace_print(CYAN"\tCOMING SOON...\n\n"RESET, "no");
}

void	see_current_stats(char *player_name)
{
	int		fd, skip = 3, i = 6 + (int)strlen(player_name) + 5;
	char	*file_name = calloc(i, sizeof(char));
	char	*line = NULL, stats_msg[1000];

	file_name = strcat(file_name, "saves/");
	file_name = strcat(file_name, player_name);
	file_name = strcat(file_name, ".txt");
	snprintf(stats_msg, sizeof(stats_msg), "saves/%s.txt", player_name);
	fd = open(file_name, O_RDONLY);

	snprintf(stats_msg, sizeof(stats_msg),
		TITLE_POLICE"\n\tCURRENT STATS OF PLAYER \""RESET LIGHT_GREEN"%s"RESET TITLE_POLICE"\" :"RESET CYAN, player_name);
	good_pace_print(stats_msg, "yes");
	while ((line = get_next_line(fd)))
	{
		if (skip > 0)
		{
			free(line);
			skip--;
			continue ;
		}
		write(1, "\t ", 2);
		good_pace_print(line, "stats");
		free(line);
	}
	close(fd);
	free(file_name);
	printf("\n");
}

void	welcome_player(char *player_name)
{
	char	welcome_msg[1000], choice[10];
	char	*choose_your_fate = "\t"CYAN UNDERLINE"WHAT ARE YOU WILLING TO DO ? :\n"RESET CYAN;
	char	*options = "\t [1] OPEN THE MESSAGE BOX\n"
								"\t [2] OPEN DAILY QUEST\n"
								"\t [3] UPDATE DAILY QUEST\n"
								"\t [4] SEE MY CURRENT STATS\n"
								"\t [5] QUIT\n"RESET;
	
	snprintf(welcome_msg, sizeof(welcome_msg),
		ALERT" WELCOME PLAYER \""LIGHT_GREEN"%.*s"RESET CYAN"\" !\n",
		500, player_name);

	good_pace_print(welcome_msg, "yes");
	printf("\n");
	while (1)
	{
		good_pace_print(choose_your_fate, "stats");
		printf("%s\n", options);
		good_pace_print(TITLE_POLICE"\tENTER YOUR CHOICE :"RESET CYAN" ", "no");
		ft_readline(choice, sizeof(choice));
		if (choice[0] == '1')
			message_box();
		else if (choice[0] == '2')
			daily_quest();
		else if (choice[0] == '3')
			update_daily_quest();
		else if (choice[0] == '4')
			see_current_stats(player_name);
		else if (choice[0] == '5')
			return (free(player_name), exit(0));
	}
}
