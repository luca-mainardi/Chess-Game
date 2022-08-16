//Luca Mainardi

#ifndef SCACCHIERA_H
#define SCACCHIERA_H

#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>

//_________________________________ PEDINA ______________________________
class Pedina
{
private:
	int x;
	int y;
	bool color;
	char name;
	int moveCount;

public:
	Pedina(int, int, bool, char); // pos x, pos y, colore(true bianco, false nero), lettera ref
	virtual ~Pedina() {}

	int getX() const { return x; }
	int getY() const { return y; }
	void setPos(int, int);
	bool getColor() const { return color; }
	void setColor(bool);
	void setName(const char &n);
	char getName() const { return name; }
	int getMoveCount() const { return moveCount; }
	void increaseCount() { moveCount++; }

	virtual bool checkPos(int destX, int destY, Pedina *matrice[8][8]) = 0;

	friend std::ostream &operator<<(std::ostream &os, const Pedina &);

	Pedina(const Pedina &) = delete;
	Pedina &operator=(const Pedina &) = delete;
};
//_________________________________ SCACCHIERA ______________________________

class Scacchiera
{
private:
	Pedina *matrice[8][8];
	bool neroHasValidPositions();
	bool biancoHasValidPositions();

public:
	Scacchiera();
	~Scacchiera();

	Pedina *getPedina(int x, int y) const { return matrice[x][y]; }
	void setPedina(Pedina *);
	bool isEmpty(int x, int y) const { return matrice[x][y] == nullptr; }

	void changePiece(int, int, Pedina *);
	void setPtr(int, int);
	void move(Pedina *, int, int); // lancia InvalidPosition se la posizione non e' valida
								   // e InvalidMove se la mossa causa uno scacco al giocatore che l'ha eseguita

	bool isScaccoNero();
	bool isScaccoBianco();
	bool isScaccoMattoNero();
	bool isScaccoMattoBianco();
	int isPatta(std::vector<std::string> &); // restituisce 0 se non e'patta
											 //			  1 se bianco e' in stallo
											 //			  2 se nero e' in stallo
											 //			  3 se e' patta per mosse ripetute

	// MOSSE SPECIALI
	void replayPromo(Pedina *, std::string, bool);
	void promozione(std::ofstream &, Pedina *, bool, bool);
	void arrocco(int, int, int, int);
	void enPassant(Pedina *, int, int);
};

std::ostream &operator<<(std::ostream &os, const Scacchiera &);


class InvalidPosition
{
};

class InvalidMove
{
};

#endif