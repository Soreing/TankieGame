#ifndef OFFENSIVETANK_H
#define OFFENSIVETANK_H

#include"Tank.h"

class OffensiveTank : public Tank
{
public:
	inline OffensiveTank() : Tank("Tanks/OffensiveTank/Stats.dat") {actions.insert(actions.begin(), specialName);}
	virtual void DoSpecialMove(std::vector<std::string> &container,const bool);
	virtual void TankAI(std::vector<std::string>&);
};

#endif