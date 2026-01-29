#include "../includes/the_system.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	/* if (!skip_intro())
	{
		system_intro();
		introduction(login_sign_in());
	}
	welcome_player(login_sign_in()); */
	welcome_player(strdup("Hillany"));
	return (0);
}
