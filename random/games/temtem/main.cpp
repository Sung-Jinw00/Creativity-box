#include "temtemlist.hpp"

int main()
{
	TypesTable typeTable;
	TemtemTable temtemTable;
	
	std::cout << C_GREEN << "=== TEMTEM MULTIPLICATOR CALCULATOR ===" << C_RESET << "\n";
	while (true)
	{
		str choice = get_input(C_YELLOW + str("\nYou want to : \n") + C_GREEN + "1 - Attack\n"
				+ C_CYAN + "2 - Defend\n" + C_RED + "0 - Quit\n" + C_YELLOW + "Choice : " + C_RESET);
		if (choice == "0" || choice == "quit")
			break;
		else if (choice != "1" && choice != "attack" && choice != "2" && choice != "defend")
		{
			clear();
			std::cout << C_RED << "Invalid choice !" << C_RESET << "\n";
			continue;
		}
		str results = get_input(C_YELLOW + str("\nDo you want the results by : \n") + C_GREEN + "1 - type\n"
				+ C_CYAN + "2 - Temtem\n" + C_YELLOW + "Choice : " + C_RESET);
		str atk1, atk2, def1, def2;
		Temtem	temtem1, temtem2;
		if (!choice.empty() && (results == "1" || results == "type" || results == "2" || results == "temtem"))
		{
			clear();
			if (results == "1" || results == "type")
			{
				refwrapstr types[4] = {std::ref(atk1), std::ref(atk2), std::ref(def1), std::ref(def2)};
				GetTypeResults(types, typeTable);
			}
			else
			{
				refwrapTemtem temtems[2] = {std::ref(temtem1), std::ref(temtem2)};
				getTemTemResults(temtems, temtemTable);
			}
		}
		if (choice == "1" || choice == "attack")
		{
			if (results == "1" || results == "type")
			{
				typeTable.getYourAtkResults(atk1, atk2, def1, def2);
				typeTable.TypeToAttack(atk1, def1, atk2, def2, 1);
			}
			else
			{
				temtemTable.getYourTemtemResults(temtem1, temtem2);
				temtemTable.TemtemToAttack(temtem1, temtem2);
			}
		}
		else if (choice == "2" || choice == "defend")
		{
			typeTable.getYourDefResults(atk1, atk2, def1, def2);
			typeTable.TypeToDefend(atk1, def1, atk2, def2);
		}
		else
		{
			clear();
			std::cout << C_RED << "Invalid choice !" << C_RESET << "\n";
			continue;
		}
		while (true)
		{
			choice = get_input(C_YELLOW + str("\nAre you willing to continue ? (Entrer/n) : ") + C_RESET);
			if (choice == "n")
				return std::cout << C_YELLOW << "\n=== END OF PROGRAM ===" << C_RESET << "\n", 0;
			else if (choice.empty())
			{
				clear();
				break;
			}
			else
				std::cout << C_RED << "Invalid response, try again.\n" << C_RESET;
		}
	}
	std::cout << C_YELLOW << "\n=== END OF PROGRAM ===" << C_RESET << "\n";
	return 0;
}
