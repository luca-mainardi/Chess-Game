// Davide Baggio

#include "../include/Game.h"
using namespace std;

/**
 * @brief Funzione che estrae un comando casuale per il Computer
 *
 * @return string Comando per il movimento
 */
string Game::randomCommand()
{
	char c1;
	string commandPC = "";
	for (int i = 0; i < 5; i++)
	{
		if (i == 0 || i == 3)
			c1 = (char)(rand() % 8 + 65);
		else
			c1 = (char)(rand() % 8 + 49);
		if (i != 2)
			commandPC += c1;
		else
			commandPC += " ";
	}
	return commandPC;
}

/**
 * @brief Controlla che il comando inserito abbia il formato corretto
 *
 * @param cmd Comando inserito
 * @return true Comando corretto es: A6 C5 (XX XX)
 * @return false Comando errato
 */
bool Game::isValid(const string &cmd)
{
	if (cmd.length() != 5 || (int)cmd[0] < 65 || (int)cmd[0] > 72 || (int)cmd[1] < 49 || (int)cmd[1] > 57 ||
		(int)cmd[3] < 65 || (int)cmd[3] > 72 || (int)cmd[4] < 49 || (int)cmd[4] > 57 || cmd[2] != ' ')
	{
		cout << "Errore nella scrittura del comando\n";
		return false;
	}
	else
		return true;
}

/**
 * @brief Funzione che controlla se è possibile fare la mossa speciale enPassant
 *
 * @param sca
 * @param p
 * @param xf
 * @param yf
 * @return true
 * @return false
 */
bool Game::canEnPassant(Scacchiera &sca, Pedina *p, int xf, int yf)
{
	// controllo se destinazione e' occupata da un pedone
	Pedina *target;
	if (!sca.isEmpty(xf, yf))
	{
		target = sca.getPedina(xf, yf);
		// controlla che target sia un pedone
		if (target->getName() != 'p' || target->getName() != 'P')
			return false;
	}
	else
	{
		return false;
	}
	// controlla se destinazione  e' occupata da un pedone
	if (p->getName() != 'p' || p->getName() != 'P')
		return false;

	if (p->getName() == 'p') // pedone bianco
	{
		if (p->getY() != 3)
			return false;
	}
	else // pedone nero
	{
		if (p->getY() != 4)
			return false;
	}

	// controlla se target ha eseguito solo un movimento (che e' di due caselle)
	if (target->getMoveCount() != 1)
		return false;

	// controlla se destinazione e' di fianco al pedone (unica da verificare)
	if (yf == p->getY() && (xf == p->getX() - 1 || xf == p->getX() + 1))
		return true;

	return false;
}

/**
 * @brief Funzione che computa il comando inserito in movimento par la pedina interessata
 *
 * @param spec
 * @param sca
 * @param cmd
 * @param col
 * @param err
 * @return true se è avvenuto il movimento
 * @return false altrimenti
 */
bool Game::computeCommand(ofstream &spec, Scacchiera &sca, const string &cmd, bool col, bool err) // funzione che trasforma il comado 'stringa' in coordinate di partenza e arrivo della pedina
{
	if (!isValid(cmd))
		return false;
	int xi = ((int)cmd[0]) - 65;	   //-65 per ascii table A
	int yi = 7 - (((int)cmd[1]) - 49); //-49 per ascii table 0
	int xf = ((int)cmd[3]) - 65;	   //-65 per ascii table A
	int yf = 7 - (((int)cmd[4]) - 49); //-49 per ascii table 0

	Pedina *temp = sca.getPedina(xi, yi);
	if (temp == nullptr)
	{
		if (err)
			cout << "Non stai spostando alcuna pedina\n";
		return false;
	}
	if (temp->getColor() != col)
	{
		if (err)
			cout << "Stai spostando la pedina dell'altro colore.\n";
		return false;
	}
	try
	{
		// cattura en passant
		if (canEnPassant(sca, temp, xf, yf))
		{
			sca.enPassant(temp, xf, yf);
		}
		// comando per arrocco   (si indicano la posizione del re e della torre che si vogliono spostare con l'arrocco)
		//  le precondizioni vengono verificate anche nella funzione
		else if (xi == 4 && yi == 0 && yf == 0 && (xf == 0 || xf == 7)) // arrocco nero
		{
			sca.arrocco(xi, yi, xf, yf);
			cout << "Arrocco\n";
			spec << "ArroccoN\n";
		}
		else if (xi == 4 && yi == 7 && yf == 7 && (xf == 0 || xf == 7)) // arrocco bianco
		{
			sca.arrocco(xi, yi, xf, yf);
			cout << "Arrocco\n";
			spec << "ArroccoB\n";
		}
		else
		{
			sca.move(temp, xf, yf);
			// promozione
			if ((temp->getName() == 'p' && temp->getY() == 0) || (temp->getName() == 'P' && temp->getY() == 7))
			{
				sca.promozione(spec, temp, col, err);
			}
			else
			{
				spec << "\n";
			}
		}
	}
	catch (const InvalidPosition &e)
	{
		if (err)
			cout << "Mossa non consentita.\n";
		return false;
	}
	catch (const InvalidMove &e)
	{
		if (err)
			cout << "Mossa non consentita: giocatore sotto scacco.\n";
		return false;
	}

	return true;
}

/**
 * @brief Starter del gioco Player vs Computer
 *
 * @param outputFile File di log delle mosse
 * @param spec File di log delle mosse speciali
 */
void Game::startPC(ofstream &outputFile, ofstream &spec)
{
	cout << "\nGiocatore Nero: Pedine con carattere maiuscolo;\nGiocatore Bianco: Pedine con carattere minuscolo.\n";
	Scacchiera s{};
	cout << "Scacchiera iniziale: \n"
		 << "\n"
		 << s << "\n";

	bool player = (bool)(rand() % 2);
	// Apertura di file di log dove verranno salvate tutte le mosse.

	vector<string> cmd{};

	// ciclo partita
	while (true)
	{
		//--------------------------- turno del bianco ---------------------------------
		if (s.isScaccoBianco())
		{
			cout << "Giocatore Bianco sotto scacco\n";
			// outputFile << "Giocatore sotto scacco\n";
		}
		if (s.isPatta(cmd) == 1)
		{
			cout << "Patta: Bianco in stallo\n";
			break;
		}

		cout << "Giocatore Bianco: \n";
		string commandW;

		// Inserimento del comando attraverso std::istream affinchè non sia valido.
		if (player)
		{
			do
			{
				getline(cin, commandW);
				// trasforma il comando in toUpperCase;
				transform(commandW.begin(), commandW.end(), commandW.begin(), ::toupper);
			} while (!computeCommand(spec, s, commandW, player, player));
		}
		else
		{
			do
			{
				commandW = randomCommand();
				// trasforma il comando in toUpperCase;
				transform(commandW.begin(), commandW.end(), commandW.begin(), ::toupper);
			} while (!computeCommand(spec, s, commandW, !player, player));
			cout << commandW;
		}

		cmd.push_back(commandW);
		outputFile << commandW << "\n";

		// stampa scacchiera
		cout << "\n"
			 << s << "\n";

		// controlla se la partita e'finita
		if (s.isScaccoMattoNero())
		{
			cout << "Nero sotto scacco matto\n";
			break;
		}
		if (s.isPatta(cmd) == 3)
		{
			cout << "Patta: Mosse ripetute\n";
			break;
		}

		//--------------------------- turno del nero ---------------------------------
		// controlla se computer e' sotto scacco
		if (s.isScaccoNero())
		{
			cout << "Nero sotto scacco\n";
			// outputFile << "Computer sotto scacco\n";
		}
		if (s.isPatta(cmd) == 2)
		{
			cout << "Patta: Nero in stallo\n";
			break;
		}

		cout << "Giocatore Nero: \n";
		string commandB = "";

		// Estrazione casuale del comando da parte del PC affinchè non sia valido.
		if (!player)
		{
			do
			{
				getline(cin, commandB);
				// trasforma il comando in toUpperCase;
				transform(commandB.begin(), commandB.end(), commandB.begin(), ::toupper);
			} while (!computeCommand(spec, s, commandB, player, !player));
		}
		else
		{
			do
			{
				commandB = randomCommand();
				// trasforma il comando in toUpperCase;
				transform(commandB.begin(), commandB.end(), commandB.begin(), ::toupper);
			} while (!computeCommand(spec, s, commandB, !player, !player));
			cout << commandB;
		}
		// stampa comando
		cmd.push_back(commandB);
		outputFile << commandB << "\n";

		// stampa scacchiera
		cout << "\n"
			 << s << "\n";

		// controlla se la partita e'finita
		if (s.isScaccoMattoBianco())
		{
			cout << "Bianco sotto scacco matto\n";
			break;
		}
		if (s.isPatta(cmd) == 3)
		{
			cout << "Patta: Mosse ripetute\n";
			break;
		}
	}
}

/**
 * @brief Starter del gioco Computer vs Computer
 *
 * @param outputFile File di log delle mosse
 * @param spec File di log delle mosse speciali
 */
void Game::startCC(ofstream &outputFile, ofstream &spec)
{
	// PC vs PC ha un massimo di mosse
	int mosseMax = 50;
	cout << "\nNumero massimo di mosse: " << mosseMax << " per giocatore\n";

	Scacchiera s{};
	cout << "Scacchiera iniziale: \n"
		 << "\n"
		 << s << "\n";

	// Apertura di file di log dove verranno salvate tutte le mosse.

	vector<string> cmd{};
	// Ciclo per la partita, continua finchè una delle condizioni non sia verificata
	// while (s.isPatta(cmd) !=3 && !s.isScaccoMattoNero() && !s.isScaccoMattoBianco() && mosseMax > 0)
	while (mosseMax > 0)
	{
		cout << "Mossa " << 51 - mosseMax << endl;
		if (s.isScaccoBianco())
		{
			cout << "PC1 sotto scacco\n";
			// outputFile << "PC1 sotto scacco\n";
		}
		if (s.isPatta(cmd) == 1)
		{
			cout << "Patta: PC1 in stallo\n";
			break;
		}

		cout << "computer 1 (bianco): \n";
		string commandPC1 = "";

		// Estrazione casuale del comando da parte del PC affinchè non sia valido.
		do
		{
			commandPC1 = randomCommand();
		} while (!computeCommand(spec, s, commandPC1, true, false));

		// stampa il comando
		cmd.push_back(commandPC1);
		cout << commandPC1 << "\n";
		outputFile << commandPC1 << "\n";

		// stampa scacchiera
		cout << s << "\n";

		// controlla se la partita e'finita
		if (s.isScaccoMattoNero())
		{
			cout << "Computer 2 sotto scacco matto\n";
			break;
		}
		if (s.isPatta(cmd) == 3)
		{
			cout << "Patta: Mosse ripetute\n";
			break;
		}

		this_thread::sleep_for(chrono::seconds(1)); // 1 secondo da una giocata all'altra

		//--------------------------- turno del nero ---------------------------------

		if (s.isScaccoNero())
		{
			cout << "PC2 sotto scacco\n";
			// outputFile << "PC2 sotto scacco\n";
		}
		if (s.isPatta(cmd) == 2)
		{
			cout << "Patta: PC2 in stallo\n";
			break;
		}

		cout << "computer 2 (nero): \n";
		string commandPC2 = "";

		// Estrazione casuale del comando da parte del PC affinchè non sia valido.
		do
		{
			commandPC2 = randomCommand();
		} while (!computeCommand(spec, s, commandPC2, false, false));

		// stampa comando
		cmd.push_back(commandPC2);
		cout << commandPC2 << "\n";
		outputFile << commandPC2 << "\n";

		// stampa scacchiera
		cout << s << "\n";

		// controlla se la partita e'finita
		if (s.isScaccoMattoBianco())
		{
			cout << "Computer 1 sotto scacco matto\n";
			break;
		}
		if (s.isPatta(cmd) == 3)
		{
			cout << "Patta: Mosse ripetute\n";
			break;
		}

		mosseMax--;

		this_thread::sleep_for(chrono::seconds(1)); // 1 secondo da una giocata all'altra
	}
	if (mosseMax == 0)
	{
		cout << "Raggiunto limite di mosse\n";
	}
}