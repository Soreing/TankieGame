#include"OffensiveTank.h"
#include"Utils.h"
// Special Action of the Offensive Tank, self destructing and dealing huge damage
void OffensiveTank::DoSpecialMove(std::vector<std::string> &sprite,const bool inverse)
{
	alive = false;
	dmg   = hp;
	hp    = 0;

	if (inverse)
	{	ReadLines(resPath+"Tanks/Attacks/IExplode.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/Explode.dat", sprite);
	}
}
// AI function for choosing actions
void OffensiveTank::TankAI(std::vector<std::string>&sprite)
{
	int choice = rand() % 100 + 1;
	
	if (hp < maxhp / 2 && choice < 80 && medikits != 0)
	{	this->Heal(sprite, 1);
	}
	else if (hp < maxhp / 2)
	{	this->DoSpecialMove(sprite, 1);
	}
	else if (choice < 50 && fire > 4)
	{	this->Fix(sprite, 1);
	}
	else if (choice < 30)
	{	this->GenerateDamage(sprite, 1);
	}
	else if (choice < 60)
	{	this->GenerateShieldDamage(sprite, 1);
	}
	else if (choice < 90)
	{	this->GenerateDamageOverTime(sprite, 1);
	}
	else
	{	this->Shield(sprite, 1);
	}
}