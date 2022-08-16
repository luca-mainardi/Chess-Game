// Davide Baggio

#include "../include/RepGame.h"

/**
 * @brief Funzione che trasforma un opportuno comando in coordinate della scacchiera (da char a int)
 * e muove la pedina nella scacchiera di conseguenza. Non vengono fatti controlli perchè il programma
 * svolge replay di partite con mosse già validate.
 *
 * @param sca Riferimento alla Scacchiera
 * @param cmd Stringa del comando
 */
void RepGame::computeCommand(Scacchiera &sca, const string &cmd, const string &special)
{
	int xi = ((int)cmd[0]) - 65;	   //-65 per ascii table A
	int yi = 7 - (((int)cmd[1]) - 49); //-49 per ascii table 1
	int xf = ((int)cmd[3]) - 65;	   //-65 per ascii table B
	int yf = 7 - (((int)cmd[4]) - 49); //-49 per ascii table 3
	Pedina *temp = sca.getPedina(xi, yi);
	if (special == "")
		sca.move(temp, xf, yf);
	else if (special == "ArroccoN" || special == "ArroccoB")
		sca.arrocco(xi, yi, xf, yf);
	else if ((int)special[0] < 91){
		sca.move(temp, xf, yf);
		sca.replayPromo(temp, special, false);
	}
	else if ((int)special[0] > 91){
		sca.move(temp, xf, yf);
		sca.replayPromo(temp, special, true);
	}
}

/**
 * @brief Replay della partita su file di output
 *
 * @param inputFile File con le mosse
 * @param outputFile File del replay
 * @param spec File delle mosse speciali.
 */
void RepGame::ReplayLogToLog(ifstream &inputFile, ofstream &outputFile, ifstream &spec)
{
	// Inizializzazione della Scacchiera
	Scacchiera s{};
	outputFile << "Scacchiera iniziale: \n"
			   << s << "\n";

	string command;
	int g = 1;

	// Lettura dei comandi da inputFile affinchè non sono terminati.
	while (getline(inputFile, command))
	{
		string special;
		if (g > 0)
		{
			getline(spec, special);
			outputFile << "Player 1: \n";
			computeCommand(s, command, special);
			outputFile << command << "\n";
			outputFile << s << "\n\n";
		}
		else
		{
			getline(spec, special);
			outputFile << "Player 2: \n";
			computeCommand(s, command, special);
			outputFile << command << "\n";
			outputFile << s << "\n\n";
		}

		// Cambio giocatore ogni turno.
		g *= -1;
	}
}

/**
 * @brief Replay della partita su console
 *
 * @param inputFile File con le mosse
 * @param spec File delle mosse speciali.
 */
void RepGame::ReplayLogToConsole(ifstream &inputFile, ifstream &spec)
{
	// Inizializzazione Scacchiera
	Scacchiera s{};
	cout << "Scacchiera iniziale: \n"
		 << s << "\n";

	string command;
	int g = 1;

	// Lettura dei comandi da inputFile affinchè non sono terminati.
	while (getline(inputFile, command))
	{
		string special;
		// Giocatore 1
		if (g > 0)
		{
			getline(spec, special);
			cout << "Player 1: \n";
			computeCommand(s, command, special);
			cout << command << "\n";
			cout << s << "\n\n";
		}

		// Giocatore 2
		else
		{
			getline(spec, special);
			cout << "Player 2: \n";
			computeCommand(s, command, special);
			cout << command << "\n";
			cout << s << "\n\n";
		}

		// Cambio giocatore ogni turno
		g *= -1;

		this_thread::sleep_for(chrono::seconds(1)); // 1 secondo da una giocata all'altra
	}
}