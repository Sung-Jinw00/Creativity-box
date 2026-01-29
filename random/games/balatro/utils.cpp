#include "Balatro.hpp"

int	HandScore(Hand hand)
{
	return hand.jetons * hand.Mult;
}

double	TotalCardValue(ScoreCarte card, bool RedSeal)
{
	double	card_value = (card.jetons + card.ExtraChips) * (card.Mult + card.AddMult);

	return RedSeal ? card_value * 2 : card_value;
}

ScoreCarte	SetCardModifiers(int CardScore, int ExtraChips, double Mult, int AddMult)
{
	ScoreCarte card;

	card.jetons = CardScore;
	card.ExtraChips = ExtraChips;
	card.Mult = Mult;
	card.AddMult = AddMult;
	return card;
}
