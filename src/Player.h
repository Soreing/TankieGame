#ifndef PLAYER_H
#define PLAYER_H

#include<string>

class Player
{
private:
	bool dev, toasty;
	int score, wins, defeats, ties, multi;
	int tanks[6];
	std::string name;

public:
	Player(const std::string);
	inline std::string getName() { return name; }
	inline std::string getTanks() { return (std::to_string(tanks[0]) + " " + std::to_string(tanks[1]) + " " + std::to_string(tanks[2]) + " " + std::to_string(tanks[3]) + " " + std::to_string(tanks[4]) + " " + std::to_string(tanks[5])); }
	inline int getScore() { return score; }
	inline int getWins() { return wins; }
	inline int getDefeats() { return defeats; }
	inline int getTies() { return ties; }
	inline int getMulti() { return multi; }
	inline bool isDev() { return dev; }
	inline bool isToasty() { return toasty; }
	inline void setName(const std::string str) { name = str; }
	inline void setScore(const int val) { score = val; }
	inline void setWins(const int val) { wins = val; }
	inline void setDefeats(const int val) { defeats = val; }
	inline void setTies(const int val) { ties = val; }
	inline void setMulti(const int val) { multi = val; }
	inline void setDev(const bool val) { dev = val; }
	inline void setToasty(const bool val) { toasty = val; }
	inline void incrementTank(const int index) { tanks[index]++; }
	std::string getTank();
};

#endif