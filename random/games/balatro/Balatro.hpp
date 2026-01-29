#pragma once
#include <string>
#include <iostream>

# define NANEINF		1e308
# define START_HAND		8

# define ONE_SCORE		1
# define TWO_SCORE		2
# define TREE_SCORE		3
# define FOUR_SCORE		4
# define FIVE_SCORE		5
# define SIX_SCORE		6
# define SEVEN_SCORE	7
# define EIGHT_SCORE	8
# define NINE_SCORE		9
# define TEN_SCORE		10
# define FIGURE_SCORE	10
# define AS_SCORE		11

struct Chips
{
	static constexpr int None = 0;
	static constexpr int BonusCard = 30;
	static constexpr int StoneCard = 50;
	static constexpr int FoilCard = 50;
};

struct AddMult
{
	static constexpr int None = 0;
	static constexpr int MultCard = 4;
	static constexpr int HolographicCard = 10;
	static constexpr int LuckyCard = 20;
};

struct TimeMult
{
	static constexpr int None = 1;
	static constexpr double Steel = 1.5;
	static constexpr int Glass = 2;
	static constexpr int Polychrome = 2;
};

struct ScoreCarte
{
	int jetons = 1;
	int ExtraChips = Chips::None;
	double Mult = TimeMult::None;
	int AddMult = AddMult::None;
};

#define PRINT_VAR(x, y) std::cout << "number of " << #x << "'s needed : " << y << std::endl;

struct Hand
{
	int		jetons;
	double	Mult;
};

inline Hand FlushFive {160, 16};
inline Hand FlushHouse {140, 14};
inline Hand FiveOfAKind {120, 12};
inline Hand RoyalFlush {100, 8};
inline Hand StraightFlush {100, 8};
inline Hand FourOfAKind {60, 7};
inline Hand FullHouse {40, 4};
inline Hand Flush {35, 4};
inline Hand Straight {30, 4};
inline Hand ThreeOfAKind {30, 3};
inline Hand TwoPair {20, 2};
inline Hand Pair {10, 2};
inline Hand HighCard {5, 1};

int	HandScore(Hand hand);
double	TotalCardValue(ScoreCarte card, bool RedSeal);
ScoreCarte	SetCardModifiers(int CardScore, int ExtraChips, double Mult, int AddMult);