// NTWI2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.

//INCLUDY

#include <iostream>
#include <vector>
#include <fstream>

#include "Classes.h"
#include "Functions.h"

//DEKLARACJE

//std::vector <Car> carVector;
std::fstream input;
int dimension, capacity;
std::vector <std::pair<int, int>> coord;
std::vector <int> demand;


int main()
{
    /*//testowanie klasy samochodowej
    carVector.push_back(Car("Mercedes",10));
    carVector.push_back(Car("BMW", -2));
    carVector.push_back(Car("VW"));

    for (int i = 0; i < carVector.size(); i++) {
        std::cout << "Model auta: " << carVector[i].getModel() << " Pojemnosc auta: " << carVector[i].getCapacity() << '\n';
    }*/

    input.open("A-n32-k5.vrp.txt",std::ios::in);

    if (input.is_open()) {
        std::string s;
        while (getline(input, s)) {
            if (s.find("DIMENSION")!=std::string::npos) {
                std::string dim_str = s.substr(12);
                dimension = std::stoi(dim_str);
            }else if (s.find("CAPACITY") != std::string::npos) {
                std::string cap_str = s.substr(11);
                capacity = std::stoi(cap_str);
            }else if (s == "NODE_COORD_SECTION ") {
                int x, y;
                for (int i = 0; i < dimension; i++) {
                    input >> x >> x >> y;
                    coord.push_back(std::make_pair(x,y));
                }
            }else if (s == "DEMAND_SECTION ") {
                int x;
                for (int i = 0; i < dimension; i++) {
                    input >> x >> x;
                    demand.push_back(x);
                }
            }
        }
        input.close();
    }
    // w wektorze coord siedzą koordy bez ID po prostu po kolei, a w wektorze demand tak samo siedzą zapotrzebowania konkretnych punktów
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
