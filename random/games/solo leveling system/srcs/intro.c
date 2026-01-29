#include "../includes/the_system.h"

int	skip_intro(void)
{
	char	response[4];
	char	*message = " DO YOU WANT TO SKIP THE INTRO ? (yes/no) ";

	while (1)
	{
		good_pace_print(message, "no");
		ft_readline(response, 4);
		if (!strcmp(response, "yes"))
			return (1);
		else if (!strcmp(response, "no"))
			return (0);
	}
	return (0);
}

void	system_intro(void)
{
	char	response[10];
	char	*str = ALERT
				   " [YOU'VE MET ALL THE REQUIREMENTS TO COMPLETE THE SECRET QUEST : "MAGENTA"\"COURAGE OF THE WEAK\""CYAN"]\n\n"
				   " [YOU'RE NOW QUALIFIED TO BECOME A PLAYER.]\n"
				   " [IF YOU DECLINE, YOUR HEART WILL STOP BEATING IN "RED"0,02"CYAN" SECONDS.]\n\n";
	char	*do_you_accept = TITLE_POLICE"\tDO YOU ACCEPT ?"RESET CYAN" (accept/decline) ";
	char	*accept = ALERT
				   " [CONGRATULATIONS ! YOU'VE NOW BECOME A "LIGHT_GREEN"PLAYER."CYAN"]\n"RESET;
	char	*decline = ALERT
				   " YOUR HEART "RED"STOPPED BEATING..."RESET;

	good_pace_print(str, "yes");
	while (1)
	{
		good_pace_print(do_you_accept, "no");
		ft_readline(response, 10);
		if (!strcmp(response, "accept"))
		{
			good_pace_print(accept, "yes");
			break ;
		}
		else if (!strcmp(response, "decline"))
		{
			good_pace_print(decline, "no");
			sleep(1);
			printf("\n");
			exit(0);
		}
	}
	welcome();
}

void	welcome(void)
{
	char	response[4] = {'\0'};
	char	*mail_notification = MESSAGE
					 " -YOU HAVE UNREAD MESSAGES.\n";
	char	*open_message_box = TITLE_POLICE"\tOPEN THE MESSAGE BOX ?"RESET CYAN" (yes/no) ";
	char	*mails = " [CONGRATULATIONS ! YOU'VE NOW BECOME "LIGHT_GREEN"A PLAYER."CYAN"]("LIGHT_GREEN"READED"CYAN")\n\n"
					 " [DAILY QUEST : TRAIN TO BECOME A FORMIBALE FIGHTER."CYAN"]("RED"UNREAD"CYAN")\n"RESET;
						
	good_pace_print(mail_notification, "yes");
	while (1)
	{
		good_pace_print(open_message_box, "no");
		ft_readline(response, 4);
		if (!strcmp(response, "yes"))
		{
			good_pace_print(mails, "yes");
			break ;
		}
		else if(!strcmp(response, "no"))
			break ;
	}
	sleep(1);
}

char	*login_sign_in(void)
{
	FILE	*fd;
	char	password[500], player_name[500];
	char	file_path[600] = "saves/";
	char	*choose_a_name = TITLE_POLICE"\tTHE PLAYER MUST CHOOSE A NAME :"RESET CYAN" ";

	good_pace_print(choose_a_name, "no");
	if (mkdir("saves", 0777) == -1 && errno != EEXIST)
		return (perror(RED"Issue creating folder"RESET), NULL);

	ft_readline(player_name, 500);
	for (int i = 0; sung_jinwoo_already_exist(player_name); i++)
	{
		jinwoo_special_messages(i);
		ft_readline(player_name, 500);
	}
	strcat(file_path, player_name);
	strcat(file_path, ".txt");
	if (access(file_path, F_OK) == 0)
	{
		good_pace_print(ALERT" THIS PLAYER ALREADY EXIST.\n", "no");
		good_pace_print("\t"TITLE_POLICE"PLEASE, ENTER THE PLAYER PASSWORD :"RESET CYAN" ", "no");
		ft_readline(password, 500);
		while (get_password(password, file_path))
			ft_readline(password, 500);
	}
	else
	{
		if (!(fd = fopen(file_path, "a")))
			return (perror(RED"Issue creating folder"RESET), NULL);
		fprintf(fd, NAME"%s\n", player_name);
		good_pace_print(ALERT" NAME SUCCESSFULLY ADDED !\n", "yes");
		good_pace_print("\t"TITLE_POLICE"PLEASE, ENTER A PASSWORD :"RESET CYAN" ", "no");
		ft_readline(password, 500);
		fprintf(fd, PASSWORD"%s\n", password);
		good_pace_print("\b\b"ALERT" PLAYER PASSWORD SUCCESSFULLY ADDED !\n", "yes");
		write_base_stats(fd);
		fclose(fd);
	}
	return (strdup(player_name));
}

void	introduction(char *player_name)
{
	char	response[4];
	char	full_message[1000];
	char	*mail = MESSAGE" [DAILY QUEST : TRAIN TO BECOME A FORMIBALE FIGHTER."CYAN"]("RED"UNREAD"CYAN")\n"RESET;
	char	*open_message_box = TITLE_POLICE"\tOPEN THE MESSAGE ?"RESET CYAN" (yes/no) ";

	snprintf(full_message, sizeof(full_message),
		ALERT CYAN" [THIS SYSTEM WILL HELP \""LIGHT_GREEN"%.*s"
		CYAN"\" DEVELOP.]\n\n"
		" [FAILING TO COMPLY WITH THE SYSTEM'S ORDERS COULD RESULT IN "RED"A PENALTY"CYAN".]\n\n"RESET,
		(int)strlen(player_name), player_name);

	good_pace_print(full_message, "no");
	good_pace_print(mail, "no");
	while (1)
	{
		good_pace_print(open_message_box, "no");
		ft_readline(response, 4);
		if (!strcmp("yes", response))
			break ;
		else if (!strcmp("no", response))
			return ;
	}
	daily_quest();
	free(player_name);
}

void	daily_quest(void)
{
	time_t current_time;
	struct tm *time_info;
	int hours_left, minutes_left;
	char time_str[100];
	char	*daily_quest =  QUEST_INFO
						CYAN" DAILY QUEST - TRAIN TO BECOME A FORMIDABLE FIGHTER\n\n"
						LIGHT_GREEN"\t       GOALS\n"
						CYAN" - PUSH-UPS\t\t[0/100]\n"
						CYAN" - SIT-UPS \t\t[0/100]\n"
						CYAN" - SQUATS  \t\t[0/100]\n"
						CYAN" - RUN\t\t\t[0/10km]\n\n"
						"\t\t⏰\n\n"
						RED" CAUTION !"CYAN" - IF THE DAILY QUEST REMAINS INCOMPLETE, PENALTIES WILL BE GIVEN ACCORDINGLY.\n";

	good_pace_print(daily_quest, "yes");
	time(&current_time);
	time_info = localtime(&current_time);
	hours_left = 23 - time_info->tm_hour;
	minutes_left = 59 - time_info->tm_min;
	if (hours_left == 0 || (hours_left == 1 && minutes_left == 0))
	{
		snprintf(time_str, sizeof(time_str), 
			" "CYAN UNDERLINE"TIME LEFT :"RESET RED" %02dh%02dmin\n"RESET,
			hours_left, minutes_left);
	}
	else if (hours_left < 7 || (hours_left == 8 && minutes_left == 0))
	{
		snprintf(time_str, sizeof(time_str), 
			" "CYAN UNDERLINE"TIME LEFT :"RESET ORANGE" %02dh%02dmin\n"RESET,
			hours_left, minutes_left);
	}
	else
	{
		snprintf(time_str, sizeof(time_str), 
			" "CYAN UNDERLINE"TIME LEFT :"RESET LIGHT_GREEN" %02dh%02dmin\n"RESET,
			hours_left, minutes_left);
	}
	good_pace_print(time_str, "yes");
}

