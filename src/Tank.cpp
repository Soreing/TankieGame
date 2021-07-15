#include"Tank.h"
#include"Utils.h"

Tank::Tank(const std::string path)
	: fire(0), shield(0), dmg(0), dot(0), sdmg(0), immune(0), alive(true)
{
	std::ifstream inFile(resPath+path);
	inFile >> name >> maxhp >> atk >> def >> evade >> crit >> medikits >> points >> special >> specialName >> artFolder;
	inFile.close();

	ReadLines(resPath+"Data/BaseActions.dat", actions);

	hp = maxhp;
}
// A function that sets the health to 0 and retreats
void Tank::Surrender(std::vector<std::string>& sprite)
{
	hp = 0;
	alive = false;
	ReadLines(resPath+"Tanks/Attacks/Nothing.dat", sprite);
}
// Setting the shield to active for the calculations
void Tank::Shield(std::vector<std::string> &sprite, const bool inverse = true)
{
	shield = 1;
	if (inverse)
	{	ReadLines(resPath+"Tanks/Attacks/IShield.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/Shield.dat", sprite);
	}
}
// Removing all Fire damage and protecting for 3 turns
void Tank::Fix(std::vector<std::string> &sprite, const bool inverse = true)
{
	fire = 0, immune = 3;
	if (inverse)
	{	ReadLines(resPath+"Tanks/Attacks/IFix.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/Fix.dat", sprite);
	}
}
// Healing 25 life and removing 1 medikit. No overhealing
void Tank::Heal(std::vector<std::string> &sprite, const bool inverse = true)
{
	medikits--;
	hp = hp + 25;

	if (hp > maxhp)
	{	hp = maxhp;
	}
	
	if (inverse)
	{	ReadLines(resPath+"Tanks/Attacks/IHeal.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/Heal.dat", sprite);
	}
}
// Generating a random normal damage (dmg)
void Tank::GenerateDamage(std::vector<std::string> &sprite, const bool inverse = true)
{
	dmg = ((rand() % 10) + atk)*(1 + ((rand() % 100 + 1)<crit));

	if (inverse)
	{	ReadLines(resPath+"Tanks/Attacks/IAttack.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/Attack.dat", sprite);
	}
}
// Generating a random shield damage (sdmg)
void Tank::GenerateShieldDamage(std::vector<std::string> &sprite, const bool inverse = true)
{
	sdmg = ((rand() % 10) + atk)*(1 + ((rand() % 100 + 1)<crit));

	if (inverse)
	{	ReadLines(resPath+"Tanks/Attacks/IShieldAttack.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/ShieldAttack.dat", sprite);
	}
}
// Generating fire damage, damage over time (dot)
void Tank::GenerateDamageOverTime(std::vector<std::string> &sprite, const bool inverse = true)
{
	dot = (rand() % 3 + 1)*(1 + ((rand() % 100 + 1)<crit));
	
	if (inverse)
	{	ReadLines(resPath+"Tanks/Attacks/IFlameThrower.dat", sprite);
	}
	else
	{	ReadLines(resPath+"Tanks/Attacks/FlameThrower.dat", sprite);
	}
}
// Evaluating incoming damage and adjusting the health
std::string Tank::EvaluateHP(Tank &other, const std::string str)
{
	int received = (int) ((other.dmg / (1 + shield))*(((rand() % 100) + 1)>evade) + (other.sdmg * (0.5 + shield))*(((rand() % 100) + 1)>evade));
	int defended = (rand() % 5) + def;
	int damage = received - defended;
	
	if (damage <0)
	{	damage = 0;
	}

	if (immune == 0)
	{
		if (shield != 0)
		{	fire += (int)(other.dot / 0.5)*((rand() % 100 + 1)>evade);
		}
		else
		{	fire += other.dot*((rand() % 100 + 1) > evade);
		}
	}
	else
	{	immune--;
	}

	hp -= (damage + fire);

	if (hp <= 0)
	{	hp = 0;
		alive = false;
	}

	other.dmg = 0, other.dot = 0, other.sdmg = 0, shield = 0;
	
	std::string message = (str + " suffered " + std::to_string(damage + fire) + " Damage!");
	for (int i = message.length(); i < 29; i++) 
	{	message += ' ';
	}
	
	return (message +'\n');
}
