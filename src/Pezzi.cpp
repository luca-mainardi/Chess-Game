// Melissa Maistro

#include "../include/Pezzi.h"
#include "../include/Scacchiera.h"
#include <iostream>
using namespace std;

//_______________________________________PEDONE___________________________________________

/**
 * @brief controlla se il pedone puo' muoversi nella posizione data
 * 
 * @param j ascissa della cella
 * @param i ordinata della cella
 * @param matrice matrice della scacchiera contenente le pedine
 * @return true se puo' muoversi nella cella
 * @return false altrimenti
 */
bool Pedone::checkPos(int j, int i, Pedina *matrice[8][8])  
{
    if (getColor()) // se bianco
    {
        if (j == getX() && (i == getY() - 1)) // se avanti di 1
        {
            if (!emptyBox(matrice, j, i)) // se c'e' una pedina non puo'
                return false;
            return true;
        }
        if ((getMoveCount() == 0) && j == getX() && i == getY() - 2) // se prima mossa e avanti di 2
        {
            if (!emptyBox(matrice, j, i) || !emptyBox(matrice, j, getY() - 1))
                return false; // se c'e' una pedina nella prima o seconda cella non puo'
            return true;
        }
        if ((i == getY() - 1 && (j == getX() - 1 || j == getX() + 1))) // se nelle due celle diagonali
        {
            if (!emptyBox(matrice, j, i) && !(matrice[j][i]->getColor())) // solo se c'e' una pedina nera
                return true;
            return false;
        }
    }
    // se nero
    else
    {
        if (j == getX() && (i == getY() + 1)) // se avanti di 1
        {
            if (!emptyBox(matrice, j, i)) // se c'e' una pedina non puo'
                return false;
            return true;
        }
        if ((getMoveCount() == 0) && j == getX() && i == getY() + 2) // se prima mossa e avanti di 2
        {
            if (!emptyBox(matrice, j, i) || !emptyBox(matrice, j, getY() + 1))
                return false; // se c'e' una pedina nella prima o seconda cella non puo'
            return true;
        }
        if ((i == getY() + 1 && (j == getX() - 1 || j == getX() + 1))) // se nelle due celle diagonali
        {
            if (!emptyBox(matrice, j, i) && matrice[j][i]->getColor()) // solo se c'e' una pedina bianca
                return true;
            return false;
        }
    }
    return false; // ritorna false se non puo' spostarsi nella casella
}

//_______________________________________CAVALLO___________________________________________
/**
 * @brief controlla se il cavallo puo' muoversi nella posizione data
 * 
 * @param j ascissa della cella
 * @param i ordinata della cella
 * @param matrice matrice della scacchiera contenente le pedine
 * @return true se puo' muoversi nella cella
 * @return false altrimenti
 */
bool Cavallo::checkPos(int j, int i, Pedina *matrice[8][8]) // si sposta a L in tutte le direzioni anche se ci sono pedine
{                                                           // j colonne, i righe

    // c'e' una pedina dello stesso colore
    if (!emptyBox(matrice, j, i) && (matrice[j][i]->getColor() == getColor()))
        return false;

    if (j == getX() - 1 && (i == getY() - 2 || i == getY() + 2))
        return true;
    if (j == getX() - 2 && (i == getY() - 1 || i == getY() + 1))
        return true;
    if (j == getX() + 1 && (i == getY() - 2 || i == getY() + 2))
        return true;
    if (j == getX() + 2 && (i == getY() - 1 || i == getY() + 1))
        return true;
    return false;
}

//_______________________________________ALFIERE___________________________________________
/**
 * @brief controlla se l'alfiere puo' muoversi nella posizione data
 * 
 * @param j ascissa della cella
 * @param i ordinata della cella
 * @param matrice matrice della scacchiera contenente le pedine
 * @return true se puo' muoversi nella cella
 * @return false altrimenti
 */
bool Alfiere::checkPos(int j, int i, Pedina *matrice[8][8]) // si muove nelle 4 diagonali
{
    for (int n = 1; n < 8; n++) // diagonale nord-ovest
    {
        if (!checkBoundaries(getX() - n, getY() - n))
            break;
        if (!emptyBox(matrice, getX() - n, getY() - n) && matrice[getX() - n][getY() - n]->getColor() == getColor())
            break; // se c'e' una pedina ed e' del suo colore non va oltre
        if (!emptyBox(matrice, getX() - n, getY() - n) && matrice[getX() - n][getY() - n]->getColor() != getColor())
        {
            if (j == getX() - n && i == getY() - n)
                return true;
            break;
        }
        if (j == getX() - n && i == getY() - n)
            return true;
    }
    for (int n = 1; n < 8; n++) // diagonale sud-ovest
    {
        if (!checkBoundaries(getX() - n, getY() + n))
            break;
        if (!emptyBox(matrice, getX() - n, getY() + n) && (matrice[getX() - n][getY() + n]->getColor() == getColor()))
            break;
        if (!emptyBox(matrice, getX() - n, getY() + n) && matrice[getX() - n][getY() + n]->getColor() != getColor())
        {
            if (j == getX() - n && i == getY() + n)
                return true;
            break;
        }
        if (j == getX() - n && i == getY() + n)
            return true;
    }
    for (int n = 1; n < 8; n++) // diagonale sud-est
    {
        if (!checkBoundaries(getX() + n, getY() + n))
            break;
        if (!emptyBox(matrice, getX() + n, getY() + n) && (matrice[getX() + n][getY() + n]->getColor() == getColor()))
            break;
        if (!emptyBox(matrice, getX() + n, getY() + n) && matrice[getX() + n][getY() + n]->getColor() != getColor())
        {
            if (j == getX() + n && i == getY() + n)
                return true;
            break;
        }
        if (j == getX() + n && i == getY() + n)
            return true;
    }
    for (int n = 1; n < 8; n++) // diagonale nord-est
    {
        if (!checkBoundaries(getX() + n, getY() - n))
            break;
        if (!emptyBox(matrice, getX() + n, getY() - n) && (matrice[getX() + n][getY() - n]->getColor() == getColor()))
            break;
        if (!emptyBox(matrice, getX() + n, getY() - n) && matrice[getX() + n][getY() - n]->getColor() != getColor())
        {
            if (j == getX() + n && i == getY() - n)
                return true;
            break;
        }
        if (j == getX() + n && i == getY() - n)
            return true;
    }
    return false;
}

//_______________________________________TORRE___________________________________________
/**
 * @brief controlla se la torre puo' muoversi nella posizione data
 * 
 * @param j ascissa della cella
 * @param i ordinata della cella
 * @param matrice matrice della scacchiera contenente le pedine
 * @return true se puo' muoversi nella cella
 * @return false altrimenti
 */
bool Torre::checkPos(int j, int i, Pedina *matrice[8][8])
{
    for (int n = 1; n < 8; n++) // sinistra
    {
        if (i != getY()) // se riga diversa non puo' essere a sx o dx
            break;
        if (!checkBoundaries(getX() - n, getY())) // controlla se va fuori da scacchiera
            break;
        if (!emptyBox(matrice, getX() - n, i) && (matrice[getX() - n][i]->getColor() == getColor()))
            break; // se c'e' pedina del suo stesso colore non puo' andare oltre
        if (!emptyBox(matrice, getX() - n, i) && (matrice[getX() - n][i]->getColor() != getColor()))
        { // se c'e' una pedina dell'altro colore
            if (j == getX() - n)
                return true;
            break;
        }
        if (j == getX() - n) // se non trova nessuna pedina
            return true;
    }
    for (int n = 1; n < 8; n++) // destra
    {
        if (i != getY())
            break;
        if (!checkBoundaries(getX() + n, getY()))
            break;
        if (!emptyBox(matrice, getX() + n, i) && (matrice[getX() + n][i]->getColor() == getColor()))
            break;
        if (!emptyBox(matrice, getX() + n, i) && (matrice[getX() + n][i]->getColor() != getColor()))
        { // se c'e' una pedina dell'altro colore
            if (j == getX() + n)
                return true;
            break;
        }
        if (j == getX() + n)
            return true;
    }
    for (int n = 1; n < 8; n++) // su
    {
        if (j != getX()) // se colonna diversa non puo' essere su o giu
            break;
        if (!checkBoundaries(getX(), getY() - n))
            break;
        if (!emptyBox(matrice, j, getY() - n) && (matrice[j][getY() - n]->getColor() == getColor()))
            break;
        if (!emptyBox(matrice, j, getY() - n) && (matrice[j][getY() - n]->getColor() != getColor()))
        { // se c'e' una pedina dell'altro colore
            if (i == getY() - n)
                return true;
            break;
        }
        if (i == getY() - n)
            return true;
    }
    for (int n = 1; n < 8; n++) // giu
    {
        if (j != getX())
            break;
        if (!checkBoundaries(getX(), getY() + n))
            break;
        if (!emptyBox(matrice, j, getY() + n) && (matrice[j][getY() + n]->getColor() == getColor()))
            break;
        if (!emptyBox(matrice, j, getY() + n) && (matrice[j][getY() + n]->getColor() != getColor()))
        { // se c'e' una pedina dell'altro colore
            if (i == getY() + n)
                return true;
            break;
        }
        if (i == getY() + n)
            return true;
    }
    return false;
}

//_______________________________________RE___________________________________________
/**
 * @brief controlla se il re puo' muoversi nella posizione data
 * 
 * @param j ascissa della cella
 * @param i ordinata della cella
 * @param matrice matrice della scacchiera contenente le pedine
 * @return true se puo' muoversi nella cella
 * @return false altrimenti
 */
bool Re::checkPos(int j, int i, Pedina *matrice[8][8])
{
    if (j == getX() && (i == getY() - 1 || i == getY() + 1))
    {
        if (!emptyBox(matrice, j, i) && (matrice[j][i]->getColor() == getColor()))
            return false;
        return true;
    }
    if (j == getX() - 1 && (i == getY() || i == getY() - 1 || i == getY() + 1))
    {
        if (!emptyBox(matrice, j, i) && (matrice[j][i]->getColor() == getColor()))
            return false;
        return true;
    }
    if (j == getX() + 1 && (i == getY() || i == getY() - 1 || i == getY() + 1))
    {
        if (!emptyBox(matrice, j, i) && (matrice[j][i]->getColor() == getColor()))
            return false;
        return true;
    }
    return false;
}

// //_______________________________________REGINA___________________________________________
/**
 * @brief controlla se la regina puo' muoversi nella posizione data
 * 
 * @param j ascissa della cella
 * @param i ordinata della cella
 * @param matrice matrice della scacchiera contenente le pedine
 * @return true se puo' muoversi nella cella
 * @return false altrimenti
 */
bool Regina::checkPos(int j, int i, Pedina *matrice[8][8])
{
    for (int n = 1; n < 8; n++) // diagonale nord-ovest
    {
        if (!checkBoundaries(getX() - n, getY() - n))
            break;
        if (!emptyBox(matrice, getX() - n, getY() - n) && matrice[getX() - n][getY() - n]->getColor() == getColor())
            break; // se c'e' una pedina ed e' del suo colore non va oltre
        if (!emptyBox(matrice, getX() - n, getY() - n) && matrice[getX() - n][getY() - n]->getColor() != getColor())
        {
            if (j == getX() - n && i == getY() - n)
                return true;
            break;
        }
        if (j == getX() - n && i == getY() - n)
            return true;
    }
    for (int n = 1; n < 8; n++) // diagonale sud-ovest
    {
        if (!checkBoundaries(getX() - n, getY() + n))
            break;
        if (!emptyBox(matrice, getX() - n, getY() + n) && (matrice[getX() - n][getY() + n]->getColor() == getColor()))
            break;
        if (!emptyBox(matrice, getX() - n, getY() + n) && matrice[getX() - n][getY() + n]->getColor() != getColor())
        {
            if (j == getX() - n && i == getY() + n)
                return true;
            break;
        }
        if (j == getX() - n && i == getY() + n)
            return true;
    }
    for (int n = 1; n < 8; n++) // diagonale sud-est
    {
        if (!checkBoundaries(getX() + n, getY() + n))
            break;
        if (!emptyBox(matrice, getX() + n, getY() + n) && (matrice[getX() + n][getY() + n]->getColor() == getColor()))
            break;
        if (!emptyBox(matrice, getX() + n, getY() + n) && matrice[getX() + n][getY() + n]->getColor() != getColor())
        {
            if (j == getX() + n && i == getY() + n)
                return true;
            break;
        }
        if (j == getX() + n && i == getY() + n)
            return true;
    }
    for (int n = 1; n < 8; n++) // diagonale nord-est
    {
        if (!checkBoundaries(getX() + n, getY() - n))
            break;
        if (!emptyBox(matrice, getX() + n, getY() - n) && (matrice[getX() + n][getY() - n]->getColor() == getColor()))
            break;
        if (!emptyBox(matrice, getX() + n, getY() - n) && matrice[getX() + n][getY() - n]->getColor() != getColor())
        {
            if (j == getX() + n && i == getY() - n)
                return true;
            break;
        }
        if (j == getX() + n && i == getY() - n)
            return true;
    }
    for (int n = 1; n < 8; n++) // sinistra
    {
        if (i != getY()) // se riga diversa non puo' essere a sx o dx
            break;
        if (!checkBoundaries(getX() - n, getY())) // controlla se va fuori da scacchiera
            break;
        if (!emptyBox(matrice, getX() - n, i) && (matrice[getX() - n][i]->getColor() == getColor()))
            break; // se c'e' pedina del suo stesso colore non puo' andare oltre
        if (!emptyBox(matrice, getX() - n, i) && (matrice[getX() - n][i]->getColor() != getColor()))
        { // se c'e' una pedina dell'altro colore
            if (j == getX() - n)
                return true;
            break;
        }
        if (j == getX() - n) // se non trova nessuna pedina
            return true;
    }
    for (int n = 1; n < 8; n++) // destra
    {
        if (i != getY())
            break;
        if (!checkBoundaries(getX() + n, getY()))
            break;
        if (!emptyBox(matrice, getX() + n, i) && (matrice[getX() + n][i]->getColor() == getColor()))
            break;
        if (!emptyBox(matrice, getX() + n, i) && (matrice[getX() + n][i]->getColor() != getColor()))
        { // se c'e' una pedina dell'altro colore
            if (j == getX() + n)
                return true;
            break;
        }
        if (j == getX() + n)
            return true;
    }
    for (int n = 1; n < 8; n++) // su
    {
        if (j != getX()) // se colonna diversa non puo' essere su o giu
            break;
        if (!checkBoundaries(getX(), getY() - n))
            break;
        if (!emptyBox(matrice, j, getY() - n) && (matrice[j][getY() - n]->getColor() == getColor()))
            break;
        if (!emptyBox(matrice, j, getY() - n) && (matrice[j][getY() - n]->getColor() != getColor()))
        { // se c'e' una pedina dell'altro colore
            if (i == getY() - n)
                return true;
            break;
        }
        if (i == getY() - n)
            return true;
    }
    for (int n = 1; n < 8; n++) // giu
    {
        if (j != getX())
            break;
        if (!checkBoundaries(getX(), getY() + n))
            break;
        if (!emptyBox(matrice, j, getY() + n) && (matrice[j][getY() + n]->getColor() == getColor()))
            break;
        if (!emptyBox(matrice, j, getY() + n) && (matrice[j][getY() + n]->getColor() != getColor()))
        { // se c'e' una pedina dell'altro colore
            if (i == getY() + n)
                return true;
            break;
        }
        if (i == getY() + n)
            return true;
    }
    return false;
}

//-------------------------------------------- HELPER FUNCTIONS --------------------------------------------
/**
 * @brief controlla se l'indice e' fuori dalla scacchiera
 * 
 * @param j ascissa della cella
 * @param i ordinata della cella
 * @return true se l'indice e' interno alla scacchiera
 * @return false altrimenti
 */
bool checkBoundaries(int j, int i)  
{
    return (i >= 0 && i <= 7 && j >= 0 && j <= 7);
}
/**
 * @brief controlla se la cella di coordinate (x,y) non contiene nessuna pedina
 * 
 * @param matrice matrice della scacchiera contenente le pedine
 * @param x ascissa della cella
 * @param y ordinata della cella
 * @return true se cella e' vuota
 * @return false se cella non e' vuota
 */
bool emptyBox(Pedina *matrice[8][8], int x, int y)
{
    return matrice[x][y] == nullptr;
}