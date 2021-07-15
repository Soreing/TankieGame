#ifndef DEVTANK_H
#define DEVTANK_H

#include"Tank.h"

class DevTank : public Tank
{
private:
	bool isDev, isGod;
public:
	DevTank(const bool);
	virtual void DoSpecialMove(std::vector<std::string>&,const bool);
};

#endif