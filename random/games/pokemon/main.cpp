#include "pokémon.hpp"

int main()
{
	TypesTable table;
	str choice;
	
	signal(SIGINT, handle_sigint);
	std::cout << C_GREEN << "=== CALCULATEUR DE MULTIPLICATEURS POKÉMON ===" << C_RESET << "\n";

	while (true)
	{
		std::cout << C_YELLOW << "\nVoulez-vous : \n"
				<< C_GREEN << "1 - Attaquer\n"
				<< C_CYAN	<< "2 - Défendre\n"
				<< C_RED	<< "0 - Quitter\n"
				<< C_YELLOW << "Choix : " << C_RESET;
		std::getline(std::cin, choice);
		std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
		if (choice == "0" || choice == "quitter")
			break;
		str atk1, atk2, def1, def2;
		if (!choice.empty())
		{
			clear();
			refwrapstr types[4] = {std::ref(atk1), std::ref(atk2), std::ref(def1), std::ref(def2)};
			str prompts[4] = {
				C_GREEN + str("Type 1 de ton pokémon (ou entrer si pas de pokémon) : ") + C_RESET,
				C_GREEN + str("Type 2 de ton pokémon (ou entrer pour vide) : ") + C_RESET,
				C_CYAN + str("Type 1 du pokémon adverse : ") + C_RESET,
				C_CYAN + str("Type 2 du pokémon adverse (ou entrer pour vide) : ") + C_RESET };
			for (int i = 0; i < 4;)
			{
				std::cout << prompts[i];
				std::getline(std::cin, types[i].get());
				types[i].get() = normalize(types[i].get());
				if (!i && types[i].get().empty())
					i += 2;
				else if (!((!(i % 2) && table.getType(types[i].get()))
					|| ((i % 2) && !types[i].get().empty() && table.getType(types[i].get()))
					|| ((i % 2) && types[i].get().empty())))
					std::cout << C_RED << "Type invalide ! Réessayez.\n" << C_RESET;
				else
					i++;
			}
		}
		if (choice == "1" || choice == "attaquer")
		{
			table.getYourAtkResults(atk1, atk2, def1, def2);
			table.TypeToAttack(atk1, def1, atk2, def2);
		}
		else if (choice == "2" || choice == "defendre")
		{
			table.getYourDefResults(atk1, atk2, def1, def2);
			table.TypeToDefend(atk1, def1, atk2, def2);
		}
		else
		{
			clear();
			std::cout << C_RED << "Choix invalide !" << C_RESET << "\n";
			continue;
		}
		while (true)
		{
			std::cout << C_YELLOW << "\nVoulez-vous continuer ? (Entrer/ctrl+C) : " << C_RESET;
			std::getline(std::cin, choice);
			std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
			if (g_interrupt)
				return std::cout << C_YELLOW << "\n=== FIN DU PROGRAMME ===" << C_RESET << "\n", 0;
			else if (choice.empty())
			{
				clear();
				break;
			}
			else
				std::cout << C_RED << "Réponse invalide, réessayez.\n" << C_RESET;
		}
	}
	std::cout << C_YELLOW << "\n=== FIN DU PROGRAMME ===" << C_RESET << "\n";
	return 0;
}
