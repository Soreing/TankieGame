#include"LuckyTank.h"
#include"Utils.h"
// Special Action ofthe Lucky Tank, defeating an enemy in 1 hit
void LuckyTank::DoSpecialMove(std::vector<std::string> &sprite, const bool inverse)
{
	if ((rand() % 100) == 0)
	{	dmg = 9001;
	}
	
	if (inverse)
	{	ReadLines(resPath+"Tanks/Attacks/IInstakill.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/Instakill.dat", sprite);
	}
}
// AI function for choosing actions
void LuckyTank::TankAI(std::vector<std::string>&sprite)
{
	int choice = rand() % 100 + 1;
	
	if (hp < maxhp / 2 && choice < 80 && medikits != 0)
	{	this->Heal(sprite, 1);
	}
	else if (choice < 50 && fire > 4)
	{	this->Fix(sprite, 1);
	}
	else if (choice < 23)
	{	this->GenerateDamage(sprite, 1);
	}
	else if (choice < 46)
	{	this->GenerateShieldDamage(sprite, 1);
	}
	else if (choice < 69)
	{	this->GenerateDamageOverTime(sprite, 1);
	}
	else if (choice < 92)
	{	this->Shield(sprite, 1);
	}
	else
	{	this->DoSpecialMove(sprite, 1);
	}
}