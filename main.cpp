#include <QCoreApplication>
#include <QDebug>
//#include <QRandomGenerator>
#include <iostream>
//#include <QVector>
#include <random>
#include <cstdlib>
#include <memory>
//using namespace std;

class GameOfLife{
private:
    double myarray;
    double myarray2;

public:
    void setArray(double x){
        myarray = x;
    }
    double getArray(){
        return myarray;
    }
};

/*void printBoard(int x,int y,int *z){
    for (int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            std::cout << z[i][j]<< " ";
        }std::cout << std::endl;
    }
}*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //a)

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0,9);
    int p = distribution(generator);


    srand (time(NULL));
    int min = 0;
    int max = 9;
    int number = std::rand() % (max + 1 - min) + min;  //Als funktion implementieren

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> uniform(0,9);

    int stat[30][30];

    std::cout << std::endl << "Vor dem Kopieren:" << std::endl;
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            stat[i][j] =  std::rand() % (max + 1 - min) + min;
            //std::cout << "stat[" << i << "][" << j << "]: ";

            std::cout << stat[i][j]<< " ";  //http://www.cplusplus.com/forum/beginner/42045/ für Matrix
        }std::cout << std::endl;
    }

    std::unique_ptr<int[]> dyn(new int[900]);  //Eindimensionales Array
    std::cout << std::endl << "Nach dem Kopieren:" << std::endl;

    int z = 0;
    for (int x = 0; x < 30; x++){
        for (int y = 0; y < 30; y++){
            dyn[z] = stat[x][y];
            //std::cout << "dyn[" << z << "]: ";
            std::cout << dyn[z] << " ";
            z++;
        }std::cout << std::endl;
    }

    //b)

    int mynumber;
    while (true) {
        std::cout << std::endl
                  << "1 fuer statisch, 2 fuer dynamisch, 3 fuers Kopieren, 4 fuer Matrix, Sonstiges zum Schliessen: " << std::endl;
        std::cin >> mynumber;
        if (mynumber == 1){
            for (int i = 0; i < 30; i++) {
                for (int j = 0; j < 30; j++) {
                    stat[i][j] =  std::rand() % (max + 1 - min) + min;
                }
            }
        }
        else if (mynumber == 2){
            std::unique_ptr<int[]> dyn(new int[900]);
        }
        else if (mynumber == 3){
            int row,column,dynnr = 0;
            for (row = 0; row < 30; row++){
                for (column = 0; column < 30; column++){
                    dyn[dynnr] = stat[row][column];
                    dynnr++;
                }
            }
        }
        else if (mynumber == 4){
            for (int q = 0; q < 30; q++){
                for(int w = 0; w < 30; w++){
                    std::cout << stat[q][w]<< " ";
                }std::cout << std::endl;
            }
            int l,m,n = 0;
            for (l;l < 30; l++){
                for (m; m < 30; m++){
                    std::cout << dyn[n] << " ";
                }std::cout << std::endl;
            }
        }
        else {
            break;
            //qApp->quit();
        }
    }

    //c)e)

    int zeile,spalte;
    std::cout << "Geben Sie die Anzahl der Zeilen und Spalten an(zB. 5 5): ";
    std::cin >> zeile >> spalte;

    int gameoflife[zeile][spalte];
    int gameoflife2[zeile][spalte];

    for (int i = 0; i < zeile; i++){
        for(int j = 0; j < spalte; j++){
            gameoflife[i][j] = 0;
        }
    }

    while (true){
        int zeil,spalt;
        std::string zustand;
        std::cout << "Koordinaten Eingabe(zB. lebend 1 2): ";
        std::cin >> zustand >> zeil >> spalt;  // std::noskipws >>
        std::cout << std::endl;

        if (zustand == "tot"){
            gameoflife[zeil][spalt] = 0;
        }
        else if (zustand == "lebend") {
            gameoflife[zeil][spalt] = 1;
        }
        else if (zustand != "tot" or zustand != "lebend" or zustand == "\n"){
            break;
        }
        //else if (std::cin.fail()){
        //    break;
        //}
        else if (zeil < 0 or zeil > zeile) {
            break;
        }
        else if (spalt < 0 or spalt > spalte) {
            break;
        }
        else {
            break;
        }
        for (int i = 0; i < zeile; i++){
            for (int j = 0; j < spalte; j++){
                std::cout << gameoflife[i][j] << "  ";
            }std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "1.Generation:" << std::endl;
    for (int i = 0; i < zeile; i++){
        for(int j = 0; j < spalte; j++){
            std::cout << gameoflife[i][j]<< "  ";
        }std::cout << std::endl;
    }

    //Kopiere gameoflife zu gameoflife2 bevor Zellen verändert werden
    for (int i = 0; i < zeile; i++){
        for (int j = 0; j < spalte; j++){
            gameoflife2[i][j] = gameoflife[i][j];
        }
    }

    for (int row = 0; row < zeile; row++){

        for(int column = 0; column < spalte; column++){

            int counter = 0;

            for (int i = -1; i < 2; i++) {

                for (int j = -1; j < 2; j++){
                    if (i == 0 && j == 0){
                        //do nothing
                    }
                    else if (gameoflife[(zeile+((row+i)%zeile))%zeile][(spalte+((column+j)%spalte))%spalte] == 1){
                        counter++;
                    }
                }
            }
            if (gameoflife[row][column] == 0){
                if (counter == 3){
                    gameoflife2[row][column] = 1;
                }
            }
            else if (gameoflife[row][column] == 1){

                if (counter < 2){
                    gameoflife2[row][column] = 0;
                }
                else if (counter == 2 or counter == 3){
                    gameoflife2[row][column] = 1;
                }
                else if (counter > 3){
                    gameoflife2[row][column] = 0;
                }
            }
        }
    }

    std::cout << std::endl << "Folgegeneration:" << std::endl;
    for (int i = 0; i < zeile; i++){
        for (int j = 0; j < spalte; j++){
            std::cout << gameoflife2[i][j] << "  ";
        }std::cout << std::endl;
    }


    //d)

    return a.exec();
}
