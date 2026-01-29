#ifndef TEXT_MANAGMENT_H
# define TEXT_MANAGMENT_H

# define RESET			"\033[0m"   //Réinitialisation
# define RED			"\033[31m"   //Couleur rouge
# define GREEN			"\033[32m"  // Couleur verte
# define LIGHT_GREEN	"\033[92m"  // Couleur vert clair
# define YELLOW			"\033[33m"  // Couleur jaune
# define BLUE			"\033[34m"  // Couleur bleue
# define MAGENTA		"\033[35m"  // Couleur magenta
# define CYAN			"\033[36m"  // Couleur cyan
# define ORANGE			"\033[93m"// Couleur orange
# define BOLD			"\033[1m"  // Texte en gras
# define UNDERLINE		"\033[4m"  // Texte souligné
# define ITALIC			"\033[3m"  // Texte en italique

//notifications banners
# define TITLE_POLICE	UNDERLINE BOLD CYAN
# define ALERT			"\n"TITLE_POLICE"ALERT"RESET CYAN"❕\n"
# define MESSAGE		"\n"TITLE_POLICE"MESSAGE"RESET CYAN" ✉️\n"
# define QUEST_INFO		"\n"TITLE_POLICE"QUEST INFO"RESET CYAN"❕\n"

# define CLEAR_SCREEN  "\033[2J\033[H"

#endif