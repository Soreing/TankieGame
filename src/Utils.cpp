#include "Utils.h"

#define PAGE_LENGTH 27

// Moves teh cursor to the start of the terminal at 0,0
void cursorHome()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

// Empties the screen from text
void emptyScreen()
{
	cursorHome();
	
	for(int i=0;i<PAGE_LENGTH; i++)
	{	std::cout << "                                                                               \n";
	}
	
	cursorHome();
}

//A function that reads lines into a container
void ReadLines(const std::string path, std::vector<std::string> &container)
{
	std::ifstream inFile(path);
	std::string line;

	while (getline(inFile, line))
	{	container.push_back(line);
	}
	
	inFile.close();
}
//A function that prints out lines fro ma container
void PrintLines(const std::string path, std::vector<std::string> &container)
{
	std::ofstream outFile(path);
	
	for (int i = 0; i < (int)container.size(); i++)
	{	outFile << container[i] << '\n';
	}
	
	outFile.close();
}
//A function for saving the profile to a file
void PrintProfile(Player& player, std::string path)
{
	std::ofstream outFile(path);
	outFile << player.getName() << ' ' << player.getScore() << ' ' << player.getWins() << ' ' << player.getDefeats() << ' ' << player.getTies() << ' ' << player.getMulti() << ' ' << player.getTanks();
	outFile.close();
}
//A function for displaying all the content of a file to the screen as it is
void ShowWholeFile(const std::string path)
{
	std::ifstream inFile(path);
	std::string file, part;
	
	while (getline(inFile, part))
	{	file += part + '\n';
	}
	std::cout << file << "\n";
	
	inFile.close();
}
//Prints the title and additional information to the screen
void PrintHeader(Player &player, std::string instruction, std::string header, bool score)
{
	cursorHome();
	
	if (score)
	{	std::cout << "Profile: " << player.getName() << "\nScore: " << player.getScore() << '\n';
	}
	
	ShowWholeFile(header);
	ShowWholeFile(instruction);
}
//A function used for printing out menu options in a menu that can be navigated
void PrintOption(std::string option, const int active, const int index, const int indent)
{
	if (active == index)
	{	std::cout << std::setw(indent) << std::right << "->";
	}
	else
	{	std::cout << std::setw(indent) << std::right << "  ";
	}
	
	std::cout << std::setw(25) << std::left << option;
}
//A function that checks if a file exists or not
bool FileExists(const std::string path)
{
	std::ifstream test(path);
	if (test)
	{	test.close();
		return true;
	}
	test.close();
	return false;
}
//A simple prompting function that forces the user to enter either Y or N (yes or no)
bool YesNoMenu()
{
	char buttonPress;
	for (;;)
	{
		buttonPress = _getch();
		if (buttonPress == 'y' || buttonPress == 'Y')
		{	return true;
		}
		else if (buttonPress == 'n' || buttonPress == 'N')
		{	return false;
		}
	}
}