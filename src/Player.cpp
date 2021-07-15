#include"Player.h"
#include"Utils.h"

Player::Player(const std::string path) :
	dev(false), toasty(false)
{
	std::ifstream inFile(path);
	inFile >> name >> score >> wins >> defeats >> ties >> multi >> tanks[0] >> tanks[1] >> tanks[2] >> tanks[3] >> tanks[4]>>tanks[5];
	inFile.close();
}
// A function that returns the most used tank for the statistics
std::string Player::getTank()
{
	std::string tankNames[6] = { "The_Standard", "The_Lucky", "The_Turtle","The_Kamikaze","The_Developer", "The_Toasty" };
	int index = 0;
	
	for (int i = 0; i < 6; i++)
	{	if (tanks[i]>tanks[index])
		{	index = i;
		}
	}

	return tankNames[index];
}
