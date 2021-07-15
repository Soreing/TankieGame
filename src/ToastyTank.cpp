#include"ToastyTank.h"
#include"Utils.h"

//Overwritten parent functions to make all actions use the flame thrower
void ToastyTank::Shield(std::vector<std::string> &sprite, const bool inverse = true)
{
	dot = (rand() % 5 + 1)*(1 + ((rand() % 100 + 1)<crit));
	
	if (inverse)
	{	ReadLines(resPath+"Tanks/Attacks/IFlammenwerfer.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/Flammenwerfer.dat", sprite);
	}
}
void ToastyTank::GenerateDamage(std::vector<std::string> &sprite, const bool inverse = true)
{
	dot = (rand() % 5 + 1)*(1 + ((rand() % 100 + 1)<crit));
	
	if (inverse)
	{	ReadLines(resPath+"Tanks/Attacks/IFlammenwerfer.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/Flammenwerfer.dat", sprite);
	}
}
void ToastyTank::GenerateShieldDamage(std::vector<std::string> &sprite, const bool inverse = true)
{
	dot = (rand() % 5 + 1)*(1 + ((rand() % 100 + 1)<crit));
	
	if (inverse)
	{	ReadLines(resPath+"Tanks/Attacks/IFlammenwerfer.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/Flammenwerfer.dat", sprite);
	}
}
void ToastyTank::GenerateDamageOverTime(std::vector<std::string> &sprite, const bool inverse = true)
{
	dot = (rand() % 5 + 1)*(1 + ((rand() % 100 + 1)<crit));
	
	if (inverse)
	{	ReadLines(resPath+"Tanks/Attacks/IFlammenwerfer.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/Flammenwerfer.dat", sprite);
	}
}
//An overwritten parent function that makes this tank immune to fire damage.
std::string ToastyTank::EvaluateHP(Tank &other, const std::string str)
{
	int received = (int)((other.getDMG() / (1 + shield))*(((rand() % 100) + 1)>evade) + (other.getSDMG() * (0.5 + shield))*(((rand() % 100) + 1)>evade));
	int defended = (rand() % 5) + def;
	int damage = received - defended;
	
	if (damage <0)
	{	damage = 0;
	}

	hp -= (damage);
	
	if (hp <= 0)
	{	hp = 0;
		alive = false;
	}

	other.setDMG(0), other.setDOT(0), other.setSDMG(0), shield = 0;
	
	std::string message = (str + " suffered " + std::to_string(damage + fire) + " Damage!");
	for (int i = message.length(); i < 29; i++)
	{	message += ' ';
	}
	
	return (message + '\n');
}