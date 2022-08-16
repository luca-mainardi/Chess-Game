// Melissa Maistro

#include "../include/Scacchiera.h"
using namespace std;

/**
 * @brief costruttore di pedina
 *
 * @param j ascissa della cella
 * @param i ordinata della cella
 * @param c colore della pedina (true per bianco, false per nero)
 * @param name iniziale del nome della pedina (minuscolo per bianco, maiuscolo per nero)
 */
Pedina::Pedina(int j, int i, bool c, char name)
{
	x = j;
	y = i;
	color = c;
	setName(name);
	moveCount = 0;
}

/**
 * @brief imposta la posizione della pedina
 *
 * @param j ascissa della cella
 * @param i ordinata della cella
 */
void Pedina::setPos(int j, int i)
{
	x = j;
	y = i;
}

/**
 * @brief imposta il colore della pedina
 *
 * @param c colore della pedina (true per bianco, false per nero)
 */
void Pedina::setColor(bool c)
{
	color = c;
}
/**
 * @brief imposta il tipo di pedina
 *
 * @param n iniziale del nome della pedina (minuscolo per bianco, maiuscolo per nero)
 */
void Pedina::setName(const char &n)
{
	if (!getColor())
		name = toupper(n);
	else
		name = n;
}

ostream &operator<<(ostream &os, const Pedina &ped)
{
	os << ped.getName();
	return os;
}
