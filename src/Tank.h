#ifndef TANK_H
#define TANK_H

#include<string>
#include<vector>
#include "Utils.h"

class Tank
{
protected:
	bool alive, special;
	int maxhp, atk, def, evade, crit, medikits, points;
	int hp, fire, shield, dmg, dot, sdmg, immune;
	std::string artFolder, name, specialName;
	std::vector<std::string> actions;
public:
	Tank(const std::string);
	inline bool isAlive() { return alive; }
	inline bool isSpecial() { return special; }
	inline int getMaxHP() { return maxhp; }
	inline int getHP() { return hp; }
	inline int getMedikits() { return medikits; }
	inline int getPoints() { return points; }
	inline int getFire() { return fire; }
	inline int getDMG() { return dmg; }
	inline int getDOT() { return dot; }
	inline int getSDMG() { return sdmg; }
	inline void setDMG(const int val) { dmg = val; }
	inline void setDOT(const int val) { dot = val; }
	inline void setSDMG(const int val) { sdmg = val; }
	inline std::vector<std::string> getActions() {return actions;}
	inline std::string getArtFolder() { return resPath+artFolder; }
	inline std::string getName() { return name; }
	inline std::string getSpecialName() { return specialName; }
	virtual void Surrender(std::vector<std::string>&);
	virtual void Fix(std::vector<std::string>&, const bool);
	virtual void Heal(std::vector<std::string>&, const bool);
	virtual void GenerateDamage(std::vector<std::string>&, const bool);
	virtual void GenerateShieldDamage(std::vector<std::string>&,const bool);
	virtual void GenerateDamageOverTime(std::vector<std::string>&, const bool);
	virtual void Shield(std::vector<std::string>&, const bool);
	virtual void DoSpecialMove(std::vector<std::string>&,const bool) {}
	virtual void TankAI(std::vector<std::string>&) {}
	virtual std::string EvaluateHP(Tank&, const std::string);
};
#endif