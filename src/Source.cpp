#include"Utils.h"

#include"Tank.h"
#include"Player.h"
#include"BaseTank.h"
#include"LuckyTank.h"
#include"OffensiveTank.h"
#include"DefensiveTank.h"
#include"DevTank.h"
#include"ToastyTank.h"

#define MENUOFFSET 30

#define LEFT  75
#define RIGHT 77
#define UP    72
#define DOWN  80
#define ENTER 13
#define ESC   27
#define BCKSP 8

const char inputChart[16] = {'1', '2', '3', '4', '5', '6', '7', '8', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K'};

// Display credits information
void Credits()
{
	ShowWholeFile(resPath+"Data/credits.dat"); 
	
	// Wait for input and return	
	_getch(); 
	emptyScreen();
	return;
}

// Displaying files that help understand the game with menu navigation left-right
void Help()
{
	unsigned short active = 0;
	char buttonPress;

	for (;;)
	{
		cursorHome();
		switch (active)
		{	case 0: ShowWholeFile(resPath+"Data/Help1.dat"); break;
			case 1: ShowWholeFile(resPath+"Data/Help2.dat"); break;
			case 2: ShowWholeFile(resPath+"Data/Help3.dat"); break;
			case 3: ShowWholeFile(resPath+"Data/Help4.dat"); break;
		}

		buttonPress = _getch();
		if (buttonPress == 0 || buttonPress == 0xE0)
		{	buttonPress = _getch();
		}

		if ((buttonPress == LEFT) && active > 0)
		{	active--;
		}
		else if ((buttonPress == RIGHT) && active < 3)
		{	active++;
		}
		else if (buttonPress == ESC)
		{	break;
		}
	}

	emptyScreen();
	return;
}

// Takes a profile name from the user and saves the profile into a file with the same name.
void SaveProfile(Player &player)
{
	bool unknown = true;
	std::string saveName;
	std::vector<std::string> availables;
	std::ofstream outFile;

	// Load all the existing saved profiles
	ReadLines(resPath+"Data/Profiles.dat", availables);
	PrintHeader(player, resPath+"Data/SaveProfileInstructions.dat", resPath+"Data/GameHeader.dat", 1);

	// Get the profile name from the user
	std::cout << std::setw(MENUOFFSET) << std::right << "Profile Name: ";
	std::cin >> saveName;

	// Find if there already exists a profile with that name
	for (auto i : availables)
	{	if (i == saveName)
		{	unknown = false;
		}
	}

	if (unknown)
	{
		player.setName(saveName);
		PrintProfile(player, resPath+"Profiles/" + saveName + ".dat");

		// Add new profile to list of profiles
		outFile.open(resPath+"Data/Profiles.dat", std::ios::app);
		outFile << saveName << '\n';
		outFile.close();
	}
	else
	{
		emptyScreen();
		PrintHeader(player, "Resources/NoInstructions.dat", "Resources/GameHeader.dat", 1);

		std::cout << std::setw(MENUOFFSET / 2) << ' ' << "A profile already exists under this name.\n" << std::setw(MENUOFFSET / 2) << ' ' << " Overrite it? (Y/N)";

		if (YesNoMenu())
		{	player.setName(saveName);
			PrintProfile(player, resPath+"Profiles/" + saveName + ".dat");
		}
	}

	emptyScreen();
	return;
}

// A function that handles loading the profile
// Using menu navigation up-down, the function loads the eisting
// profile into memory. The list of profiles is loaded from a file.
// The function can also delete profiles
// Warns the user about permanently deleting and loading onto unsaved profiles
void LoadProfile(Player &player)
{
	unsigned short active = 0;
	char buttonPress;
	std::vector<std::string> availables;

	// Load all the existing saved profiles
	ReadLines(resPath+"Data/Profiles.dat", availables);

	for (;;)
	{
		PrintHeader(player, resPath+"Data/LoadProfileInstructions.dat", resPath+"Data/GameHeader.dat", 1);
		std::cout << std::setw(MENUOFFSET) << ' ' << "Available Profiles: \n\n";

		// Print all the profiles in a menu
		for (unsigned short i = 0; i < availables.size(); i++)
		{	PrintOption(availables[i], active, i, MENUOFFSET);
			std::cout << '\n';
		}

		buttonPress = _getch();
		if (buttonPress == 0 || buttonPress == 0xE0)
		{	buttonPress = _getch();
		}

		if ((buttonPress == UP) && active > 0)
		{	active--;
		}
		else if ((buttonPress == DOWN) && active < availables.size() - 1)
		{	active++;
		}
		else if (buttonPress == ESC)
		{	break;
		}
		// Load Profile selected
		else if (buttonPress == ENTER)
		{
			emptyScreen();
			PrintHeader(player, resPath+"Data/NoInstructions.dat", resPath+"Data/GameHeader.dat", 1);
			std::cout << std::setw(MENUOFFSET / 2) << ' ' << "All unsaved progress will be lost.\n" << std::setw(MENUOFFSET / 2) << ' ' << "Continue? (Y/N)";

			if (YesNoMenu())
			{
				if (availables.size() == 0 || !FileExists(resPath+"Profiles/" + availables[active] + ".dat"))
				{	player = Player(resPath+"Profiles/Default.dat");
				}
				else
				{	player = Player(resPath+"Profiles/" + availables[active] + ".dat");
				}

				break;
			}
		}
		// Delete profile selected
		else if (buttonPress == BCKSP && active > 0)
		{
			emptyScreen();
			PrintHeader(player, resPath+"Data/NoInstructions.dat", resPath+"Data/GameHeader.dat", 1);
			std::cout << std::setw(MENUOFFSET / 2) << ' ' << "The data will be permanently lost.\n" << std::setw(MENUOFFSET / 2) << ' ' << " Are you sure? (Y/N)";

			if (YesNoMenu())
			{	availables.erase(availables.begin() + active);
				active = 0;

				std::ofstream profileFile(resPath+"Data/Profiles.dat");
				
				for(int i=0; i< (int)availables.size(); i++)
				{	profileFile << availables[i] << "\n";
				}

				profileFile.close();
			}
		}
	}

	emptyScreen();
	return;
}

// Prints out the statistical information stored in the player object with some formatting
void ProfileStatistics(Player player)
{
	std::vector<std::string> Statistics;
	Statistics.push_back("Profile Name: " + player.getName());
	Statistics.push_back("Favorite Tank: " + player.getTank());
	Statistics.push_back("Score: " + std::to_string(player.getScore()) + '\n');
	Statistics.push_back("SinglePlayer Wins: " + std::to_string(player.getWins()));
	Statistics.push_back("SinglePlayer Defeats: " + std::to_string(player.getDefeats()));
	Statistics.push_back("SinglePlayer Ties: " + std::to_string(player.getTies()) + '\n');
	Statistics.push_back("Multiplayer Games: " + std::to_string(player.getMulti()));

	emptyScreen();
	PrintHeader(player, resPath+"Data/NoInstructons.dat", resPath+"Data/StatisticsHeader.dat", 0);

	// Print all statistics information centered on the screen
	for (auto i : Statistics)
	{	std::cout << std::setw((80 - i.length()) / 2 + i.length()) << std::right << i << '\n';
	}

	// Wait for input and return	
	_getch();
	emptyScreen();
	return;
}

// Allows the player to select a tank to play with.
// Uses menu navigation left-right
Tank* TankSelect(Player &player, bool &abort, const bool isMulti, const std::string header)
{
	unsigned short active = 0;
	char buttonPress;
	Tank* selection = NULL;

	std::string upassword, password = "toasty";
	
	std::vector<int> TankRequirement = { 0, 50, 100,100,0,0 };
	std::vector<std::string> TankInfoPath = { 
		resPath + "Tanks/BaseTank/Info.dat", 
		resPath + "Tanks/LuckyTank/Info.dat",
		resPath + "Tanks/DefensiveTank/Info.dat",
		resPath + "Tanks/OffensiveTank/Info.dat",
		resPath + "Tanks/DevTank/Info.dat", 
		resPath + "Tanks/ToastyTank/Info.dat" 
	};
	
	for (;;)
	{
		PrintHeader(player, resPath+"Data/TankSelectInstructions.dat", header, 1);

		// Print whether the tank is unlocked
		if (player.getScore() >= TankRequirement[active])
		{	std::cout << "       UNLOCKED!        \n";
		}
		else
		{	std::cout << "       " << TankRequirement[active] << " SCORE NEEDED!   \n";
		}

		// Show information about the tank
		ShowWholeFile(TankInfoPath[active]);

		buttonPress = _getch();
		if (buttonPress == 0 || buttonPress == 0xE0)
			buttonPress = _getch();

		// Moving menu left or right
		if ((buttonPress == LEFT) && active > 0)
		{	active--;
		}
		else if ((buttonPress == RIGHT) && active < 4 + player.isToasty())
		{	active++;
		}
		else if (buttonPress == ESC)
		{	abort = true;
			break;
		}
		else if (buttonPress == ENTER && TankRequirement[active] <= player.getScore())
		{
			// Increase the amount of times the player selected this tank for statistics
			if (!isMulti)
			{	player.incrementTank(active);
			}

			// Set the appropriate tank
			switch (active)
			{	case 0: selection = new BaseTank(); break;
				case 1: selection = new LuckyTank(); break;
				case 2: selection = new DefensiveTank(); break;
				case 3: selection = new OffensiveTank(); break;
				case 4: selection = new DevTank(player.isDev()); break;
				case 5: selection = new ToastyTank(); break;
			}

			break;
		}
	}

	emptyScreen();
	return selection;
}

//Allows the computer to select a random tank.
Tank* ComputerSelect(int score)
{
	// Unlock requirements of the tanks
	std::vector<int> TankRequirement = { 0, 50, 100,100 };
	unsigned short index;
	Tank* selection = NULL;

	// Randomly pick a new tank, but re-roll if it's not unlocked
	do
	{	index = rand() % (4);
	} 	while (TankRequirement[index] > score);

	switch (index)
	{	case 0: selection = new BaseTank; break;
		case 1: selection = new LuckyTank; break;
		case 2: selection = new DefensiveTank; break;
		case 3: selection = new OffensiveTank; break;
	}

	return selection;
}

// Single player function for player vs computer game.
void SinglePlayer(Player &player)
{
	bool  abort  = false;
	short active = 0;
	short option = 0;
	char buttonPress;

	std::vector<std::string> TankImage1, TankImage2, TankShot1, TankShot2;
	std::vector<std::string> Log = { "\n","\n","\n","\n","\n" };

	Tank *Tank1 = TankSelect(player, abort, 0, resPath+"Data/P1Header.dat");
	Tank *Tank2 = ComputerSelect(player.getScore());

	// if the user quit the tank selection menu, return to the menu
	if (abort)
	{	if(Tank1 != NULL) delete Tank1;
		if(Tank2 != NULL) delete Tank2;
		return;
	}

	// Reading the graphics from file
	ReadLines(Tank1->getArtFolder() + "Image.dat", TankImage1);
	ReadLines(Tank2->getArtFolder() + "ReverseImage.dat", TankImage2);
	ReadLines(resPath+"Tanks/Attacks/Nothing.dat", TankShot1);
	ReadLines(resPath+"Tanks/Attacks/Nothing.dat", TankShot2);

	// Action options for the player
	std::vector<int> actOpts = {0,1,2,3,4,5,6};

	// Adding special attack for special tanks
	if (Tank1->isSpecial())
	{	actOpts.push_back(7);
	}

	// Game Loop
	for (;;)
	{
		// Do appropriate action if one of the tanks is defeated
		if (!Tank1->isAlive() || !Tank2->isAlive())
		{
			Log.push_back(" \n");
			Log.push_back("                             \n");
			
			if (!Tank1->isAlive() && !Tank2->isAlive())
			{	player.setTies(player.getTies() + 1);
				Log.push_back("The game is a Tie!           \n");
			}
			else if (!Tank1->isAlive())
			{	player.setDefeats(player.getDefeats() + 1);
				Log.push_back("You Lost! Shame on you      \n");
			}
			else if (!Tank2->isAlive())
			{	player.setWins(player.getWins() + 1);
				Log.push_back("Player Wins! +" + std::to_string(Tank2->getPoints()) + " Points!    \n");
				player.setScore(player.getScore() + Tank2->getPoints());
			}
		}

		// Print out the graphics
		PrintHeader(player, "NoInstructions.dat", resPath+"Data/GameHeader.dat", 0);
		std::cout << std::setw(25) << std::left << "|Name: " + player.getName() << std::setw(26) << std::right << "Name: Computer|\n";
		std::cout << std::setw(25) << std::left << "|Tank: " + Tank1->getName() << std::setw(26) << std::right << "Tank: " + Tank2->getName() + "|\n";
		std::cout << std::setw(25) << std::left << "|Health: " + std::to_string(Tank1->getHP()) + '/' + std::to_string(Tank1->getMaxHP()) << std::setw(26) << std::right << "Health: " + std::to_string(Tank2->getHP()) + '/' + std::to_string(Tank2->getMaxHP()) + "|\n";
		std::cout << std::setw(25) << std::left << "|Medikits: " + std::to_string(Tank1->getMedikits()) << std::setw(26) << std::right << "Medikits: " + std::to_string(Tank2->getMedikits()) + "|\n";
		std::cout << std::setw(25) << std::left << "|Fire: " + std::to_string(Tank1->getFire()) << std::setw(25) << std::right << "Fire: " + std::to_string(Tank2->getFire()) + "|" << "Action Log: \n";
		
		for (unsigned short i = 0; i < TankImage1.size(); i++)
		{	std::cout << TankImage1[i] << TankShot1[i] << TankShot2[i] << TankImage2[i] << Log[Log.size() - 5 + i];
		}
		std::cout << '\n';

		// If someone is defeated, end the game
		if (!Tank1->isAlive() || !Tank2->isAlive())
		{	std::cout << "Press Any Key To Continue...\n                    \n                    \n                    \n                    \n                    \n                    \n                    \n";
			
			_getch();
			emptyScreen();
			break;
		}

		// Print the available actions while the game is running 
		for (unsigned short i = 0; i < Tank1->getActions().size(); i++)
		{	PrintOption(Tank1->getActions()[i], actOpts[active], i, 0);
			std::cout << '\n';
		}

		buttonPress = _getch();
		if (buttonPress == 0 || buttonPress == 0xE0)
		{	buttonPress = _getch();
		}

		if (buttonPress == UP && active > 0)
		{	active--;
		}
		else if (buttonPress == DOWN && active < (short)actOpts.size()-1)
		{	active ++;
		}
		else if (buttonPress == ENTER)
		{
			// Clear the action graphics
			Log.push_back(" \n");
			TankShot1.clear();
			TankShot2.clear();

			option = actOpts[active] - Tank1->isSpecial();

			// Execute an action and fill the action graphics
			switch (option)
			{	case -1: Tank1->DoSpecialMove(TankShot1, 0); break;
				case 0: Tank1->GenerateDamage(TankShot1, 0); break;
				case 1: Tank1->GenerateShieldDamage(TankShot1, 0); break;
				case 2: Tank1->GenerateDamageOverTime(TankShot1, 0); break;
				case 3: Tank1->Shield(TankShot1, 0); break;
				case 4: Tank1->Heal(TankShot1, 0); break;
				case 5: Tank1->Fix(TankShot1, 0); break;
				case 6: Tank1->Surrender(TankShot1); break;
			}

			// Adjust the menu if the player is out of medkits
			if(option == 4 && Tank1->getMedikits() == 0)
			{	actOpts.erase(actOpts.end()-3);
				active--;
			}

			// Make the computer pick an action and execute it.
			Tank2->TankAI(TankShot2);

			// Evaluate the health points
			Log.push_back(Tank1->EvaluateHP(*Tank2, player.getName()));
			Log.push_back(Tank2->EvaluateHP(*Tank1, "Computer"));
		}
	}

	delete Tank1;
	delete Tank2;
}

// Translate the multiplauer user input from characters to numbers
void translateInput(char input, int &option, int &player)
{
	player = option = -1;

	for(int i=0; i<16; i++)
	{	if(input == inputChart[i])
		{	player = i/8;
			option = i%8;
		}
	}
}

// Multi player function handling the player vs player game.
void MultiPlayer(Player &player)
{
	bool abort   = false;
	bool p1Ready = false; 
	bool p2Ready = false;
	int actionsLength = 4;
	char buttonPress;

	int plNum;
	int optNum;

	std::vector<std::string> TankImage1, TankImage2, TankShot1, TankShot2, NextShot1, NextShot2;
	std::vector<std::string> Log = { "\n","\n","\n","\n","\n" };
	std::vector<std::string> Ready;

	// Player1 selecting a tank
	Tank *Tank1 = TankSelect(player, abort, 1, resPath+"Data/P1Header.dat");
	if (abort)
	{	if(Tank1 != NULL) delete Tank1;
		return;
	}

	// Player2 selecting a tank
	Tank *Tank2 = TankSelect(player, abort, 1, resPath+"Data/P2Header.dat");
	if (abort)
	{	if(Tank1 != NULL) delete Tank1;
		if(Tank2 != NULL) delete Tank2;
		return;
	}

	// Setting the maximum action length
	int t1ASize = Tank1->getActions().size();
	int t2ASize = Tank2->getActions().size();
	actionsLength = t1ASize > t2ASize ? t1ASize : t2ASize;

	// Reading the graphics from file
	ReadLines(Tank1->getArtFolder() + "Image.dat", TankImage1);
	ReadLines(Tank2->getArtFolder() + "ReverseImage.dat", TankImage2);
	ReadLines(resPath+"Tanks/Attacks/Nothing.dat", TankShot1);
	ReadLines(resPath+"Tanks/Attacks/Nothing.dat", TankShot2);
	ReadLines(resPath+"Data/Ready.dat", Ready);

	// Game Loop
	for (;;)
	{
		// Do appropriate action if one of the tanks is defeated
		if (!Tank1->isAlive() || !Tank2->isAlive())
		{
			Log.push_back(" \n");
			Log.push_back("                             \n");

			if (!Tank1->isAlive() && !Tank2->isAlive())
			{	Log.push_back("The game is a Tie!           \n");
			}
			else if (!Tank1->isAlive())
			{	Log.push_back("Player2 Wins!!               \n");
			}
			else if (!Tank2->isAlive())
			{	Log.push_back("Player1 Wins!!               \n");
			}
		}

		// Clear and print out the graphics
		cursorHome();
		PrintHeader(player, resPath+"Data/NoInstructions.dat", resPath+"Data/GameHeader.dat", 0);
		std::cout << std::setw(25) << std::left << "|Name: Player1" << std::setw(26) << std::right << "Name: Player2|\n";
		std::cout << std::setw(25) << std::left << "|Tank: " + Tank1->getName() << std::setw(26) << std::right << "Tank: " + Tank2->getName() + "|\n";
		std::cout << std::setw(25) << std::left << "|Health: " + std::to_string(Tank1->getHP()) + '/' + std::to_string(Tank1->getMaxHP()) << std::setw(26) << std::right << "Health: " + std::to_string(Tank2->getHP()) + '/' + std::to_string(Tank2->getMaxHP()) + "|\n";
		std::cout << std::setw(25) << std::left << "|Medikits: " + std::to_string(Tank1->getMedikits()) << std::setw(26) << std::right << "Medikits: " + std::to_string(Tank2->getMedikits()) + "|\n";
		std::cout << std::setw(25) << std::left << "|Fire: " + std::to_string(Tank1->getFire()) << std::setw(25) << std::right << "Fire: " + std::to_string(Tank2->getFire()) + "|" << "Action Log: \n";
		
		for (int i = 0; i < static_cast<int>(TankImage1.size()); i++)
			std::cout << TankImage1[i] << TankShot1[i] << TankShot2[i] << TankImage2[i] << Log[Log.size() - 5 + i];
		std::cout << '\n';


		// If someone is defeated, end the game
		if (!Tank1->isAlive() || !Tank2->isAlive())
		{	std::cout << "Press Any Key To Continue...                      \n                                                  \n                                                  \n                                                  \n                                                  \n                                                  \n                                                  \n                                                  \n";
			player.setMulti(player.getMulti() + 1);
			
			_getch();
			emptyScreen();
			break;
		}

		// Print the available actions 
		for (int i = 0; i < actionsLength; i++)
		{	
			std::string p1Action = i < (int)Tank1->getActions().size() ? (std::string("       ") + inputChart[i] + ", " + Tank1->getActions()[i]) : " ";
			std::string p2Action = i < (int)Tank2->getActions().size() ? (std::string("       ") + inputChart[i+8] + ", " + Tank2->getActions()[i]) : " ";

			std::cout << std::setw(25) << std::left << (p1Ready ? Ready[i] : p1Action);
			std::cout << std::setw(25) << std::left << (p2Ready ? Ready[i] : p2Action);
			std::cout << '\n';
		}

		// Take a character input
		buttonPress = _getch();
		translateInput(toupper(buttonPress), optNum, plNum);

		// Handle Player1's action pick
		if(plNum == 0 && !p1Ready)
		{
			if(Tank1->isSpecial())
			{	optNum--;
			}
			
			// Quit if the player is out of med kits
			if( !(optNum==4 && Tank1->getMedikits()==0) )
			{	
				p1Ready = true;
				// Execute an action and fill the action graphics
				switch (optNum)
				{	case -1: Tank1->DoSpecialMove(NextShot1, 0); break;
					case 0: Tank1->GenerateDamage(NextShot1, 0); break;
					case 1: Tank1->GenerateShieldDamage(NextShot1, 0); break;
					case 2: Tank1->GenerateDamageOverTime(NextShot1, 0); break;
					case 3: Tank1->Shield(NextShot1, 0); break;
					case 4: Tank1->Heal(NextShot1, 0); break;
					case 5: Tank1->Fix(NextShot1, 0); break;
					case 6: Tank1->Surrender(NextShot1); break;
					default: p1Ready = false;
				}
			}
		}

		// Handle Player2's action pick
		else if(plNum == 1 && !p2Ready)
		{
			if(Tank2->isSpecial())
			{	optNum--;
			}

			// Quit if the player is out of med kits
			if( !(optNum==4 && Tank2->getMedikits()==0) )
			{
				p2Ready = true;
				// Execute an action and fill the action graphics
				switch (optNum)
				{	case -1: Tank2->DoSpecialMove(NextShot2, 1); break;
					case 0: Tank2->GenerateDamage(NextShot2, 1); break;
					case 1: Tank2->GenerateShieldDamage(NextShot2, 1); break;
					case 2: Tank2->GenerateDamageOverTime(NextShot2, 1); break;
					case 3: Tank2->Shield(NextShot2, 1); break;
					case 4: Tank2->Heal(NextShot2, 1); break;
					case 5: Tank2->Fix(NextShot2, 1); break;
					case 6: Tank2->Surrender(NextShot2); break;
					default: p2Ready = false;
				}
			}
		}

		
		// If both players chose an action, execute them
		if (p1Ready && p2Ready)
		{	Log.push_back(" \n");

			// Assign the action graphics for the next stage
			TankShot1 = NextShot1;
			TankShot2 = NextShot2;
			NextShot1.clear();
			NextShot2.clear();

			// Revert ready to false for both players
			p1Ready = false, p2Ready = false;
			
			// Evalueate their health
			Log.push_back(Tank1->EvaluateHP(*Tank2, "Player1"));
			Log.push_back(Tank2->EvaluateHP(*Tank1, "Player2"));
		}
	}

	delete Tank1;
	delete Tank2;
	return;
}

bool passwordCheck(std::string input, std::string pass)
{
	int inLen = input.length();
	int psLen = pass.length();

	// If the input is shorter, the password can't match
	if(inLen < psLen)
	{	return false;
	}

	// Check from the back if the password matches the last inputed characters
	for(int i = 0; i < (int)pass.length(); i++)
	{	if(input[inLen-i-1] != pass[psLen-i-1])
		{	return false;
		}
	}

	return true;
}

/*MAIN MENU*/
// Main connection to everything in the game.
// Uses menu navigation up-down
void MainMenu()
{
	// Declarations and Initializations
	unsigned short active = 0;
	char buttonPress;
	std::string passInput="";
	std::vector<std::string> MainMenuOptions;

	Player player(resPath+"Profiles/Default.dat");
	ReadLines(resPath+"Data/MainMenuOptions.dat", MainMenuOptions);
	
	// Main menu Loop
	for (;;)
	{
		// Show the Menu
		PrintHeader(player, resPath+"Data/mainMenuInstructions.dat", resPath+"Data/GameHeader.dat", 1);
		for (unsigned short i = 0; i < MainMenuOptions.size(); i++)
		{	PrintOption(MainMenuOptions[i], active, i, MENUOFFSET);
			std::cout << '\n';
		}

		// Take a character Input
		buttonPress = _getch();
		if (buttonPress == 0 || buttonPress == 0xE0)
			buttonPress = _getch();

		if ((buttonPress == UP) && active > 0)
			active--;
		else if ((buttonPress == DOWN) && active < MainMenuOptions.size() - 1)
			active++;
		else if (buttonPress == ENTER)
		{
			emptyScreen();
			switch (active)
			{	case 0: SinglePlayer(player); break;
				case 1: MultiPlayer(player); break;
				case 2: Help(); break;
				case 3: ProfileStatistics(player); break;
				case 4: SaveProfile(player); break;
				case 5: LoadProfile(player); break;
				case 6: Credits(); break;
				case 7: return;
			}
		}
		// Check for secret passwords
		else if(buttonPress >= 32 &&  buttonPress <= 126)
		{
			passInput += (char)buttonPress; 
			if(passInput.length() > 10)
			{	passInput.erase(passInput.begin());
			}

			if (passwordCheck(passInput, "toasty"))
			{	player.setToasty(true);
			}
			else if(passwordCheck(passInput, "iamadev"))
			{	player.setDev(true);
			}
		}
	}
}

/*MAIN*/
int main()
{
	// Seeding the random number generator
	srand((unsigned int)time(NULL));

	// Console Resizing
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 680, 520, TRUE);

	// Hiding cursor
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO params{ 1, FALSE };
	SetConsoleCursorInfo(outputHandle, &params);

	MainMenu();
}
