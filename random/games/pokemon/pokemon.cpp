#include "pokémon.hpp"

float TypesTable::getMultiplierOne(const Type& atk, const str& defName) const
{
	for (const auto& s : atk.super_effective)
		if (s == defName) return 2.0f;
	for (const auto& s : atk.less_effective)
		if (s == defName) return 0.5f;
	for (const auto& s : atk.ineffective)
		if (s == defName) return 0.0f;
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
	typesTable.push_back(Type(NORMAL, {}, {NORMAL, PLANTE, FEU, EAU, ELECTRIQUE, GLACE, COMBAT, POISON, SOL, VOL, PSY, INSECTE, DRAGON, TENEBRES, FEE}, {ROCHE, ACIER}, {SPECTRE}));
	typesTable.push_back(Type(PLANTE, {EAU, SOL, ROCHE}, {NORMAL, ELECTRIQUE, GLACE, COMBAT, PSY, SPECTRE, TENEBRES, FEE}, {PLANTE, FEU, POISON, VOL, INSECTE, DRAGON, ACIER}, {}));
	typesTable.push_back(Type(FEU, {PLANTE, GLACE, INSECTE, ACIER}, {NORMAL, ELECTRIQUE, COMBAT, POISON, SOL, VOL, PSY, SPECTRE, TENEBRES, FEE}, {FEU, EAU, ROCHE, DRAGON}, {}));
	typesTable.push_back(Type(EAU, {FEU, SOL, ROCHE}, {NORMAL, ELECTRIQUE, GLACE, COMBAT, POISON, VOL, PSY, INSECTE, SPECTRE, TENEBRES, ACIER, FEE}, {EAU, PLANTE, DRAGON}, {}));
	typesTable.push_back(Type(ELECTRIQUE, {EAU, VOL}, {NORMAL, FEU, GLACE, COMBAT, POISON, PSY, INSECTE, ROCHE, SPECTRE, TENEBRES, ACIER, FEE}, {ELECTRIQUE, PLANTE, DRAGON}, {SOL}));
	typesTable.push_back(Type(GLACE, {PLANTE, SOL, VOL, DRAGON}, {NORMAL, ELECTRIQUE, COMBAT, POISON, PSY, INSECTE, ROCHE, SPECTRE, TENEBRES, FEE}, {FEU, EAU, GLACE, ACIER}, {}));
	typesTable.push_back(Type(COMBAT, {NORMAL, GLACE, ROCHE, TENEBRES, ACIER}, {PLANTE, FEU, EAU, ELECTRIQUE, COMBAT, SOL, DRAGON}, {POISON, VOL, PSY, INSECTE, FEE}, {SPECTRE}));
	typesTable.push_back(Type(POISON, {PLANTE, FEE}, {NORMAL, FEU, EAU, ELECTRIQUE, GLACE, COMBAT, VOL, PSY, INSECTE, DRAGON, TENEBRES}, {POISON, SOL, ROCHE, SPECTRE}, {ACIER}));
	typesTable.push_back(Type(SOL, {FEU, ELECTRIQUE, POISON, ROCHE, ACIER}, {NORMAL, EAU, GLACE, COMBAT, SOL, PSY, SPECTRE, DRAGON, TENEBRES, FEE}, {PLANTE, INSECTE}, {VOL}));
	typesTable.push_back(Type(VOL, {PLANTE, COMBAT, INSECTE}, {NORMAL, FEU, EAU, GLACE, POISON, SOL, VOL, PSY, SPECTRE, DRAGON, TENEBRES, FEE}, {ELECTRIQUE, ROCHE, ACIER}, {}));
	typesTable.push_back(Type(PSY, {COMBAT, POISON}, {NORMAL, PLANTE, FEU, EAU, ELECTRIQUE, GLACE, SOL, VOL, INSECTE, ROCHE, SPECTRE, DRAGON, FEE}, {PSY, ACIER}, {TENEBRES}));
	typesTable.push_back(Type(INSECTE, {PLANTE, PSY, TENEBRES}, {NORMAL, EAU, ELECTRIQUE, GLACE, SOL, INSECTE, ROCHE, DRAGON}, {FEU, COMBAT, POISON, VOL, SPECTRE, ACIER, FEE}, {}));
	typesTable.push_back(Type(ROCHE, {GLACE, VOL, INSECTE}, {NORMAL, PLANTE, FEU, EAU, ELECTRIQUE, POISON, PSY, ROCHE, SPECTRE, DRAGON, TENEBRES, FEE}, {COMBAT, SOL, ACIER}, {}));
	typesTable.push_back(Type(SPECTRE, {PSY, SPECTRE}, {PLANTE, FEU, EAU, ELECTRIQUE, GLACE, COMBAT, POISON, SOL, VOL, INSECTE, ROCHE, DRAGON, ACIER, FEE}, {TENEBRES}, {NORMAL}));
	typesTable.push_back(Type(DRAGON, {DRAGON}, {NORMAL, PLANTE, FEU, EAU, ELECTRIQUE, GLACE, COMBAT, POISON, SOL, VOL, PSY, INSECTE, ROCHE, SPECTRE, TENEBRES}, {ACIER}, {FEE}));
	typesTable.push_back(Type(TENEBRES, {PSY, SPECTRE}, {NORMAL, PLANTE, FEU, EAU, ELECTRIQUE, GLACE, POISON, SOL, VOL, INSECTE, ROCHE, DRAGON, ACIER}, {COMBAT, TENEBRES, FEE}, {}));
	typesTable.push_back(Type(ACIER, {GLACE, ROCHE, FEE}, {NORMAL, EAU, COMBAT, POISON, SOL, VOL, PSY, INSECTE, SPECTRE, DRAGON, TENEBRES}, {PLANTE, FEU, ELECTRIQUE, ACIER}, {}));
	typesTable.push_back(Type(FEE, {COMBAT, DRAGON, TENEBRES}, {NORMAL, FEU, EAU, ELECTRIQUE, GLACE, VOL, SOL, PSY, INSECTE, ROCHE, SPECTRE, FEE}, {PLANTE, POISON, ACIER}, {}));
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
		res = " (degomme les deux)";
	else if (resist1)
		res = " (degomme " + def1 + ")";
	else if (resist2)
		res = " (degomme " + def2 + ")";
	else
		res = " (neutre)";
	return total;
}

void TypesTable::TypeToAttack(const str& atk1, const str& def1, const str& atk2, const str& def2) const
{
	printTitle(C_GREEN + (str)(!atk1.empty() ? " Autres types " : " Types efficaces ") + C_YELLOW " contre " C_CYAN + def1 + (str)(def2 != "" ? "/" + def2 + " " : " "));
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
		printTypeAttack(mult, name);
	}
}

void TypesTable::TypeToDefend(const str& atk1, const str& def1, const str& atk2, const str& def2) const
{
	printTitle(C_YELLOW " Résiste à " C_CYAN + def1 + (str)(def2 != "" ? "/" + def2 : "") + C_YELLOW " " C_RESET);
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
		float mult = results[i].second;
		float resist = (mult == 0.0f) ? 0.0f : 1.0f / mult;
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
	oss << C_YELLOW << " Résultat " << C_GREEN << atk1;
	if (!atk2.empty())
		oss << "/" << atk2;
	oss << C_YELLOW << " → " << C_CYAN << def1;
	if (!def2.empty())
		oss << "/" << def2;
	oss << " ";
	printTitle(oss.str());
	std::cout << STATS_STRING;
	float mult1 = GetMultiplier(atk1, "", def1, def2);
	printTypeAttack(mult1, atk1);
	if (!atk2.empty())
	{
		float mult2 = GetMultiplier(atk2, "", def1, def2);
		printTypeAttack(mult2, atk2);
	}
	std::cout << std::endl;
}


void TypesTable::getYourDefResults1Type(const str def1, const str def2, const str atk)
{
	float mult1 = GetMultiplier(atk, "", def1, "");
	float defMult1 = (mult1 == 0.0f) ? 0.0f : 1.0f / mult1;
	float defMult2 = 1.0f;
	float mult2 = 1.0f;
	if (!def2.empty())
	{
		mult2 = GetMultiplier(atk, "", def2, "");
		defMult2 = (mult2 == 0.0f) ? 0.0f : 1.0f / mult2;
	}
	float finalDef = defMult1 * defMult2;
	float finalmult = mult1 * mult2;
	std::cout << C_YELLOW << "Résistance à " C_CYAN << atk << C_YELLOW" :\n" << STATS_STRING << C_RESET;
	printTypeDefense(defMult1, "🔴" + def1, atk, "", mult1 < 1.0f);
	if (!def2.empty())
	{
		printTypeDefense(defMult2, "🔵" + def2, atk, "", mult2 < 1.0f);
		printTypeDefense(finalDef, "🧬Combiné", atk, "", finalmult < 1.0f);
	}
	std::cout << "\n";
}

void TypesTable::getYourDefResults(const str def1, const str def2, const str atk1, const str atk2)
{
	std::cout << C_YELLOW << "\n";
	if (def1.empty())
		return;
	std::ostringstream oss;
	oss << C_YELLOW << " Résultat " << C_GREEN << def1;
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
