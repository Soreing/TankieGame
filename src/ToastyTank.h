#ifndef TOASTYTANK_H
#define TOASTYTANK_H

#include"Tank.h"

class ToastyTank : public Tank
{
public:
	inline ToastyTank() : Tank("Tanks/ToastyTank/Stats.dat")
	{	actions = { "Flammenwerfer!","Flammenwerfer!","Flammenwerfer!","Flammenwerfer!","Heal","Fix","Surrender" };
	}

	virtual void GenerateDamage(std::vector<std::string>&, const bool);
	virtual void GenerateShieldDamage(std::vector<std::string>&, const bool);
	virtual void GenerateDamageOverTime(std::vector<std::string>&, const bool);
	virtual void Shield(std::vector<std::string>&, const bool);
	virtual std::string EvaluateHP(Tank&, const std::string);
};

#endif