// Melissa Maistro

#ifndef PEZZI_H
#define PEZZI_H
#include "Scacchiera.h"

//_______________________________________PEDONE___________________________________________
class Pedone : public Pedina
{
public:
    Pedone(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    virtual ~Pedone() {}
    bool checkPos(int destX, int destY, Pedina *matrice[8][8]) override;
};
//_______________________________________CAVALLO___________________________________________
class Cavallo : public Pedina
{
public:
    Cavallo(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    virtual ~Cavallo() {}
    bool checkPos(int destX, int destY, Pedina *matrice[8][8]) override;
};
//_______________________________________ALFIERE___________________________________________
class Alfiere : public Pedina
{
public:
    Alfiere(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    virtual ~Alfiere() {}
    bool checkPos(int destX, int destY, Pedina *matrice[8][8]) override;
};
//_______________________________________TORRE___________________________________________
class Torre : public Pedina
{
public:
    Torre(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    virtual ~Torre() {}
    bool checkPos(int destX, int destY, Pedina *matrice[8][8]) override;
};
//_______________________________________RE___________________________________________
class Re : public Pedina
{
public:
    Re(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    virtual ~Re() {}
    bool checkPos(int destX, int destY, Pedina *matrice[8][8]) override;
};
//_______________________________________REGINA___________________________________________
class Regina : public Pedina
{
public:
    Regina(int l, int n, bool color, char na) : Pedina(l, n, color, na) {}
    virtual ~Regina() {}
    bool checkPos(int destX, int destY, Pedina *matrice[8][8]) override;
};

// HELPER FUNCTIONS
bool checkBoundaries(int i, int j);
bool emptyBox(Pedina *matrice[8][8], int x, int y);

#endif