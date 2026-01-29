#include "temtemlist.hpp"

s_Type::s_Type(str n, vectstr sup, vectstr nor, vectstr less)
		: name(n), super_effective(sup), normal(nor), less_effective(less)
{}

int utf8Size(const str& str)
{
    int len = 0;
    for (unsigned char c : str)
        if ((c & 0xC0) != 0x80) len++;
    return len;
}

int displayWidth(const str& str)
{
    std::setlocale(LC_ALL, "");
    int width = 0;
    for (size_t i = 0; i < str.size(); )
	{
        wchar_t wc;
        int n = mbtowc(&wc, str.c_str() + i, str.size() - i);
        if (n <= 0) break;
        width += wcwidth(wc);
        i += n;
    }
    return width;
}

str stripAnsi(const str& s)
{
    str out;
    for (size_t i = 0; i < s.size();)
    {
        if (s[i] == '\033' && i + 1 < s.size() && s[i + 1] == '[')
        {
            i += 2;
            while (i < s.size() && s[i] != 'm')
                i++;
            if (i < s.size())
                i++;
        }
        else
            out += s[i++];
    }
    return out;
}

str getMultStab(const float &resist, str &multStr, const str mode)
{
	float mult_stab = std::atoi(multStr.substr(2).c_str());
	if (mode == "atk")
		mult_stab = (resist < 1.0f) ? mult_stab / 1.25f : mult_stab * 1.25f;
	else
		mult_stab = (resist > 1.0f) ? mult_stab / 1.25f : mult_stab * 1.25f;
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << mult_stab;
	str multStabStr = oss.str();
	return multStabStr;
}

str GetColor(float val)
{
	if		(val == 4)		return C_LIGHT_PURPLE;
	else if	(val == 2)		return C_GREEN;
	else if	(val == 1)		return C_YELLOW_BRIGHT;
	else if	(val == 0.5f)	return C_ORANGE;
	else					return C_RED;
}

void	GetColorAtk(float mult, str &color, str &multStr, str &msg)
{
	if (mult >= 4.0f)		{ color = C_LIGHT_PURPLE;	multStr = " x4";		msg = "(Gigachad)"; }
	else if (mult >= 2.0f)	{ color = C_GREEN;			multStr = " x2";		msg = "(goes to the gym)"; }
	else if (mult == 1.0f)	{ color = C_YELLOW_BRIGHT;	multStr = " x1";		msg = "(neutral)"; }
	else if (mult >= 0.5f)	{ color = C_ORANGE;			multStr = " /2";		msg = "(body positive)"; }
	else					{ color = C_RED;			multStr = " /4";		msg = "(yamcha)"; }
}

void	GetColorDef(float resist, str &color, str &multStr, str &msg, const str& atk1, const str& atk2, bool res1)
{
	if (resist == 0.25f)	{ color = C_RED;			multStr = " x4";		msg = " (get crushed)";}
	else if (resist == 0.5f)	{ color = C_ORANGE;			multStr = " x2";		msg = (atk2 != "" ? (" (get crushed by " + (!res1 ? atk1 : atk2) + ")") : " (get crushed)"); }
	else if (resist == 1.0f)	{ color = C_YELLOW_BRIGHT;	multStr = " x1";		msg = " (neutral)"; }
	else if (resist == 2.0f)	{ color = C_GREEN;			multStr = " /2";		msg = (atk2 != "" ? (" (resist to " + (!res1 ? atk1 : atk2) + ")") : " (resist)"); }
	else						{ color = C_LIGHT_PURPLE;	multStr = " /4";		msg = " (resist to both)";}
}

str removeANSI(const str& s)
{
    static const std::regex ansi_regex("\033\\[[0-9;]*m");
    return std::regex_replace(s, ansi_regex, "");
}

std::vector<std::pair<str, size_t>> getColumnWidths(const str& titleLine)
{
    std::vector<std::pair<str, size_t>> colWidths;
    std::istringstream iss(titleLine);
    vectstr titles;
    str word;
    while (iss >> word)
	{
		str category = word;
		if (category == "DMG")
		{
			while (word != "STAB")
			{
				iss >> word;
				category += " " + word;
			}
		}
		str noansi = removeANSI(category);
		if (!noansi.empty())
        	titles.push_back(noansi);
	}
    size_t pos = 0;
    for (size_t i = 0; i < titles.size(); ++i)
    {
        size_t start = titleLine.find(titles[i], pos);
        size_t width;
        if (i < titles.size() - 1)
			width = titleLine.find(titles[i + 1], pos) - start;
        else
            width = titleLine.size() - start;
        colWidths.push_back({titles[i], width});
        pos = start;
    }
    return colWidths;
}

size_t trailingSpaces(const str& s)
{
    size_t count = 0;
    for (size_t i = s.size(); i > 0 && s[i - 1] == ' '; --i)
        ++count;
    return count;
}

str centerText(const str& text, str categorie)
{
	size_t width = categorie.size() - trailingSpaces(categorie);
    if (width <= text.size())
        return text;
    size_t pad = (width - text.size()) / 2;
    return str(pad, ' ') + text + str(pad, ' ');
}

void printTypeAttack(float mult, const str &name, const str &title)
{
	str color;
	str multStr;
	str msg;
	GetColorAtk(mult, color, multStr, msg);
	str multStabStr = getMultStab(mult, multStr, "atk");
	if (mult > 0.0f && mult < 1.0f)
		multStabStr = "/" + multStabStr;
	else if (mult >= 1.0f)
		multStabStr = "x" + multStabStr;
	else
		multStabStr = "0";
	auto colWidths = getColumnWidths(title);
	std::cout << color
		<< std::setw(colWidths[0].second) << std::left << name
		<< std::setw(colWidths[1].second) << std::left << centerText(multStr, colWidths[1].first)
		<< std::setw(colWidths[2].second) << std::left << centerText(multStabStr, colWidths[2].first)
		<< std::setw(colWidths[3].second) << std::left << msg
		<< C_RESET << "\n"; // multiplicateur avec STAB
}

void printTypeDefense(float resist, const str &name, const str& atk1, const str& atk2, bool res1)
{
	str color;
	str multStr;
	str msg;
	GetColorDef(resist, color, multStr, msg, atk1, atk2, res1);
	str multStabStr = getMultStab(resist, multStr, "def");
	if (resist >= 0.25 && resist <= 1.0f)
		multStabStr = "x" + multStabStr;
	else if (resist > 1.0f)
		multStabStr = "/" + multStabStr;
	int center1 = (utf8Size(multStr) % 2) ? (utf8Size(multStr) / 2) : (utf8Size(multStr) / 2) - 1;
	int center2 = utf8Size(multStabStr) / 2;
	int diff = displayWidth(name) - name.size();
	std::cout << color << std::setw(18 - (center1) - diff) << std::left << name
		<< std::setw(17 - (center2 - center1)) << multStr		// multiplicateur normal
		<< std::setw(11 + center2) << multStabStr << msg << C_RESET << "\n"; // multiplicateur avec STAB
}

void printTitle(const str title)
{
	int titleLen = displayWidth(stripAnsi(title)), statslen = std::size(STATS_STRING) - 4;
	titleLen += !(titleLen % 2) ? 1 : 0;
	str equals = C_YELLOW;
	equals.append((statslen - titleLen) / 2, '=');
	equals += C_RESET;
	std::cout << equals << title << equals << std::endl;
}

void	clear()
{
	#ifdef _WIN32
		system("CLS");
	#else
		system("clear");
	#endif
}

void temtemCapital(str &name)
{
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	if (!name.empty())
		name[0] = std::toupper(name[0]);
}

void GetTypeResults(refwrapstr types[4], TypesTable &table)
{
	str prompts[4] = {
		C_GREEN + str("Type 1 of your Temtem (or entrer if no Temtem) : ") + C_RESET,
		C_GREEN + str("Type 2 of your Temtem (or entrer if empty) : ") + C_RESET,
		C_CYAN + str("Type 1 du Temtem opposing : ") + C_RESET,
		C_CYAN + str("Type 2 du Temtem opposing (or entrer if empty) : ") + C_RESET };

	for (int i = 0; i < 4;)
	{
		std::cout << prompts[i];
		std::getline(std::cin, types[i].get());
		std::transform(types[i].get().begin(), types[i].get().end(), types[i].get().begin(), ::tolower);
		if (!i && types[i].get().empty())
			i += 2;
		else if (!((!(i % 2) && table.getType(types[i].get()))
			|| ((i % 2) && !types[i].get().empty() && table.getType(types[i].get()))
			|| ((i % 2) && types[i].get().empty())))
			std::cout << C_RED << "Invalid type ! Try again.\n" << C_RESET;
		else
			i++;
	}
}

void getTemTemResults(refwrapTemtem types[2], TemtemTable &table)
{
    str prompts[2] = {
        C_GREEN + str("Enter your Temtem (or nothing if you want the full list) : ") + C_RESET,
        C_CYAN + str("Enter the opposing Temtem  : ") + C_RESET
    };

    for (int i = 0; i < 2; )
    {
        str temtemName;
        std::cout << prompts[i];
        std::getline(std::cin, temtemName);
        temtemCapital(temtemName);

        const Temtem* t = table.getTemTem(temtemName);
        if ((i == 1 && temtemName.empty()) || (!temtemName.empty() && !t))
            std::cout << C_RED << "Invalid Temtem ! Try again.\n" << C_RESET;
        else
        {
            types[i].get() = *t;
            i++;
        }
    }
}

void AssignTemTem(const Temtem &temtem, str &type1, str &type2)
{
	if (!temtem.types.empty())
	{
		type1 = temtem.types[0];
		type2 = (temtem.types.size() > 1) ? temtem.types[1] : "";
	}
	else
		type1 = type2 = "";
}


str get_input(const str &message)
{
	std::cout << message;
	str choice;
	std::getline(std::cin, choice);
	std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
	return choice;
}

void	temtemNbCheck(const TemtemTable &temtemTable)
{
	int i = 0;
	const std::vector<Temtem> &Table = temtemTable.getTable();
	for (std::vector<Temtem>::const_iterator it = Table.begin(); it != Table.end(); ++it)
	{
		Temtem temtem = *it;
		if (temtem.number != i++ && temtem.number != -1)
		{
			std::cout << "missing number =" << i << std::endl;
			break;
		}
		if (it + 1 == Table.end())
			std::cout << "Temtem nb check ok" << std::endl;
	}
}