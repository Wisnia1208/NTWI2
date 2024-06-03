// NTWI2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string>
#include <vector>

class Car {
protected:
    std::string model="";
    int capacity = 500;
public:
    void setModel(std::string name) {
        model = name;
    }
    std::string getModel() {
        return model;
    }

    void setCapacity(int x) {
        try {
            if (x >= 0) {
                capacity = x;
            }
            else {
                throw(x);
            }
        }
        catch (int e){
            std::cout << "error setCapacity() - input: " << e << " is below 0\n";
        }
    }
    int getCapacity() {
        return capacity;
    }

    Car(std::string name, int cap) {
        model = name;
            if (cap >= 0) {
                capacity = cap;
            }
            else { 
                std::cout << "incorrect input CAPACITY\n";
            }
    }

    Car(std::string name) {
        model = name;
    }

    ~Car() {}
};

std::vector <Car> carVector;

int main()
{
    carVector.push_back(Car("Mercedes",10));
    carVector.push_back(Car("BMW", -2));
    carVector.push_back(Car("VW"));

    for (int i = 0; i < carVector.size(); i++) {
        std::cout << "Model auta: " << carVector[i].getModel() << " Pojemnosc auta: " << carVector[i].getCapacity() << '\n';
    }
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
