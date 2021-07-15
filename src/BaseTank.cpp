#include"BaseTank.h"
#include"Utils.h"

// AI function for choosing actions
void BaseTank::TankAI(std::vector<std::string>&sprite)
{
	int choice = rand() % 100 + 1;

	if (hp < maxhp / 2 && choice < 80 && medikits != 0)
	{	this->Heal(sprite, 1);
	}
	else if (choice < 50 && fire > 4)
	{	this->Fix(sprite, 1);
	}
	else if (choice < 25)
	{	this->GenerateDamage(sprite, 1);
	}
	else if (choice < 50)
	{	this->GenerateShieldDamage(sprite, 1);
	}
	else if (choice < 75)
	{	this->GenerateDamageOverTime(sprite, 1);
	}
	else
	{	this->Shield(sprite, 1);
	}
}