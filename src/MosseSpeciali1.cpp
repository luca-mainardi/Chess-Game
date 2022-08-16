// Melissa Maistro

#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"
using namespace std;
/**
 * @brief gestisce la promozione del pedone
 *
 * @param p pedone che viene promosso
 * @param player colore del pedone che viene promosso
 */
void Scacchiera::promozione(ofstream &spec, Pedina *p, bool player, bool pl)
{
	if (p->getColor() == player && pl)	// colore del  giocatore e partita PC
	{
		cout << "\nPromozione del Pedone del Giocatore\n";
		cout << "Inserire la pedina con il quale vogliamo promuovere:\n";
		char name;
		do
		{
			cin >> name;
		} while (name != 't' && name != 'c' && name != 'a' && name != 'd' && name != 'r');
		int x = p->getX();
		int y = p->getY();
		Pedina *temp;
		if (name == 't')
			temp = new Torre(x, y, player, name);
		if (name == 'c')
			temp = new Cavallo(x, y, player, name);
		if (name == 'a')
			temp = new Alfiere(x, y, player, name);
		if (name == 'd')
			temp = new Regina(x, y, player, name);
		if (name == 'r')
			temp = new Re(x, y, player, name);
		changePiece(x, y, temp);
		spec << temp->getName() << "\n";
	}
	else if(p->getColor() == player)
	{
		cout << "\nPromozione del Pedone del Computer\n";
		int x = p->getX();
		int y = p->getY();
		Pedina *temp = new Regina(x, y, player, 'd');
		changePiece(x, y, temp);
		spec << temp->getName() << "\n";
	}else{
		cout << "\nPromozione del Pedone del Computer\n";
		int x = p->getX();
		int y = p->getY();
		Pedina *temp = new Regina(x, y, !player, 'd');
		changePiece(x, y, temp);
		spec << temp->getName() << "\n";
	}
}

void Scacchiera::replayPromo(Pedina *p, string special, bool player)
{
	int x = p->getX();
	int y = p->getY();
	Pedina *temp;
	if (special == "t" || special == "T")
		temp = new Torre(x, y, player, special[0]);
	if (special == "c" || special == "C")
		temp = new Cavallo(x, y, player, special[0]);
	if (special == "a" || special == "A")
		temp = new Alfiere(x, y, player, special[0]);
	if (special == "d" || special == "D")
		temp = new Regina(x, y, player, special[0]);
	if (special == "r" || special == "R")
		temp = new Re(x, y, player, special[0]);
	changePiece(x, y, temp);
}

/**
 * @brief gestisce cattura "En Passant"; le precondizioni della mossa sono verificate dalla
 * funzione canEnPassant della classe Game
 *
 * @param p pedone che cattura
 * @param xf ascissa del pedone da catturare
 * @param yf ordinata del pedone da catturare
 */
void Scacchiera::enPassant(Pedina *p, int xf, int yf)
{
	// salva coordinate di partenza
	int xi = p->getX();
	int yi = p->getY();
	// sposta pedina e elimina quella mangiata
	p->setPos(xf, yf);
	delete matrice[xf][yf];
	matrice[xf][yf] = p;
	matrice[xi][yi] = nullptr;
}
