#include"DefensiveTank.h"
#include"Utils.h"

// Special Action of the Defensive Tank, defending all damage
void DefensiveTank::Shield(std::vector<std::string> &sprite, const bool inverse)
{
	shield = -2;
	if (inverse)
	{	ReadLines(resPath+"Tanks/Attacks/ISShield.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/SShield.dat", sprite);
	}
}
// AI function for choosing actions
void DefensiveTank::TankAI(std::vector<std::string>&sprite)
{
	int choice = rand() % 100 + 1;
	
	if (hp < maxhp / 2 && choice < 80 && medikits != 0)
	{	this->Heal(sprite, 1);
	}
	else if (choice < 50 && fire > 4)
	{	this->Fix(sprite, 1);
	}
	else if (choice < 20)
	{	this->GenerateDamage(sprite, 1);
	}
	else if (choice < 40)
	{	this->GenerateShieldDamage(sprite, 1);
	}
	else if (choice < 60)
	{	this->GenerateDamageOverTime(sprite, 1);
	}
	else
	{	this->Shield(sprite, 1);
	}
}