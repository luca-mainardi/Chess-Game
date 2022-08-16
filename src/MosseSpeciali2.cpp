//Luca Mainardi

#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"
using namespace std;

/**
 * @brief gestisce l'arrocco: si esegue indicando prima la posizione del re, poi della torre con cui
 * si vuole fare l'arrocco
 * 
 * @param xi ascissa iniziale (del re)
 * @param yi ordinata iniziale (del re)
 * @param xf ascissa finale (della torre)
 * @param yf ordinata finale (della torre)
 * @throws invalid position se le coordinate non sono valide
 */
void Scacchiera::arrocco(int xi, int yi, int xf, int yf)
{
	if (xi == 4 && yi == 0 && yf == 0) // arrocco del nero
	{
		if (xf == 0) // arrocco lungo
		{
			// verifica condizioni
			if (isScaccoNero()) // arrocco non si puo' fare se re e' sotto scacco
			{
				throw InvalidPosition();
			}
			if (isEmpty(xi, yi) || isEmpty(xf, yf)) // se una delle due caselle e' vuota
			{
				throw InvalidPosition();
			}
			Pedina *re = getPedina(xi, yi);
			Pedina *torre = getPedina(xf, yf);
			if (re->getMoveCount() != 0 || torre->getMoveCount() != 0) // se le pedine hanno gia fatto movimenti non si puo' arroccare
			{
				throw InvalidPosition();
			}
			if (!isEmpty(1, 0) || !isEmpty(2, 0) || !isEmpty(3, 0)) // se una delle celle tra re e torre e' occupata non si puo' arroccare
			{
				throw InvalidPosition();
			}
			// esegue arrocco
			move(re, 3, 0); // move controlla anche se re va sotto scacco (lancia InvalidPosition)
			move(re, 2, 0);
			torre->setPos(3, 0);
			setPedina(torre);
			setPtr(0, 0);
			return;
		}
		else if (xf == 7) // arrocco corto
		{
			// verifica condizioni
			if (isScaccoNero()) // arrocco non si puo' fare se re e' sotto scacco
			{
				throw InvalidPosition();
			}
			if (isEmpty(xi, yi) || isEmpty(xf, yf)) // se una delle due caselle e' vuota
			{
				throw InvalidPosition();
			}
			Pedina *re = getPedina(xi, yi);
			Pedina *torre = getPedina(xf, yf);
			if (re->getMoveCount() != 0 || torre->getMoveCount() != 0) // se le pedine hanno gia fatto movimenti non si puo' arroccare
			{
				throw InvalidPosition();
			}
			if (!isEmpty(5, 0) || !isEmpty(6, 0)) // se una delle celle tra re e torre e' occupata non si puo' arroccare
			{
				throw InvalidPosition();
			}
			// esegue arrocco
			move(re, 5, 0); // move controlla anche se re va sotto scacco (lancia InvalidPosition)
			move(re, 6, 0);
			torre->setPos(5, 0);
			setPedina(torre);
			setPtr(7, 0);
			return;
		}
		else // altre xf non valide
		{
			throw InvalidPosition();
		}
	}
	else if (xi == 4 && yi == 7 && yf == 7) // arrocco del bianco
	{
		if (xf == 0) // arrocco lungo
		{
			// verifica condizioni
			if (isScaccoBianco()) // arrocco non si puo' fare se re e' sotto scacco
			{
				throw InvalidPosition();
			}
			if (isEmpty(xi, yi) || isEmpty(xf, yf)) // se una delle due caselle e' vuota
			{
				throw InvalidPosition();
			}
			Pedina *re = getPedina(xi, yi);
			Pedina *torre = getPedina(xf, yf);
			if (re->getMoveCount() != 0 || torre->getMoveCount() != 0) // se le pedine hanno gia fatto movimenti non si puo' arroccare
			{
				throw InvalidPosition();
			}
			if (!isEmpty(1, 7) || !isEmpty(2, 7) || !isEmpty(3, 7)) // se una delle celle tra re e torre e' occupata non si puo' arroccare
			{
				throw InvalidPosition();
			}
			// esegue arrocco
			move(re, 3, 7); // move controlla anche se re va sotto scacco (lancia InvalidPosition)
			move(re, 2, 7);
			torre->setPos(3, 7);
			setPedina(torre);
			setPtr(0, 7);
			return;
		}
		else if (xf == 7) // arrocco corto
		{
			// verifica condizioni
			if (isScaccoBianco()) // arrocco non si puo' fare se re e' sotto scacco
			{
				throw InvalidPosition();
			}
			if (isEmpty(xi, yi) || isEmpty(xf, yf)) // se una delle due caselle e' vuota
			{
				throw InvalidPosition();
			}
			Pedina *re = getPedina(xi, yi);
			Pedina *torre = getPedina(xf, yf);
			if (re->getMoveCount() != 0 || torre->getMoveCount() != 0) // se le pedine hanno gia fatto movimenti non si puo' arroccare
			{
				throw InvalidPosition();
			}
			if (!isEmpty(5, 7) || !isEmpty(6, 7)) // se una delle celle tra re e torre e' occupata non si puo' arroccare
			{
				throw InvalidPosition();
			}
			// esegue arrocco
			move(re, 5, 7); // move controlla anche se re va sotto scacco (lancia InvalidPosition)
			move(re, 6, 7);
			torre->setPos(5, 7);
			setPedina(torre);
			setPtr(7, 7);
			return;
		}
		else
		{
			throw InvalidPosition();
		}
	}
	else // tutti i casi non validi
	{
		throw InvalidPosition();
	}
}