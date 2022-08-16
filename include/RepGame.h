// Davide Baggio

#ifndef REPGAME_H
#define REPGAME_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <chrono>
#include <thread>
#include "Scacchiera.h"

using namespace std;

class RepGame
{
public:
	void computeCommand(Scacchiera &, const string &, const string &);
	void ReplayLogToLog(ifstream &, ofstream &, ifstream &);
	void ReplayLogToConsole(ifstream &, ifstream &);
};

#endif // REPGAME_H
