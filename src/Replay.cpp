// Baggio Davide

#include <iostream>
#include <fstream>
#include <string.h>
#include "../include/Scacchiera.h"
#include "../include/RepGame.h"

using namespace std;

/**
 * @brief Entry point dell'eseguibile Replay.exe. Gestisce il replay di una partita
 *
 * @param argc Accetta al massimo 3 argomenti: l'eseguibile, il file di lettura del replay e il
 * file di scrittura del replay.
 * @param argv
 * @return int 0.
 */
int main(int argc, char *argv[])
{
	/**
	 * @brief std::this_thread e std::chrono verranno usati
	 * per far passare il tempo di 1 secondo da ogni giocata stampata su Prompt dei comandi.
	 */

	RepGame repGame = RepGame();

	// Se si avvia Replay.exe con argomenti non corretti.
	if (argc <= 2 || argc > 4)
	{
		cout << "[Error] Incorrect arguments. Type: " << endl
			 << "\t v [input_file_name]: to watch the replay of the match." << endl
			 << "\t f [input_file_name] [output_file_name]: to watch the replay on the output file." << endl;
		return 0;
	}

	// Se si avvia Replay [input_file_name]
	else if (argc == 3 && strcmp(argv[1], "v") == 0)
	{
		// Apertura di file di log dove verranno lette tutte le mosse.
		ifstream inputFile(argv[2]);
		ifstream spec;
		if (strcmp(argv[2], "logPC.txt") == 0)
			spec.open("specPC.txt");
		else
			spec.open("specCC.txt");
		if (!inputFile.is_open() || !spec.is_open())
		{
			cout << "[Error] File = " << argv[2] << " not found\n";
			return 0;
		}
		else
		{
			cout << "Replay on command prompt\n";
			repGame.ReplayLogToConsole(inputFile, spec);
		}
		spec.close();
		inputFile.close();
	}

	// Se si avvia Replay.exe [input_file_name] [output_file_name]
	else if (strcmp(argv[1], "f") == 0)
	{
		// Apertura dei file di log dove verranno lette tutte le mosse e stampato il replay della partita.
		ifstream inputFile(argv[2]);
		ofstream outputFile(argv[3]);
		ifstream spec;
		if (strcmp(argv[2], "logPC.txt") == 0)
			spec.open("specPC.txt");
		else
			spec.open("specCC.txt");
		if (!inputFile.is_open() || !outputFile.is_open() || !spec.is_open())
		{
			cout << "[Error] Cannot open [argument files] or file name not provided. Check file names again.\n";
			return 0;
		}
		else
		{
			outputFile.clear();
			cout << "Replay on [file] = " << argv[3] << "\n";

			repGame.ReplayLogToLog(inputFile, outputFile, spec);

			inputFile.close();
			outputFile.close();
			spec.close();
		}
		return 0;
	}
}