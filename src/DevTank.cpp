#include"DevTank.h"
#include"Utils.h"

DevTank::DevTank(const bool val) : Tank("Tanks/DevTank/Stats.dat"), isDev(val), isGod(0)
{
	actions.insert(actions.begin(), specialName);

	if (!isDev)
	{	hp = 50;
		def = 0;
		atk = 0;
		crit = 0;
		evade = 0;
		points = 0;
		maxhp = 50;
	}
}

// Special Action of the Dev Tank making it invincible or suer weak
void DevTank::DoSpecialMove(std::vector<std::string> &sprite, const bool invert)
{
	if (isDev)
	{	hp = 999, def = 99, atk = 99, crit = 100, evade = 100, maxhp = 999;
	}
	else
	{	hp = 25, def = 0, atk = 0, crit = 0, evade = 0, maxhp = 25;
	}
	
	if (invert)
	{	ReadLines(resPath+"Tanks/Attacks/IGodMode.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/GodMode.dat", sprite);
	}
}

