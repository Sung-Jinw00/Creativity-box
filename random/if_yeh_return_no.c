#include <string.h>
#include <stdio.h>

int main(int ac, char **av)
{
	while (--ac > 0 && ++av)
	{
		if (!strcmp(av[0], "yeh") || !strcmp(av[0], "yes")
			|| !strcmp(av[0], "yuh") || !strcmp(av[0], "yuh uh")
			|| !strcmp(av[0], "yuh huh") || !strcmp(av[0], "yas"))
		{
			while (1)
				printf("nuh\n");
		}
		else if (!strcmp(av[0], "nuh") || !strcmp(av[0], "no")
			|| !strcmp(av[0], "nos") || !strcmp(av[0], "nuh uh")
			|| !strcmp(av[0], "nuh huh") || !strcmp(av[0], "noes"))
		{
			while (1)
				printf("yuh\n");
		}
	}
	return (0);
}
