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
int numTrucks;
std::vector <Color> rainbow = rainbow_colors();

 //do zmieniania jak na razie niestety
//std::string fileName = "A-n32-k5.vrp.txt"; //to też
std::string fileName = "A-n80-k10.vrp.txt";


int main()
{
    /*//testowanie klasy samochodowej
    carVector.push_back(Car("Mercedes",10));
    carVector.push_back(Car("BMW", -2));
    carVector.push_back(Car("VW"));

    for (int i = 0; i < carVector.size(); i++) {
        std::cout << "Model auta: " << carVector[i].getModel() << " Pojemnosc auta: " << carVector[i].getCapacity() << '\n';
    }*/

    input.open(fileName,std::ios::in);

    if (input.is_open()) {
        std::string s;
        while (getline(input, s)) {
            if (s.find("DIMENSION")!=std::string::npos) {
                std::string dim_str = s.substr(12);
                dimension = std::stoi(dim_str);
            }else if (s.find("No of trucks: ") != std::string::npos){
                std::string NT_str = s.substr((s.find("No of trucks: ") + 14), (s.find(", Optimal value: ")-(s.find("No of trucks: ") + 14)));
                numTrucks = std::stoi(NT_str);
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
    std::cout << std::endl << std::endl << std::endl;
    std::vector<std::vector<Point>> routes = solveVRP(nodes, capacity, numTrucks);

    float sum = 0;
    double max = DBL_MIN;
    double min = DBL_MAX;
    for (int i = 0; i < routes.size(); ++i) {
        std::cout << "Truck " << i + 1 << " route: ";
        for (Point& p : routes[i]) {
            std::cout << "(" << p.x << ", " << p.y << ") ";
        }
        std::cout << std::endl;
        double result = calculateRouteLength(routes[i]);
        if (result > max) {
            max = result;
        }
        if (result < min) {
            min = result;
        }
        std::cout << "length of this route: " << result << std::endl;
        sum += calculateRouteLength(routes[i]);
    }

    std::cout << std::endl << "Lenght of all routes: " << sum << std::endl;
    std::cout << "min - max difference: " << max - min << std::endl;

    GLFWwindow* window;

    /* Initialize the library */
    if (!initOpenGL(&window, window_width, window_height, "2D Points Graph")) {
        return -1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glPointSize(5.0f);
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

        for (int i = 0; i < routes.size(); ++i) {
            for (int j = 0; j < routes[i].size()-1;j++) {
                drawLine(routes[i][j].x, routes[i][j].y, routes[i][j+1].x, routes[i][j+1].y, rainbow[i%rainbow.size()]);
            }
        }

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
