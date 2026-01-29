#include "temtemlist.hpp"

Temtem* TemtemTable::getTemTem(const str& name)
{
	auto it = std::find_if(temtemTable.begin(), temtemTable.end(),
						   [&name](Temtem& t) { return t.name == name; });
	if (it != temtemTable.end())
		return &(*it);
	return nullptr;
}
const std::vector<Temtem> &TemtemTable::getTable(void) const
{
	return this->temtemTable;
}

void TemtemTable::printTemtem(const str& name)
{
	const Temtem *t = getTemTem(name);
	if (t)
	{

		std::cout << "ID: " << t->number << "\n";
		std::cout << "NAME: " << t->name << "\n";
		std::cout << "Type: "; 
		for (size_t i = 0; i < t->types.size(); ++i)
		{
			std::cout << t->types[i];
			if (i != t->types.size() - 1)
				std::cout << "/";
		}
		 std::cout << "\nStats:\n";
	std::cout << "HP   Stamina   Speed   Attack   Defense   Special Attack   Special Defense\n";
	std::cout << std::left
		  << std::setw(7) << t->hp
		  << std::setw(10) << t->sta
		  << std::setw(8) << t->spd
		  << std::setw(9) << t->atk
		  << std::setw(14) << t->def_
		  << std::setw(17) << t->spatk
		  << std::setw(13) << t->spdef
		  << "\n";
	}
	else
		std::cout << "Temtem '" << name << "' not found.\n";
}

TemtemTable::TemtemTable()
{
	temtemTable = std::vector<Temtem>{
		{-1,	"",				{},					-1,	-1,	-1,	-1,	-1,	-1, -1},
		{1,		"Mimit",		{NEUTRAL},			50,	50,	50,	50,	60,	50, 65},
		{2,		"Oree",			{DIGITAL},			61,	74,	35,	65,	44,	32,	31},
		{3,		"Zaobian",		{DIGITAL},			72,	90,	51,	84,	50,	42,	44},
		{4,		"Chromeon",		{DIGITAL},			61,	55,	66,	65,	49,	78,	63},
		{5,		"Halzhi",		{DIGITAL},			52,	35,	38,	56,	48,	39,	44},
		{6,		"Molgu",		{DIGITAL},			79,	47,	51,	84,	64,	52,	58},
		{7,		"Platypet",		{WATER,TOXIC},		55,	39,	65,	45,	31,	67,	56},
		{8,		"Platox",		{WATER,TOXIC},		62,	44,	74,	50,	35,	76,	63},
		{9,		"Platimous",	{WATER,TOXIC},		73,	49,	82,	56,	39,	93,	70},
		{10,	"Swali",		{NATURE},			44,	65,	35,	50,	40,	55,	60},
		{11,	"Loali",		{NATURE,WIND},		61,	74,	77,	60,	54,	70,	81},
		{12,	"Tateru",		{NEUTRAL},			79,	82,	60,	75,	66,	54,	66},
		{13,	"Gharunder",	{TOXIC,ELECTRIC},	71,	59,	49,	84,	45,	47,	85},
		{14,	"Mosu",			{MELEE},			60,	39,	35,	65,	54,	65,	54},
		{15,	"Magmut",		{MELEE,FIRE},		90,	45,	40,	75,	62,	75,	62},
		{16,	"Paharo",		{WIND},				48,	18,	60,	40,	40,	50,	50},
		{17,	"Paharac",		{WIND},				60,	35,	70,	54,	55,	60,	60},
		{18,	"Granpah",		{WIND},				70,	44,	78,	55,	63,	76,	68},
		{19,	"Ampling",		{ELECTRIC},			51,	40,	70,	35,	36,	41,	42},
		{20,	"Amphatyr",		{ELECTRIC,NATURE},	65,	42,	110,51,	53,	62,	64},
		{21,	"Bunbun",		{EARTH,CRYSTAL},	72,	40,	69,	50,	36,	64,	43},
		{22,	"Mudrid",		{EARTH,CRYSTAL},	85,	52,	95,	60,	42,	80,	50},
		{23,	"Hidody",		{NATURE},			49,	70,	39,	42,	39,	62,	55},
		{24,	"Taifu",		{NATURE},			60,	87,	45,	50,	45,	91,	89},
		{25,	"Fomu",			{WATER},			40,	60,	40,	30,	35,	65,	70},
		{26,	"Wiplump",		{WATER,WIND},		66,	80,	70,	40,	50,	95,	80},
		{27,	"Skail",		{NEUTRAL},			57,	43,	60,	45,	50,	32,	41},
		{28,	"Skunch",		{NEUTRAL,MELEE},	72,	67,	75,	68,	70,	45,	60},
		{29,	"Goty",			{NEUTRAL},			51,	48,	31,	55,	48,	58,	37},
		{30,	"Mouflank",		{NEUTRAL},			79,	75,	72,	65,	79,	72,	41},
		{31,	"Rhoulder",		{NEUTRAL,EARTH},	90,	37,	42,	84,	83,	22,	40},
		{32,	"Houchic",		{MENTAL},			38,	44,	66,	40,	41,	72,	52},
		{33,	"Tental",		{MENTAL},			41,	51,	76,	42,	50,	81,	62},
		{34,	"Nagaise",		{MENTAL,WATER},		47,	52,	81,	49,	55,	92,	76},
		{35,	"Orphyll",		{NATURE,TOXIC},		42,	48,	75,	68,	64,	27,	40},
		{36,	"Nidrasil",		{NATURE,TOXIC},		77,	52,	61,	88,	80,	36,	51},
		{37,	"Banapi",		{FIRE},				42,	40,	70,	50,	50,	40,	41},
		{38,	"Capyre",		{FIRE},				55,	55,	88,	71,	68,	45,	47},
		{39,	"Lapinite",		{CRYSTAL},			58,	31,	46,	44,	63,	55,	56},
		{40,	"Azuroc",		{CRYSTAL},			64,	34,	50,	58,	69,	60,	62},
		{41,	"Zenoreth",		{CRYSTAL},			71,	45,	60,	72,	87,	70,	73},
		{42,	"Reval",		{MENTAL},			50,	46,	40,	61,	42,	80,	75},
		{43,	"Aohi",			{MENTAL,FIRE},		64,	51,	71,	61,	42,	89,	79},
		{44,	"Bigu",			{NATURE},			55,	68,	20,	65,	38,	41,	42},
		{45,	"Babawa",		{NATURE,WATER},		85,	92,	40,	79,	60,	51,	52},
		{46,	"0b1",			{DIGITAL,ELECTRIC},	22,	38,	74,	24,	32,	29,	34},
		{47,	"0b10",			{DIGITAL,ELECTRIC},	61,	76,	78,	52,	64,	62,	68},
		{48,	"Kaku",			{NATURE},			69,	48,	35,	60,	60,	35,	50},
		{49,	"Saku",			{NATURE,WIND},		82,	68,	40,	66,	62,	40,	70},
		{50,	"Valash",		{NEUTRAL,CRYSTAL},	58,	57,	90,	74,	56,	74,	56},
		{51,	"Towly",		{MELEE,MENTAL},		45,	41,	70,	54,	36,	54,	36},
		{52,	"Owlhe",		{WIND,MELEE},		57,	46,	78,	75,	79,	60,	40},
		{53,	"Barnshe",		{WIND,MENTAL},		63,	61,	80,	60,	47,	75,	79},
		{54,	"Gyalis",		{CRYSTAL,MELEE},	86,	44,	100,85,	61,	23,	61},
		{55,	"Occlura",		{CRYSTAL},			50,	39,	50,	45,	43,	38,	65},
		{56,	"Myx",			{CRYSTAL,MENTAL},	51,	59,	65,	51,	43,	82,	80},
		{57,	"Raiber",		{FIRE},				57,	35,	42,	40,	61,	59,	38},
		{58,	"Raize",		{FIRE},				66,	46,	40,	46,	74,	69,	43},
		{59,	"Raican",		{FIRE},				77,	49,	67,	77,	77,	51,	50},
		{60,	"Pewki",		{WATER},			70,	32,	33,	42,	45,	31,	10},
		{61,	"Piraniant",	{WATER},			90,	50,	55,	77,	85,	65,	42},
		{62,	"Scarawatt",	{ELECTRIC},			51,	41,	40,	24,	50,	35,	61},
		{63,	"Scaravolt",	{ELECTRIC,FIRE},	89,	52,	44,	60,	65,	62,	77},
		{64,	"Hoglip",		{"unknown"},		-1,	-1,	-1,	-1,	-1,	-1,	-1},	// stats inconnues
		{65,	"Hedgine",		{DIGITAL,FIRE},		54,	43,	84,	51,	61,	80,	64},
		{66,	"Osuchi",		{EARTH},			52,	37,	38,	65,	51,	24,	25},
		{67,	"Osukan",		{EARTH,MELEE},		60,	41,	41,	78,	69,	26,	27},
		{68,	"Osukai",		{EARTH,MELEE},		71,	48,	68,	95,	85,	31,	46},
		{69,	"Saipat",		{WATER,MELEE},		75,	55,	85,	85,	60,	55,	61},
		{70,	"Pycko",		{EARTH,FIRE},		49,	52,	39,	55,	40,	44,	41},
		{71,	"Drakash",		{EARTH,FIRE},		64,	60,	79,	57,	45,	83,	72},
		{72,	"Crystle",		{CRYSTAL},			60,	41,	33,	61,	69,	46,	42},
		{73,	"Sherald",		{CRYSTAL},			68,	45,	43,	69,	78,	51,	48},
		{74,	"Tortenite",	{CRYSTAL,TOXIC},	74,	52,	52,	45,	76,	89,	60},
		{75,	"Innki",		{ELECTRIC,CRYSTAL},	59,	74,	73,	65,	58,	65,	58},
		{76,	"Shaolite",		{MELEE},			40,	58,	68,	43,	58,	54,	61},
		{77,	"Shaolant",		{MELEE},			47,	68,	80,	51,	68,	64,	72},
		{78,	"Cycrox",		{DIGITAL,TOXIC},	73,	62,	48,	54,	61,	75,	71},
		{79,	"Hocus",		{MENTAL},			49,	61,	65,	55,	34,	55,	34},
		{80,	"Pocus",		{MENTAL},			70,	73,	78,	61,	40,	87,	51},
		{81,	"Smolzy",		{ELECTRIC},			40,	60,	65,	65,	26,	22,	26},
		{82,	"Sparzy",		{ELECTRIC},			62,	78,	78,	81,	45,	40,	45},
		{83,	"Golzy",		{ELECTRIC,MELEE},	76,	78,	82,	84,	49,	40,	48},
		{84,	"Mushi",		{TOXIC},			48,	33,	68,	48,	36,	48,	29},
		{85,	"Mushook",		{TOXIC,MELEE},		67,	45,	81,	76,	75,	49,	41},
		{86,	"Magmis",		{FIRE},				52,	51,	37,	55,	42,	45,	35},
		{87,	"Mastione",		{FIRE,WATER},		76,	62,	52,	91,	65,	62,	45},
		{88,	"Umishi",		{WATER},			51,	76,	80,	21,	34,	63,	45},
		{89,	"Ukama",		{WATER},			68,	90,	100,34,	51,	76,	54},
		{90,	"Galvanid",		{ELECTRIC},			59,	49,	46,	70,	60,	50,	43},
		{91,	"Raignet",		{ELECTRIC},			68,	57,	54,	81,	69,	58,	50},
		{92,	"Smazee",		{MELEE},			49,	55,	66,	69,	44,	37,	37},
		{93,	"Baboong",		{MELEE},			62,	61,	75,	79,	51,	41,	41},
		{94,	"Seismunch",	{MELEE,EARTH},		70,	65,	85,	89,	54,	43,	43},
		{95,	"Zizare",		{EARTH},			60,	75,	30,	90,	95,	40,	62},
		{96,	"Gorong",		{MELEE},			86,	42,	63,	71,	100,12,	64},
		{97,	"Mitty",		{MENTAL},			40,	46,	50,	80,	75,	42,	61},
		{98,	"Sanbi",		{MENTAL},			71,	51,	64,	89,	79,	42,	61},
		{99,	"Momo",			{NEUTRAL},			75,	64,	89,	46,	49,	79,	75},
		{100,	"Kuri",			{EARTH},			52,	30,	52,	60,	58,	35,	31},
		{101,	"Kauren",		{EARTH},			81,	45,	65,	81,	74,	52,	51},
		{102,	"Spriole",		{NATURE},			72,	38,	65,	42,	70,	37,	31},
		{103,	"Deendre",		{NATURE},			80,	42,	70,	48,	74,	42,	35},
		{104,	"Cerneaf",		{NATURE},			91,	52,	79,	60,	88,	43,	46},
		{105,	"Toxolotl",		{TOXIC},			59,	40,	47,	50,	64,	65,	37},
		{106,	"Noxolotl",		{TOXIC},			72,	49,	61,	61,	78,	85,	45},
		{107,	"Blooze",		{TOXIC},			68,	50,	33,	43,	52,	46,	54},
		{108,	"Goolder",		{TOXIC},			125,70,	10,	64,	62,	68,	62},
		{109,	"Zephyruff",	{TOXIC,WIND},		55,	34,	68,	43,	47,	50,	51},
		{110,	"Volarend",		{TOXIC,WIND},		60,	42,	74,	66,	55,	68,	92},
		{111,	"Grumvel",		{EARTH},			70,	36,	55,	50,	65,	48,	60},
		{112,	"Grumper",		{EARTH,ELECTRIC},	75,	41,	50,	56,	75,	81,	67},
		{113,	"Ganki",		{ELECTRIC,WIND},	38,	46,	61,	57,	38,	62,	73},
		{114,	"Gazuma",		{ELECTRIC,WIND},	46,	53,	67,	68,	43,	81,	91},
		{115,	"Oceara",		{WATER},			64,	42,	100,54,	51,	105,65},
		{116,	"Yowlar",		{NEUTRAL},			81,	71,	40,	77,	82,	50,	70},
		{117,	"Droply",		{WATER,EARTH},		60,	60,	25,	65,	60,	39,	54},
		{118,	"Garyo",		{WATER,EARTH},		74,	65,	38,	78,	68,	56,	66},
		{119,	"Broccoblin",	{NATURE},			59,	51,	38,	35,	32,	61,	59},
		{120,	"Broccorc",		{NATURE,MELEE},		66,	56,	42,	54,	50,	68,	65},
		{121,	"Broccolem",	{NATURE,MELEE},		74,	63,	47,	60,	60,	76,	73},
		{122,	"Shuine",		{CRYSTAL,WATER},	43,	90,	81,	67,	49,	72,	60},
		{123,	"Nessla",		{WATER,ELECTRIC},	60,	62,	66,	70,	56,	79,	72},
		{124,	"Valiar",		{MENTAL},			50,	74,	69,	79,	68,	54,	61},
		{125,	"Pupoise",		{DIGITAL,NATURE},	51,	37,	49,	66,	54,	40,	42},
		{126,	"Loatle",		{DIGITAL,MENTAL},	84,	51,	65,	75,	67,	51,	57},
		{127,	"Kalazu",		{WATER},			63,	24,	28,	54,	70,	38,	44},
		{128,	"Kalabyss",		{WATER,TOXIC},		82,	37,	37,	75,	100,65,	55},
		{129,	"Adoroboros",	{TOXIC,MENTAL},		65,	66,	60,	29,	42,	70,	110},
		{130,	"Tuwai",		{WIND},				54,	47,	58,	62,	45,	60,	47},
		{131,	"Tukai",		{WIND,WATER},		75,	68,	65,	53,	49,	74,	78},
		{132,	"Tulcan",		{WIND,FIRE},		62,	54,	65,	62,	69,	79,	49},
		{133,	"Tuvine",		{WIND,CRYSTAL},		58,	47,	70,	78,	111,60,	47},
		{134,	"Turoc",		{WIND,EARTH},		105,48,	60,	75,	68,	47,	45},
		{135,	"Tuwire",		{WIND,DIGITAL},		-1,	-1,	-1,	-1,	-1,	-1,	-1},	// stats inconnues
		{136,	"Tutsu",		{WIND,MELEE},		68,	56,	84,	74,	63,	55,	61},
		{137,	"Kinu",			{NATURE,MENTAL},	47,	74,	74,	53,	41,	69,	96},
		{138,	"Vulvir",		{FIRE,EARTH},		59,	54,	57,	47,	64,	47,	31},
		{139,	"Vulor",		{FIRE,EARTH},		65,	59,	63,	49,	71,	49,	32},
		{140,	"Vulcrane",		{FIRE,EARTH},		76,	65,	73,	74,	86,	64,	35},
		{141,	"Pigepic",		{WIND},				54,	72,	58,	65,	69,	45,	69},
		{142,	"Akranox",		{EARTH,TOXIC},		71,	52,	71,	71,	64,	71,	64},
		{143,	"Koish",		{WATER},			57,	61,	66,	76,	68,	70,	58},
		{144,	"Vulffy",		{EARTH,NATURE},		50,	70,	60,	39,	55,	76,	85},
		{145,	"Chubee",		{DIGITAL,WIND},		64,	40,	36,	30,	65,	28,	65},
		{146,	"Waspeen",		{DIGITAL,CRYSTAL},	92,	64,	36,	58,	80,	50,	70},
		{147,	"Mawtle",		{DIGITAL,NATURE},	62,	50,	55,	32,	50,	42,	60},
		{148,	"Mawmense",		{DIGITAL,NATURE},	100,52,	41,	42,	52,	56,	88},
		{149,	"Hazrat",		{TOXIC,FIRE},		52,	69,	76,	90,	54,	57,	51},
		{150,	"Minttle",		{MENTAL},			39,	40,	20,	50,	25,	25,	25},
		{151,	"Minox",		{MENTAL,ELECTRIC},	69,	50,	60,	74,	61,	35,	35},
		{152,	"Minothor",		{MENTAL,ELECTRIC},	80,	59,	61,	86,	70,	44,	44},
		{153,	"Maoala",		{MELEE,MENTAL},		65,	70,	57,	80,	61,	57,	58},
		{154,	"Venx",			{NEUTRAL},			55,	51,	54,	81,	81,	81,	81},
		{155,	"Venmet",		{NEUTRAL,MELEE},	72,	60,	60,	78,	78,	48,	48},
		{156,	"Vental",		{NEUTRAL,MENTAL},	55,	63,	74,	48,	48,	78,	78},
		{157,	"Chimurian",	{NATURE,CRYSTAL},	49,	54,	84,	67,	78,	37,	84},
		{158,	"Arachnyte",	{NEUTRAL,DIGITAL},	71,	55,	42,	64,	55,	79,	74},
		{159,	"Thaiko",		{DIGITAL,MELEE},	50,	46,	60,	36,	49,	68,	41},
		{160,	"Monkko",		{DIGITAL,MELEE},	84,	55,	59,	43,	71,	84,	48},
		{161,	"Anahir",		{CRYSTAL,FIRE},		54,	36,	31,	50,	101,50,	101},
		{162,	"Anatan",		{CRYSTAL,FIRE},		62,	48,	32,	50,	103,50,	103},
		{163,	"Tyranak",		{FIRE,NATURE},		78,	48,	34,	81,	74,	57,	76},
		{164,	"Volgon",		{ELECTRIC},			60,	38,	60,	58,	62,	90,	67}
	};
}

TemtemTable::~TemtemTable() {}

void	TemtemTable::getYourTemtemResults(const Temtem &t1, const Temtem &t2)
{
	std::cout << "\n";
	if (t1.name.empty())
		return ;
	std::ostringstream oss;
	oss << C_YELLOW << " Result " << C_GREEN << t1.name << C_YELLOW << " → " << C_CYAN << t2.name << " " C_RESET;
	printTitle(oss.str());
	std::cout << TEMTEM_STRING;
	const str atk1 = !t1.types.empty() ? t1.types[0] : "";
	const str atk2 = t1.types.size() > 1 ? t1.types[1] : "";
	const str def1 = !t2.types.empty() ? t2.types[0] : "";
	const str def2 = t2.types.size() > 1 ? t2.types[1] : "";
	float mult1 = GetMultiplier(atk1, "", def1, def2);
	printTypeAttack(mult1, t1.name + " (" + atk1 + ")", TEMTEM_STRING);
	if (!atk2.empty())
	{
		float mult2 = GetMultiplier(atk2, "", def1, def2);
		printTypeAttack(mult2, t1.name + " (" + atk2 + ")", TEMTEM_STRING);
	}
	std::cout << std::endl;
}

float maxEffectiveness(const std::pair<float, float>& mult)
{
    return std::max(mult.first, mult.second);
}

void TemtemTable::TemtemToAttack(const Temtem &t1, const Temtem &t2)
{
	str choice = get_input(C_YELLOW + str("Do you want the list of effective :\n") + C_GREEN + "1 - types ?\n"
				+ C_CYAN + "2 - Temtems ?\n" + C_YELLOW + "Choice : " + C_RESET);
	while (choice != "1" && choice != "types" && choice != "2" && choice != "temtems")
	{
		clear();
		std::cout << C_RED << "Invalid choice !" << C_RESET << "\n";
		choice = get_input(C_YELLOW + str("Do you want the list of effective :\n") + C_GREEN + "1 - types ?\n"
				+ C_CYAN + "2 - Temtems ?\n" + C_YELLOW + "Choice : " + C_RESET);
	}
	const str atk1 = !t1.types.empty() ? t1.types[0] : "";
	const str atk2 = t1.types.size() > 1 ? t1.types[1] : "";
	const str def1 = !t2.types.empty() ? t2.types[0] : "";
	const str def2 = t2.types.size() > 1 ? t2.types[1] : "";
	str type = " (" + (!def2.empty() ? def1 + "/" + def2 : def1) + ")";
	printTitle(C_GREEN + (str)(!t1.name.empty() ? " Other types " : " Effective types ") + C_YELLOW "against " C_CYAN
				+ t2.name + type + " ");
	if (choice == "2" || choice == "temtems")
	{
		std::vector<std::pair<Temtem, std::pair<float, float>>> results;
		for (const auto& temtem : temtemTable)
			if (!temtem.name.empty())
				results.push_back({temtem, {GetMultiplier(temtem.types[0], "", def1, def2), temtem.types.size() > 1 ? GetMultiplier(temtem.types[1], "", def1, def2) : -1}});
		std::sort(results.begin(), results.end(),
		[](const auto& a, const auto& b)
		{
			float effA = maxEffectiveness(a.second);
			float effB = maxEffectiveness(b.second);
			if (effA != effB)
				return effA > effB;
			return a.first.name < b.first.name;
		});
		std::cout << TEMTEM_STRING;
		for (const auto& [t, mult] : results)
		{
			if (t.name == t1.name|| t.name == t2.name || !(mult.first > 1.0f || mult.second > 1.0f))
				continue;
			if (mult.first > 1.0f)
				printTypeAttack(mult.first, t.name + " (" + t.types[0] + ")", TEMTEM_STRING);
			if (mult.second != -1)
			{
				if (mult.second <= 1.0f)
					continue;
				else if (mult.first > 1.0f)
					printTypeAttack(mult.second, str(t.name.size(), ' ') + " (" + t.types[1] + ")", TEMTEM_STRING);
				else
					printTypeAttack(mult.second, t.name + " (" + t.types[1] + ")", TEMTEM_STRING);
			}
		}
	}
	else if (choice == "1" || choice == "types")
		TypeToAttack(atk1, def1, atk2, def2, 0);
}