#pragma once

#include <iostream>
#include <string>
#include <csignal>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include <cmath>
#include <cwchar>
#include <locale>

#define C_RED			"\033[1;31m"
#define C_BLUE			"\033[34m"
#define C_CYAN			"\033[36m"
#define C_GRAY			"\033[1;90m"
#define C_RESET			"\033[0m"
#define C_GREEN			"\033[1;32m"
#define C_WHITE			"\033[1;37m"
#define C_YELLOW		"\033[33m"
#define C_ORANGE		"\033[38;5;202m"
#define C_LIGHT_PURPLE	"\033[1;95m"
#define C_YELLOW_BRIGHT	"\033[38;5;226m"

#define FEU			"Feu"
#define EAU			"Eau"
#define FEE			"Fée"
#define SOL			"Sol"
#define VOL			"Vol"
#define PSY			"Psy"
#define GLACE		"Glace"
#define ROCHE		"Roche"
#define ACIER		"Acier"
#define PLANTE		"Plante"
#define COMBAT		"Combat"
#define POISON		"Poison"
#define NORMAL		"Normal"
#define DRAGON		"Dragon"
#define INSECTE		"Insecte"
#define SPECTRE		"Spectre"
#define TENEBRES	"Ténèbres"
#define ELECTRIQUE	"Électrique"
#define STATS_STRING C_YELLOW "Type         DGT sans STAB   DGT avec STAB     description\n" C_RESET

using str = std::string;
using vectstr = std::vector<str>;
using refwrapstr = std::reference_wrapper<str>;
using refwrapbool = std::reference_wrapper<bool>;
using refwrapconststr = std::reference_wrapper<const str>;

extern volatile std::sig_atomic_t g_interrupt;

typedef struct s_Type
{
	str		name;
	vectstr	super_effective;
	vectstr	normal;
	vectstr	less_effective;
	vectstr	ineffective;

	s_Type(str n, vectstr sup = {}, vectstr nor = {}, vectstr less = {}, vectstr ine = {});
} Type;

class TypesTable
{
private:
	std::vector<Type> typesTable;

	float		getMultiplierOne(const Type& atk, const str& defName) const;
	void		getYourDefResults1Type(const str def1, const str def2, const str atk);
	float		GetMultiplier(const str& atk, const str& def1, const str& def2, str& res) const;
	float		GetMultiplier(const str& atk1, const str& atk2, const str& def1, const str& def2) const;
public:
	TypesTable();
	~TypesTable();

	const Type*	getType(const str& name) const;
	void		getYourAtkResults(const str atk1, const str atk2, const str def1, const str def2);
	void		getYourDefResults(const str atk1, const str atk2, const str def1, const str def2);
	void		TypeToAttack(const str& atk1, const str& def1, const str& atk2 = "", const str& def2 = "") const;
	void		TypeToDefend(const str& atk1, const str& def1, const str& atk2 = "", const str& def2 = "") const;
};

//utils
void			clear();
str				normalize(str s);
str				GetColor(float val);
str				stripAnsi(const str& s);
int				utf8Size(const str& str);
void			handle_sigint(int signal);
void			printTitle(const str title);
int				displayWidth(const str& str);
void			printTypeAttack(float mult, const str &name);
void			GetColorAtk(float mult, str &color, str &multStr, str &msg);
str				getMultStab(const float &resist, str &multStr, const str mode);
void			printTypeDefense(float resist, const str &name, const str& atk1, const str& atk2, bool res1);
void			GetColorDef(float resist, str &color, str &multStr, str &msg, const str& atk1, const str& atk2, bool res1);
