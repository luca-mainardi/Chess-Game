// Luca Mainardi
#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"
using namespace std;

/**
 * @brief posiziona pedine nella posizione di partenza
 */
Scacchiera::Scacchiera()
{
	bool gWhite = false; // colore pedine
	for (int i = 0; i < 8; i++)
	{
		if (i > 3) // meta' scacchiera
			gWhite = true;
		for (int j = 0; j < 8; j++)
		{
			if (i == 1) // fila di pedoni neri
			{
				matrice[j][i] = new Pedone(j, i, gWhite, 'p');
			}
			else if (i == 6) // fila di pedoni bianchi
			{
				matrice[j][i] = new Pedone(j, i, gWhite, 'p');
			}
			else if (i == 0) // fila con pedine nere
			{
				if (j == 0 || j == 7)
				{
					matrice[j][i] = new Torre(j, i, gWhite, 't');
				}
				if (j == 1 || j == 6)
				{
					matrice[j][i] = new Cavallo(j, i, gWhite, 'c');
				}
				if (j == 2 || j == 5)
				{
					matrice[j][i] = new Alfiere(j, i, gWhite, 'a');
				}
				if (j == 3)
				{
					matrice[j][i] = new Regina(j, i, gWhite, 'd');
				}
				if (j == 4)
				{
					matrice[j][i] = new Re(j, i, gWhite, 'r');
				}
			}
			else if (i == 7) // fila con pedine bianche
			{
				if (j == 0 || j == 7)
				{
					matrice[j][i] = new Torre(j, i, gWhite, 't');
				}
				if (j == 1 || j == 6)
				{
					matrice[j][i] = new Cavallo(j, i, gWhite, 'c');
				}
				if (j == 2 || j == 5)
				{
					matrice[j][i] = new Alfiere(j, i, gWhite, 'a');
				}
				if (j == 3)
				{
					matrice[j][i] = new Regina(j, i, gWhite, 'd');
				}
				if (j == 4)
				{
					matrice[j][i] = new Re(j, i, gWhite, 'r');
				}
			}
			else // caselle vuote
			{
				matrice[j][i] = nullptr;
			}
		}
	}
}

Scacchiera::~Scacchiera()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete matrice[i][j];
			matrice[i][j] = nullptr;
		}
	}
}

/**
 * @brief stampa la scacchiera
 */
ostream &operator<<(ostream &os, const Scacchiera &sca)
{
	for (int i = 0; i < 8; i++)
	{
		os << 8 - i << "  ";
		for (int j = 0; j < 8; j++)
		{
			if (sca.getPedina(j, i) == nullptr)
				os << "  ";
			else
				os << sca.getPedina(j, i)->getName() << " ";
		}
		os << "\n";
	}
	os << "\n   A B C D E F G H\n";

	return os;
}

/**
 * @brief inserisce una pedina nella cella indicata nelle sue coordinate (membri di Pedina)
 */
void Scacchiera::setPedina(Pedina *p)
{
	matrice[p->getX()][p->getY()] = p;
}

/**
 * @brief Sostituisce una pedina con un pezzo diverso (usato nella promozione)
 * @param x coordinata x della pedina da sostituire
 * @param y coordinata y della pedina da sostituire
 * @param p nuova pedina
 */
void Scacchiera::changePiece(int x, int y, Pedina *p)
{
	delete matrice[x][y];
	matrice[x][y] = p;
}

/**
 * @brief libera la casella di coordinate (x,y)
 */
void Scacchiera::setPtr(int x, int y)
{
	matrice[x][y] = nullptr;
}

/**
 * @brief sposta la pedina invocando il metodo Pedina::checkPos per verificare le mosse valide
 * @param p pedina da spostare
 * @param j ascissa della casella in cui si vuole spostare p
 * @param i ordinata della casella in cui si vuole spostare p
 * @throws InvalidPosition se (j,i) non e' una posizione valida
 * @throws InvalidMove se la mossa non e'consentita (se e' scacco)
 */
void Scacchiera::move(Pedina *p, int j, int i)
{
	// controlla che casella (j,i) sia valida per p
	if (!(p->checkPos(j, i, matrice)))
		throw InvalidPosition();

	// memorizza eventuale pedina in (j,i)
	Pedina *temp = matrice[j][i];

	// salva coordinate di partenza
	int x = p->getX();
	int y = p->getY();

	// provo a spostare la pedina
	p->setPos(j, i);		 // aggiorna coordinate della pedina
	matrice[j][i] = p;		 // aggiorna matrice
	matrice[x][y] = nullptr; // libera cella di partenza

	if (p->getColor()) // se e' bianca
	{
		if (isScaccoBianco()) // se il giocatore che ha fatto la mossa e' sotto scacco bisogna annullare la mossa e lanciare eccezione
		{
			matrice[x][y] = p;
			matrice[j][i] = temp;
			p->setPos(x, y);
			throw InvalidMove();
		}
		else // bianco non e' sotto scacco
		{
			// dealloca la memoria della pedina mangiata
			if (temp != nullptr)
			{
				delete temp;
			}
		}
	}
	else // e' nera
	{
		if (isScaccoNero()) // se il giocatore che ha fatto la mossa e' sotto scacco bisogna annullare la mossa e lanciare eccezione
		{
			matrice[x][y] = p;
			matrice[j][i] = temp;
			p->setPos(x, y);
			throw InvalidMove();
		}
		else // nero non e' sotto scacco
		{
			// dealloca la memoria della pedina mangiata
			if (temp != nullptr)
			{
				delete temp;
			}
		}
	}
	p->increaseCount();
}
/**
 * @brief controlla se il giocatore nero uno e' sotto scacco
 * @return true se nero e' sotto scacco
 * @return false se nero non e' sotto scacco
 */
bool Scacchiera::isScaccoNero()
{
	// inizializzazione a indici non validi
	int reNeroX = -1, reNeroY = -1;

	// trova posizione re
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!isEmpty(j, i))
			{
				if (getPedina(j, i)->getName() == 'R') // re nero
				{
					reNeroX = j;
					reNeroY = i;
				}
			}
		}
	}

	// controlla se le altre pedine potrebbero muoversi nella casella del re (e quindi catturarlo)
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!isEmpty(j, i))
			{
				Pedina *p = getPedina(j, i);

				if (p->getColor()) // se c'e' una pedina ed e' bianca
				{
					if (p->checkPos(reNeroX, reNeroY, matrice)) // scacco al nero
						return true;
				}
			}
		}
	}
	return false; // non scacco
}

/**
 * @brief controlla se il giocatore bianco uno e' sotto scacco
 * @return true se bianco e' sotto scacco
 * @return false se bianco non e' sotto scacco
 */
bool Scacchiera::isScaccoBianco()
{
	// inizializzazione a indici non validi
	int reBiancoX = -1, reBiancoY = -1;

	// trova posizione re
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!isEmpty(j, i))
			{
				if (getPedina(j, i)->getName() == 'r') // re bianco
				{
					reBiancoX = j;
					reBiancoY = i;
				}
			}
		}
	}

	// controlla se le altre pedine potrebbero muoversi nella casella del re (e quindi catturarlo)
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!isEmpty(j, i))
			{
				Pedina *p = getPedina(j, i);

				if (!p->getColor()) // se c'e' una pedina ed e' nera
				{
					if (p->checkPos(reBiancoX, reBiancoY, matrice)) // scacco al bianco
						return true;
				}
			}
		}
	}
	return false; // non scacco
}

/**
 * @brief controlla se il giocatore nero uno e' sotto scaccomatto
 * @return true se nero e' sotto scaccomatto
 * @return false se nero non e' sotto scaccomatto
 */
bool Scacchiera::isScaccoMattoNero()
{
	if (isScaccoNero() && !neroHasValidPositions())
		return true;
	return false;
}

/**
 * @brief controlla se il giocatore bianco uno e' sotto scaccomatto
 * @return true se bianco e' sotto scaccomatto
 * @return false se bianco non e' sotto scaccomatto
 */
bool Scacchiera::isScaccoMattoBianco()
{
	if (isScaccoBianco() && !biancoHasValidPositions())
		return true;
	return false;
}
/**
 * @brief controlla la condizione di patta
 *
 * @param cmd ultime tre mosse (per verificare patta per mossa ripetuta)
 * @return 0 se non e' patta
 * @return 1 se bianco e'in stallo
 * @return 2 se nero e' in stallo
 * @return 3 se e' patta per mosse ripetute
 */
int Scacchiera::isPatta(vector<string> &cmd)
{
	// patta per assenza di posizioni valide
	if (!isScaccoNero() && !neroHasValidPositions()) // se nero non e' scacco ma non ha pos valide
	{
		return 2; // nero in stallo
	}
	if (!isScaccoBianco() && !biancoHasValidPositions()) // se bianco non e' scacco ma non ha pos valide
	{
		return 1; // bianco in stallo
	}
	// patta per mosse ripetute
	try
	{
		for (int i = 0; i < cmd.size(); i++) // verifica se tre mosse sono ripetute
		{
			string s1 = cmd.at(i);
			string s2 = cmd.at(i + 1);

			if (s1 == cmd.at(i + 4) && s1 == cmd.at(i + 8) && s2 == cmd.at(i + 5) && s2 == cmd.at(i + 9))
				return 3; // giocatori 1 e 2 in stallo
		}
	}
	catch (out_of_range &e) // se indice non valido non puo' essere patta (fine del vector)
	{
		return 0;
	}
	return 0;
}

/**
 * @brief controlla se il nero ha delle posizioni valide, cioe' mosse che non
 * provocano scacco al giocatore che le esegue o che permettono di uscire da una situazione di scacco
 * (questa funzione e' necessaria alle funzioni isScaccoMattoNero e isPatta)
 *
 * @return true se nero ha almeno una posizione  valida
 * @return false se nero non ha posizioni valide (e' scaccomatto oppure patta per stallo)
 */
bool Scacchiera::neroHasValidPositions()
{
	bool neroHasPositions = false;
	// esamina ogni pedina nera
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!isEmpty(j, i)) // c'e'una pedina in (j,i)
			{
				Pedina *p = matrice[j][i];

				if (!p->getColor()) // se la pedina e' nera
				{
					// prova tutti i movimenti della pedina esaminata e vede se e' scacco
					for (int y = 0; y < 8; y++)
					{
						for (int x = 0; x < 8; x++)
						{
							// se la posizione e'valida per lo spostamento
							if (p->checkPos(x, y, matrice))
							{
								Pedina *temp = matrice[x][y];

								// se c'e' il re bianco non puo'provare a spostarsi(NON si puo' mangiare il re)
								if (temp != nullptr && temp->getName() == 'r')
								{
								}
								else // non c'e' re bianco
								{
									// prova movimento (NON si puo fare move() perche mangerebbe le pedine)
									matrice[x][y] = p;
									matrice[j][i] = nullptr;
									if (!isScaccoNero()) // se non e' scacco allora il nero ha almeno una posizione valida
									{
										neroHasPositions = true;
									}
									// torna indietro
									matrice[j][i] = matrice[x][y];
									matrice[x][y] = temp;
								}
							}
						}
					}
				}
			}
		}
	}
	return neroHasPositions;
}

/**
 * @brief controlla se il bianco ha delle posizioni valide, cioe' mosse che non
 * provocano scacco al giocatore che le esegue o che permettono di uscire da una situazione di scacco
 * (questa funzione e' necessaria alle funzioni isScaccoMattoBianco e isPatta)
 *
 * @return true se bianco ha almeno una posizione  valida
 * @return false se bianco non ha posizioni valide (e' scaccomatto oppure patta per stallo)
 */
bool Scacchiera::biancoHasValidPositions()
{
	bool biancoHasPositions = false;
	// esamina ogni pedina
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (!isEmpty(j, i))
			{
				Pedina *p = matrice[j][i];
				if (p->getColor()) // se la pedina e' bianca
				{
					// prova tutti i movimenti della pedina esaminata e vede se e' scacco
					for (int y = 0; y < 8; y++)
					{
						for (int x = 0; x < 8; x++)
						{
							// se la posizione e'valida per lo spostamento
							if (p->checkPos(x, y, matrice))
							{
								Pedina *temp = matrice[x][y];

								// se c'e' il re nero non puo'provare a spostarsi(NON si puo' mangiare il re)
								if (temp != nullptr && temp->getName() == 'R')
								{
								}
								else // se non c'e' il re nero
								{
									// prova movimento (NON si puo fare move() perche mangerebbe le pedine)
									matrice[x][y] = p;
									matrice[j][i] = nullptr;
									if (!isScaccoBianco()) // se non e' scacco allora il bianco ha almeno una posizione valida
									{
										biancoHasPositions = true;
									}
									// torna indietro
									matrice[j][i] = matrice[x][y];
									matrice[x][y] = temp;
								}
							}
						}
					}
				}
			}
		}
	}
	return biancoHasPositions;
}
