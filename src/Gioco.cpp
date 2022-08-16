// Baggio Davide

#include <string.h>
#include "../include/Scacchiera.h"
#include "../include/Pezzi.h"
#include "../include/Game.h"

using namespace std;

/**
 * @brief Entry point dell'eseguibile Scacchiera. Gestisce le partite
 *
 * @param argc Accetta al massimo 2 argomenti: l'eseguibile e gli argomenti da riga di comando
 *             pc: per le partite giocatore vs PC
 *             cc: per le partite PC vs PC
 * @param argv
 * @return int 0.
 */
int main(int argc, char *argv[])
{
    srand(time(NULL));

    Game game = Game();

    // Se si avvia Scacchiera senza argomenti
    if (argc <= 1)
    {
        cout << "[Error] Not enough arguments. Type: " << endl
             << "\t pc: to play vs computer." << endl
             << "\t cc: to watch a match computer vs computer." << endl;
        return 0;
    }

    // Se si avvia Scacchiera con argomenti errati
    else if (strcmp(argv[1], "pc") != 0 && strcmp(argv[1], "cc") != 0)
    {
        cout << "[Error] Incorrect arguments. Type: " << endl
             << "\t pc: to play vs computer." << endl
             << "\t cc: to watch a match computer vs computer." << endl;
        return 0;
    }

    //---------------------------------- Se si avvia Scacchiera pc (Partita Giocatore vs PC) ----------------------------------
    else if (strcmp(argv[1], "pc") == 0)
    {
        cout << "Partita giocatore (Bianco) vs computer (Nero)\n";
        cout << "Per giocare inserire la posizione di cella iniziale e finale separati da uno spazio. Es: A2 C3\n";

        ofstream outputFile("logPC.txt");
        ofstream spec("specPC.txt");
        outputFile.clear();
        spec.clear();

        game.startPC(outputFile, spec);

        outputFile.close();
        spec.close();
    }
    //---------------------------------- Se si avvia Scacchiera cc (Partita PC vs PC) ----------------------------------
    else
    {
        cout << "Partita computer vs computer\n";

        ofstream outputFile("logCC.txt");
        ofstream spec("specCC.txt");
        outputFile.clear();
        spec.clear();

        game.startCC(outputFile, spec);

        outputFile.close();
        spec.close();
    }
    return 0;
}

/**
 * @brief Secondo Entry point per debug.
 *
 * @return int 0.
 */
int main2()
{
    /* Scacchiera s{};
    cout << "Scacchiera iniziale: \n";
    cout << s << "\n"; */

    //----------------------------------- test hasValidPositions -----------------------------------
    /* if (s.neroHasValidPositions())
    {
        cout << "Nero ha posizioni valide\n"
             << s << endl;
    }
    if (s.biancoHasValidPositions())
    {
        cout << "Bianco ha posizioni valide\n"
             << s << endl;
    } */

    //----------------------------------- test per scacco matto -----------------------------------
    // for(int i = 0; i<8; i++)
    // {
    //     for(int j= 0; j<8; j++)
    //     {
    //         s.setPtr(j,i);
    //     }
    // }

    // Re* reN = new Re(2,0,false,'R');
    // Re* reB = new Re(2,2,true,'r');
    // Regina* regB = new Regina(7,0,true,'d');

    // s.setPedina(reN);
    // s.setPedina(reB);
    // s.setPedina(regB);

    //  cout << s <<endl;

    // bool scacco = s.isScaccoMattoNero();

    // cout<< "ScaccoMatto:" <<scacco <<endl;

    //----------------------------------- test enpassant -----------------------------------
    // Pedina *p1 = s.getPedina(5, 6);
    // s.move(p1, 5, 4);
    // s.move(p1, 5, 3);

    // cout << s << "\n";

    // Pedina *p2 = s.getPedina(4, 1);
    // s.move(p2, 4, 3);

    // cout << s << "\n";

    // s.enPassant(p1, 4, 3);

    //----------------------------------- test patta per stallo -----------------------------------
    // for(int i = 0; i<8; i++)
    // {
    //     for(int j= 0; j<8; j++)
    //     {
    //         s.setPtr(j,i);
    //     }
    // }

    // Re* reN = new Re(7,1,false,'R');
    // Re* reB = new Re(5,2,true,'r');
    // Regina* regB = new Regina(5,0,true,'d');
    // //Torre* torreN = new Torre(4,1,false,'T');

    // s.setPedina(reN);
    // s.setPedina(reB);
    // s.setPedina(regB);

    // cout << s <<endl;

    // vector<string> v;
    // v.push_back("B1");
    // v.push_back("C2");
    // if(s.isPatta(v))
    //     cout << "PATTA"<<endl;
    // else cout << "NON PATTA"<<endl;

    //----------------------------------- test patta per mosse ripetute -----------------------------------
    // vector<string> v = {"B1 C2","D1 E2","C2 B1","E2 D1","B1 C2","D1 E2","C2 B1","E2 D1","B1 C2","D1 E2","C2 B1","E2 D1"};
    // if(s.isPatta(v))
    //     cout << "PATTA"<<endl;
    // else cout << "NON PATTA"<<endl;

    // cout << s;
    return 0;
}