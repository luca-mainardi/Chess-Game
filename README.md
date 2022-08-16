Progetto Scacchi in C++ per corso di Laboratorio di Programmazione:

Comandi su console:

$cd build

$cmake ..

$make

In caso il "cmake .." non funzionasse perchè non trova il generatore corretto (a causa dell'implementazione su sistemi operativi differenti):

$rm CMakeCache.txt

$cmake -G "MinGW Makefiles" ..

$make

I file di log rispettivamente per la partita PC e CC sono presenti nella directory /build sotto forma di file logPC.txt e logCC.txt
E' importante che non vengano usati altri file .txt per il replay perchè sono generati in modo da contenere altre informazioni importanti quali per esempio le mosse speciali (file build/spec.txt).
L'eseguibile del replay non fa controlli sulla validita' delle mosse perchè si aspetta che le mosse provengano da una partita già valida.
Quando si inseriscono i file come argomento di riga di comando è necessario che non venga inserito il prefisso "./" per indicare la cartella corrente.
