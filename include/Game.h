// Davide Baggio

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <algorithm>

#include "Scacchiera.h"
#include "Pezzi.h"

using namespace std;

class Game
{
public:
	std::string randomCommand();
	bool isValid(const std::string &);
	bool computeCommand(std::ofstream &, Scacchiera &, const std::string &, bool, bool);

	bool canEnPassant(Scacchiera &, Pedina *, int, int);

	void startPC(ofstream &, ofstream &);
	void startCC(ofstream &, ofstream &);
};

#endif // GAME_H