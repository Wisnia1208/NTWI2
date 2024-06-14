// NTWI2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.

//INCLUDY nie zapominaj o tych w Functions.h!!!

#include <fstream>

#include <windows.h>

#include "Classes.h"
#include "Functions.h"

//DEKLARACJE



//std::vector <Car> carVector;
std::fstream input;
int dimension, capacity;
std::vector <Point> nodes;
int window_height = 800, window_width = 800;


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
                Point p;
                for (int i = 0; i < dimension; i++) {
                    input >> x >> x >> y;
                    p.x = x;
                    p.y = y;
                    p.demand = 0;
                    nodes.push_back(p);
                }
            }else if (s == "DEMAND_SECTION ") {
                int x;
                for (int i = 0; i < dimension; i++) {
                    input >> x >> x;
                    nodes[i].demand = x;
                }
            }
        }
        input.close();
    }
    // w wektorze nodes siedzą koordy bez ID po prostu po kolei, a w wektorze demand tak samo siedzą zapotrzebowania konkretnych punktów
    for (const auto& i : nodes) {
        std::cout << i.x << " " << i.y << " - " << i.demand << std::endl;
    }
    //wypis tych punktów

    //rozw
    int truckCapacity = 100;
    int numTrucks = 5;
    std::cout << std::endl << std::endl << std::endl;
    std::vector<std::vector<Point>> routes = solveVRP(nodes, truckCapacity, numTrucks);
    for (int i = 0; i < routes.size(); ++i) {
        std::cout << "Truck " << i + 1 << " route: ";
        for (Point& p : routes[i]) {
            std::cout << "(" << p.x << ", " << p.y << ") ";
        }
        std::cout << std::endl;
    }

    GLFWwindow* window;

    /* Initialize the library */
    if (!initOpenGL(&window, window_width, window_height, "2D Points Graph")) {
        return -1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glPointSize(5.0f);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        drawAxes();
        // Rysowanie punktów
        //glColor3f(1.0f, 0.0f, 0.0f); //czerwony
        drawPoints(nodes);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
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
