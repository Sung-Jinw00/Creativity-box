#include "pokémon.hpp"

s_Type::s_Type(str n, vectstr sup, vectstr nor, vectstr less, vectstr ine)
		: name(n), super_effective(sup), normal(nor), less_effective(less), ineffective(ine)
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
	float mult_stab = !resist ? 0.0f : std::atoi(multStr.substr(2).c_str());
	if (mode == "atk")
		mult_stab = (resist < 1.0f) ? mult_stab / 1.5f : mult_stab * 1.5f;
	else
		mult_stab = (resist > 1.0f) ? mult_stab / 1.5f : mult_stab * 1.5f;
	std::ostringstream oss;
	if (std::fmod(mult_stab, static_cast<int>(mult_stab)) == 0.0f)
		oss << static_cast<int>(mult_stab);
	else
		oss << std::fixed << std::setprecision(1) << mult_stab;
	str multStabStr = oss.str();
	return multStabStr;
}

str GetColor(float val)
{
	if		(val == 4)		return C_LIGHT_PURPLE;
	else if	(val == 2)		return C_GREEN;
	else if	(val == 1)		return C_YELLOW_BRIGHT;
	else if	(val == 0.5f)	return C_ORANGE;
	else if	(val == 0.25f)	return C_RED;
	else					return C_GRAY;
}

void	GetColorAtk(float mult, str &color, str &multStr, str &msg)
{
	if		(mult == 0.0f)	{ color = C_GRAY;			multStr = " nullifié";	msg = "(tombé dans l'oubli)"; }
	else if (mult >= 4.0f)	{ color = C_LIGHT_PURPLE;	multStr = " x4";		msg = "(extension du territoire)"; }
	else if (mult >= 2.0f)	{ color = C_GREEN;			multStr = " x2";		msg = "(territoire simple)"; }
	else if (mult == 1.0f)	{ color = C_YELLOW_BRIGHT;	multStr = " x1";		msg = "(neutre)"; }
	else if (mult >= 0.5f)	{ color = C_ORANGE;			multStr = " /2";		msg = "(granite marin)"; }
	else					{ color = C_RED;			multStr = " /4";		msg = "(Griffith avant éclipse)"; }
}

void	GetColorDef(float resist, str &color, str &multStr, str &msg, const str& atk1, const str& atk2, bool res1)
{
	if		(resist == 0.0f)	{ color = C_GRAY;			multStr = " nullifie";	msg = (atk2 != "" ? (" (infinite void sur " + (!res1 ? atk1 : atk2) + ")") : " (infinite void)");}
	else if (resist == 0.25f)	{ color = C_RED;			multStr = " x4";		msg = " (se fait démolir)";}
	else if (resist == 0.5f)	{ color = C_ORANGE;			multStr = " x2";		msg = (atk2 != "" ? (" (se fait démolir par " + (!res1 ? atk1 : atk2) + ")") : " (se fait démolir)"); }
	else if (resist == 1.0f)	{ color = C_YELLOW_BRIGHT;	multStr = " x1";		msg = " (neutre)"; }
	else if (resist == 2.0f)	{ color = C_GREEN;			multStr = " /2";		msg = (atk2 != "" ? (" (Résiste à " + (!res1 ? atk1 : atk2) + ")") : " (résiste)"); }
	else						{ color = C_LIGHT_PURPLE;	multStr = " /4";		msg = " (Résiste aux deux)";}
}

void printTypeAttack(float mult, const str &name)
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
	int center1 = (utf8Size(multStr) % 2) ? (utf8Size(multStr) / 2) : (utf8Size(multStr) / 2) - 1;
	int center2 = (utf8Size(multStabStr) % 2) ? (utf8Size(multStabStr) / 2) : (utf8Size(multStabStr) / 2) - 1;
	int center3 = (multStabStr == "0") ? center2 - center1 - 1 : center2 - center1;
	int diff = displayWidth(name) - name.size();
	std::cout << color << std::setw(18 - center1 - diff) << std::left << name
		<< std::setw(17 - center3) << multStr		// multiplicateur normal
		<< std::setw(12 + center2) << multStabStr << msg << C_RESET << "\n"; // multiplicateur avec STAB
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

str normalize(str s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);

	if (s == "normal") return NORMAL;
	if (s == "feu") return FEU;
	if (s == "eau") return EAU;
	if (s == "plante") return PLANTE;
	if (s == "electrique" || s == "électrique") return ELECTRIQUE;
	if (s == "glace") return GLACE;
	if (s == "combat") return COMBAT;
	if (s == "poison") return POISON;
	if (s == "sol") return SOL;
	if (s == "vol") return VOL;
	if (s == "psy") return PSY;
	if (s == "insecte") return INSECTE;
	if (s == "roche") return ROCHE;
	if (s == "spectre") return SPECTRE;
	if (s == "dragon") return DRAGON;
	if (s == "acier") return ACIER;
	if (s == "fee" || s == "fée") return FEE;
	if (s == "tenebres" || s == "ténèbres" || s == "tenèbres" || s == "ténèbre")
		return TENEBRES;
	return s;
}

void	clear()
{
	#ifdef _WIN32
		system("CLS");
	#else
		system("clear");
	#endif
}

volatile std::sig_atomic_t g_interrupt = 0;

void handle_sigint(int signal)
{
	(void)signal;
    g_interrupt = 1;
}