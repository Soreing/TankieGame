#ifndef BASETANK_H
#define BASETANK_H

#include"Tank.h"

class BaseTank : public Tank
{
public:
	inline BaseTank() : Tank("Tanks/BaseTank/Stats.dat") {}
	virtual void TankAI(std::vector<std::string>&);
};

#endif