#ifndef DEFENSIVETANK_H
#define DEFENSIVETANK_H

#include"Tank.h"

class DefensiveTank : public Tank
{
public:
	inline DefensiveTank() : Tank("Tanks/DefensiveTank/Stats.dat") {}
	virtual void Shield(std::vector<std::string> &,const bool);
	virtual void TankAI(std::vector<std::string>&);
};

#endif