#include "Temtem.hpp"

float TypesTable::getMultiplierOne(const Type& atk, const str& defName) const
{
	for (const auto& s : atk.super_effective)
		if (s == defName) return 2.0f;
	for (const auto& s : atk.less_effective)
		if (s == defName) return 0.5f;
	return 1.0f;
}

const Type* TypesTable::getType(const str& name) const
{
	for (const auto& t : typesTable)
		if (t.name == name)
			return &t;
	return nullptr;
}

TypesTable::TypesTable()
{
	typesTable.push_back(Type(NEUTRAL, {}, {FIRE, WATER, ELECTRIC, NATURE, EARTH, WIND, MELEE, CRYSTAL, DIGITAL, TOXIC, NEUTRAL}, {MENTAL}));
	typesTable.push_back(Type(FIRE, {NATURE, CRYSTAL}, {NEUTRAL, ELECTRIC, WIND, MENTAL, MELEE, DIGITAL, TOXIC}, {FIRE, WATER, EARTH}));
	typesTable.push_back(Type(WATER, {FIRE, EARTH, DIGITAL}, {NEUTRAL, ELECTRIC, WIND, MENTAL, MELEE, CRYSTAL}, {WATER, NATURE, TOXIC}));
	typesTable.push_back(Type(NATURE, {WATER, EARTH}, {NEUTRAL, ELECTRIC, WIND, MENTAL, MELEE, CRYSTAL, DIGITAL}, {FIRE, NATURE, TOXIC}));
	typesTable.push_back(Type(ELECTRIC, {WATER, MENTAL, WIND, DIGITAL}, {NEUTRAL, FIRE, MELEE, TOXIC}, {NATURE, ELECTRIC, EARTH, CRYSTAL}));
	typesTable.push_back(Type(EARTH, {FIRE, ELECTRIC, CRYSTAL}, {NEUTRAL, EARTH, MENTAL, MELEE, DIGITAL, TOXIC}, {WATER, NATURE, WIND}));
	typesTable.push_back(Type(MENTAL, {NEUTRAL, MELEE}, {FIRE, WATER, ELECTRIC, NATURE, EARTH, WIND, MENTAL, DIGITAL, TOXIC}, {CRYSTAL}));
	typesTable.push_back(Type(WIND, {TOXIC}, {EARTH, NEUTRAL, FIRE, WATER, NATURE, MENTAL, MELEE, CRYSTAL, DIGITAL}, {ELECTRIC, WIND}));
	typesTable.push_back(Type(DIGITAL, {MENTAL, DIGITAL, MELEE}, {NEUTRAL, FIRE, WATER, ELECTRIC, NATURE, EARTH, WIND, CRYSTAL, TOXIC}, {}));
	typesTable.push_back(Type(MELEE, {EARTH, CRYSTAL}, {NEUTRAL, FIRE, WATER, ELECTRIC, NATURE, WIND, DIGITAL, TOXIC}, {MELEE, MENTAL}));
	typesTable.push_back(Type(CRYSTAL, {ELECTRIC, MENTAL}, {NEUTRAL, WATER, NATURE, WIND, MELEE, CRYSTAL, DIGITAL, TOXIC}, {FIRE, EARTH}));
	typesTable.push_back(Type(TOXIC, {WATER, NATURE}, {NEUTRAL, FIRE, ELECTRIC, WIND, MENTAL, MELEE}, {EARTH, DIGITAL, CRYSTAL, TOXIC}));
}

TypesTable::~TypesTable() {};

float TypesTable::GetMultiplier(const str& atk1, const str& atk2, const str& def1, const str& def2) const
{
	const Type* A1 = getType(atk1);
	const Type* A2 = (atk2 == "") ? nullptr : getType(atk2);

	float total = 1.0f;

	if (A1)
	{
		if (def1 != "")
			total *= getMultiplierOne(*A1, def1);
		if (def2 != "")
			total *= getMultiplierOne(*A1, def2);
	}
	if (A2)
	{
		if (def1 != "")
			total *= getMultiplierOne(*A2, def1);
		if (def2 != "")
			total *= getMultiplierOne(*A2, def2);
	}
	return total;
}

float TypesTable::GetMultiplier(const str& atk, const str& def1, const str& def2, str& res) const
{
	const Type* A = getType(atk);
	if (!A)
	{
		res = " N/A";
		return 1.0f;
	}
	float total = 1.0f;
	bool resist1 = false;
	bool resist2 = false;

	std::vector<std::pair<refwrapconststr, refwrapbool>> defs;
	defs.emplace_back(std::ref(def1), std::ref(resist1));
	defs.emplace_back(std::ref(def2), std::ref(resist2));
	for (auto& p : defs)
	{
		const str& def = p.first.get();
		bool& resist = p.second.get();

		if (!def.empty())
		{
			float m = getMultiplierOne(*A, def);
			total *= m;
			if (m > 1.0f) resist = true;
		}
	}
	if (resist1 && resist2)
		res = " (destroy both)";
	else if (resist1)
		res = " (destroy " + def1 + ")";
	else if (resist2)
		res = " (destroy " + def2 + ")";
	else
		res = " (neutral)";
	return total;
}

void TypesTable::TypeToAttack(const str& atk1, const str& def1, const str& atk2, const str& def2, bool title) const
{
	if (title)
		printTitle(C_GREEN + (str)(!atk1.empty() ? " Other types " : " Effective types ") + C_YELLOW "against " C_CYAN + def1 + (str)(def2 != "" ? "/" + def2 + " " : " "));
	std::vector<std::pair<str, float>> results;
	for (const auto& atk : typesTable)
		results.push_back({atk.name, GetMultiplier(atk.name, "", def1, def2)});
	std::sort(results.begin(), results.end(),
			[](const auto& a, const auto& b){ return a.second > b.second; });
	std::cout << STATS_STRING;
	for (const auto& [name, mult] : results)
	{
		if (name == atk1 || name == atk2)
			continue;
		printTypeAttack(mult, name, STATS_STRING);
	}
}

void TypesTable::TypeToDefend(const str& atk1, const str& def1, const str& atk2, const str& def2) const
{
	printTitle(C_YELLOW " Resist to " C_CYAN + def1 + (str)(def2 != "" ? "/" + def2 : "") + C_YELLOW " " C_RESET);
	std::vector<std::pair<str, float>> results;
	std::vector<std::pair<bool, bool>> res;
	for (const auto& def : typesTable)
	{
		results.push_back({def.name, GetMultiplier(def1, def2, def.name, "")});
		res.push_back({GetMultiplier(def1, "", def.name, "") < 1.0f, ((def2 != "") ? GetMultiplier(def2, "", def.name, "") : 1.0f) < 1.0f});
	}
	std::sort(results.begin(), results.end(),
			[](const auto& a, const auto& b){ return a.second < b.second; });
	std::cout << STATS_STRING;
	for (size_t i = 0; i < results.size(); ++i)
	{
		str name = results[i].first;
		if (name == atk1 || name == atk2)
			continue ;
		float resist = 1.0f / results[i].second;
		bool res1 = res[i].first;
		printTypeDefense(resist, name, def1, def2, res1);
	}
}

void	TypesTable::getYourAtkResults(const str atk1, const str atk2, const str def1, const str def2)
{
	std::cout << "\n";
	if (atk1.empty())
		return ;
	std::ostringstream oss;
	oss << C_YELLOW << " Result " << C_GREEN << atk1;
	if (!atk2.empty())
		oss << "/" << atk2;
	oss << C_YELLOW << " → " << C_CYAN << def1;
	if (!def2.empty())
		oss << "/" << def2;
	oss << " ";
	printTitle(oss.str());
	std::cout << STATS_STRING;
	float mult1 = GetMultiplier(atk1, "", def1, def2);
	printTypeAttack(mult1, atk1, STATS_STRING);
	if (!atk2.empty())
	{
		float mult2 = GetMultiplier(atk2, "", def1, def2);
		printTypeAttack(mult2, atk2, STATS_STRING);
	}
	std::cout << std::endl;
}


void TypesTable::getYourDefResults1Type(const str def1, const str def2, const str atk)
{
	float mult1 = GetMultiplier(atk, "", def1, "");
	float defMult1 = 1.0f / mult1;
	float defMult2 = 1.0f;
	float mult2 = 1.0f;
	if (!def2.empty())
	{
		mult2 = GetMultiplier(atk, "", def2, "");
		defMult2 = 1.0f / mult2;
	}
	float finalDef = defMult1 * defMult2;
	float finalmult = mult1 * mult2;
	std::cout << C_YELLOW << "Resist to " C_CYAN << atk << C_YELLOW" :\n" << STATS_STRING << C_RESET;
	printTypeDefense(defMult1, "🔴" + def1, atk, "", mult1 < 1.0f);
	if (!def2.empty())
	{
		printTypeDefense(defMult2, "🔵" + def2, atk, "", mult2 < 1.0f);
		printTypeDefense(finalDef, "🧬Combined", atk, "", finalmult < 1.0f);
	}
	std::cout << "\n";
}

void TypesTable::getYourDefResults(const str def1, const str def2, const str atk1, const str atk2)
{
	std::cout << C_YELLOW << "\n";
	if (def1.empty())
		return;
	std::ostringstream oss;
	oss << C_YELLOW << " Result " << C_GREEN << def1;
	if (!def2.empty())
		oss << "/" << def2;
	oss << C_YELLOW << " ← " << C_CYAN << atk1;
	if (!atk2.empty())
		oss << "/" << atk2;
	oss << " ";
	printTitle(oss.str());
	getYourDefResults1Type(def1, def2, atk1);
	if (!atk2.empty())
		getYourDefResults1Type(def1, def2, atk2);
	std::cout << "\n";
}
