#include "Temtem.hpp"

struct Temtem {
	int number;
	str name;
	vectstr types;
	int hp;
	int sta;
	int spd;
	int atk;
	int def_;
	int spatk;
	int spdef;

	Temtem(int number = -1, str name = "", vectstr types = {}, int hp = -1, int sta = -1,
			int spd = -1, int atk = - 1, int def_ = -1, int spatk = -1, int spdef = -1) 
	: number(number), name(name), types(types), hp(hp), sta(sta), spd(spd), atk(atk), def_(def_), spatk(spatk), spdef(spdef) {};
};

using refwrapTemtem = std::reference_wrapper<Temtem>;

#define TEMTEM_STRING C_YELLOW "TemTem              DMG without STAB   DMG with STAB    description\n" C_RESET

class TemtemTable : public TypesTable
{
private:
	std::vector<Temtem> temtemTable;
public:
	TemtemTable();
	~TemtemTable();

	void printTemtem(const str& name);
	Temtem* getTemTem(const str& name);
	const std::vector<Temtem> &getTable(void) const;
	void	getYourTemtemResults(const Temtem &t1, const Temtem &t2);
	void	TemtemToAttack(const Temtem &t1, const Temtem &t2);
};

//utils
void	temtemCapital(str &name);
void	temtemNbCheck(const TemtemTable &temtemTable);
void	AssignTemTem(const Temtem &temtem, str &type1, str &type2);
void	getTemTemResults(refwrapTemtem types[2], TemtemTable &table);