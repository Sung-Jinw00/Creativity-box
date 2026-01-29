#ifndef THE_SYSTEM_H
# define THE_SYSTEM_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <ctype.h>
# include <stdarg.h>
# include <math.h>
# include <time.h>

# include "text_managment.h"
# include "get_next_line_bonus.h"
# include "player_variables.h"
# include "libft_extras.h"

//messages
void	welcome(void);//welcome player
int		skip_intro(void);//skip system proposal
void	system_intro(void);//message before heart stop beating
char	*login_sign_in(void);//creating a save
void	daily_quest(void);//daily quest
void	introduction(char *player_name);//system presentation
void	welcome_player(char *player_name);  // Ajout de la déclaration avec le paramètre player_name

//messages-utils
void	ft_readline(char *response, int str_len);
void	good_pace_print(char *str, char *return_line);

//player infos
int		get_password(char *password, char *filepath);
void	write_base_stats(FILE *fd);

//easter_eggs
int		sung_jinwoo_already_exist(char *player_name);
void	jinwoo_special_messages(int i);

#endif