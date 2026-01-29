/* #include "Balatro.hpp"
#include <cmath>

int CardsNeededExponential(double card_value, int hand_size)
{
	return static_cast<int>(std::ceil(std::log(NANEINF / hand_size) / std::log(card_value)));
}

int main()
{
	ScoreCarte king = SetCardModifiers(FIGURE_SCORE, Chips::None, TimeMult::Glass, AddMult::None);
	int cards_needed = CardsNeededExponential(TotalCardValue(king, true) * 2, 20);

	std::cout << "Nombre de cartes nécessaires pour dépasser NANEINF : " 
			  << cards_needed << std::endl;
} */

#include <iostream>
#include <cmath> // pour log et ceil

int main()
{
	long double multiplicateur = 1.5;    // chaque carte multiplie par 1,5
	long double cible = 1e308;           // valeur finale voulue
	long double depart = 1.0;            // multiplicateur initial
	int repetitions = 20; // nombre de fois qu'on peut réappliquer chaque carte

	// Formule : n = log(cible / depart) / log(multiplicateur)
	double n = std::log(cible / depart) / (std::log(multiplicateur) * repetitions);

	// Arrondir au nombre entier supérieur
	int cartes = static_cast<int>(std::ceil(n));

	std::cout << "Nombre de cartes nécessaires : " << cartes << std::endl;

	return 0;
}

