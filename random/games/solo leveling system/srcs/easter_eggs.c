#include "the_system.h"

int	sung_jinwoo_already_exist(char *player_name)
{
	char cpy[500];
	int i, j;

	ft_bzero(cpy, 500);
	strcpy(cpy, player_name);
	for (i = 0; cpy[i]; i++)
	{
		cpy[i] = ft_isnum_equal_al(cpy[i]);
		if ((i == 0 && ft_islowalpha(cpy[i])) || (i != 0 && ft_iswhitespace(cpy[i - 1]) && ft_islowalpha(cpy[i])))
			cpy[i] = ft_toupper(cpy[i]);
		else if (i != 0 && ft_isupalpha(cpy[i]) && ft_isalpha(cpy[i - 1]))
			cpy[i] = ft_tolower(cpy[i]);
	}
	i = 0;
	for (j = 0; cpy[j]; j++)
	{
		if (ft_iswhitespace(cpy[j]) && ((j != 0 && !ft_isalpha(cpy[j - 1])) || j == 0))
			continue ;
		if (i != j)
			cpy[i] = cpy[j];
		i++;
	}
	if (ft_iswhitespace(cpy[i - 1]))
		i--;
	while (cpy[i])
		cpy[i++] = 0;
	if (!strcmp(cpy, "Sung Jinwoo") || !strcmp(cpy, "Jinwoo Sung"))
		return (1);
	return (0);
}

void	jinwoo_special_messages(int i)
{
	if (i == 0)
		return (good_pace_print(ALERT MAGENTA" THE SHADOW MONARCH ALREADY EXIST."CYAN" TRY AGAIN : ", "no"));
	else if (i == 1)
		return (good_pace_print(ALERT MAGENTA" SERIOUSLY, YOU CAN'T BE MR. SUNG."CYAN" TRY AGAIN : ", "no"));
	else if (i == 2)
		return (good_pace_print(ALERT MAGENTA" IGRIS WILL FIND YOU."RED" THIS IS YOU LAST CHANCE"CYAN" : ", "no"));
	else
		return (good_pace_print(ALERT MAGENTA" HE'S ON HIS WAY, YOU CAN'T STOP HIM, UNLESS YOU SEARCH FOR ANOTHER NAME."CYAN" : ", "no"));
}
