#ifndef UTILS_CPP
#define UTILS_CPP

#include "Player.h"

#include<iostream>
#include<fstream>
#include<conio.h>
#include<vector>
#include<iomanip>
#include<ctime>
#include<cstdlib>
#include<windows.h>

static const std::string resPath = "../Resources/";

void cursorHome();
void emptyScreen();
void ReadLines(const std::string, std::vector<std::string>&);
void PrintLines(const std::string, std::vector<std::string>&);
void PrintProfile(Player&, std::string);
void ShowWholeFile(const std::string);
void PrintHeader(Player&, std::string, std::string, bool);
void PrintOption(std::string, const int, const int, const int);
bool FileExists(const std::string);
bool YesNoMenu();

#endif