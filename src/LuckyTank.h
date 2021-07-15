#ifndef LUCKYTANK_H
#define LUCKYTANK_H

#include"Tank.h"

class LuckyTank : public Tank
{
public:
	inline LuckyTank() : Tank("Tanks/LuckyTank/Stats.dat") {actions.insert(actions.begin(), specialName);}
	virtual void DoSpecialMove(std::vector<std::string>&,const bool);
	virtual void TankAI(std::vector<std::string>&);
};

#endif