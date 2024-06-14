#include "Functions.h"

void drawPoints(const std::vector<Point>& points) {
    //glBegin(GL_POINTS);
    int segments = 30;
    for (const auto& point : points) {
        float x = point.x;
        float y = point.y;
        float radius = 0.5f;
        glColor3f(1.0f, 0.0f, 0.0f);
        /*
        float radius = point.demand/5; // Promie� okr�gu punktu
        if (point.demand < 10) {
            if (point.demand == 0){
                glColor3f(0.0f, 0.5f, 1.0f);
                radius = 1.0f;
            }
            else {
                glColor3f(0.0f, 1.0f, 0.0f);
            }
            
        }
        else if (point.demand < 20) {
            glColor3f(1.0f, 1.0f, 0.0f);
            radius /= 2;
        }
        else if (point.demand < 30) {
            glColor3f(1.0f, 0.0f, 0.0f);
            radius /= 3;
        }
        else {
            glColor3f(1.0f, 0.0f, 1.0f);
        }
        */
        // Rysowanie okr�gu jako wielok�ta
        drawCircle(x, y, radius, segments);
    }
    //glEnd();
}

bool initOpenGL(GLFWwindow** window, int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!*window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(*window);

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(1.0, 100.0, 1.0, 100.0, -1.0, 1.0); // Zakres wsp�rz�dnych od 1 do 100
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return true;
}

void drawAxes() {
    glColor3f(1.0f, 1.0f, 1.0f); // Bia�e linie osi

    // O� X
    glBegin(GL_LINES);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(100.0f, 1.0f);
    glEnd();

    // O� Y
    glBegin(GL_LINES);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, 100.0f);
    glEnd();

    // Podzia�ka na osi X
    glBegin(GL_LINES);
    for (int i = 10; i <= 100; i += 10) {
        glVertex2f(i, 0.5f);
        glVertex2f(i, 1.5f);
    }
    glEnd();

    // Podzia�ka na osi Y
    glBegin(GL_LINES);
    for (int i = 10; i <= 100; i += 10) {
        glVertex2f(0.5f, i);
        glVertex2f(1.5f, i);
    }
    glEnd();
}

void drawCircle(float x, float y, float radius, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * 3.1415926f * float(i) / float(segments);
        float dx = radius * std::cosf(angle);
        float dy = radius * std::sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

double calculateDistance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

std::vector<std::vector<Point>> solveVRP(std::vector<Point>& points, int truckCapacity, int numTrucks) {
    // Find the starting point (depot)
    Point depot;
    for (const auto& point : points) {
        if (point.demand == 0) {
            depot = point;
            break;
        }
    }

    // Remove the depot from the points list
    points.erase(remove_if(points.begin(), points.end(), [&](Point p) { return p.demand == 0; }), points.end());

    std::vector<std::vector<Point>> routes(numTrucks);
    std::vector<bool> visited(points.size(), false);
    // Assign points to trucks using a balanced approach
    int currentTruck = 0;
    while (find(visited.begin(), visited.end(), false) != visited.end()) {
        int remainingCapacity = truckCapacity;
        Point currentLocation = depot;

        routes[currentTruck].push_back(depot); // Start route with depot

        while (remainingCapacity > 0) {
            int nextPoint = -1;
            double minDist = std::numeric_limits<double>::max();

            for (int j = 0; j < points.size(); ++j) {
                if (!visited[j] && points[j].demand <= remainingCapacity) {
                    double dist = calculateDistance(currentLocation, points[j]);
                    if (dist < minDist) {
                        minDist = dist;
                        nextPoint = j;
                    }
                }
            }

            if (nextPoint == -1) break;

            routes[currentTruck].push_back(points[nextPoint]);
            visited[nextPoint] = true;
            remainingCapacity -= points[nextPoint].demand;
            currentLocation = points[nextPoint];
        }

        routes[currentTruck].push_back(depot); // Return to depot

        // Move to the next truck
        currentTruck = (currentTruck + 1) % numTrucks;
    }

    // Optimize each route using 2-opt
    for (auto& route : routes) {
        twoOpt(route);
    }

    return routes;

}

void drawLine(int x1, int y1 ,int x2, int y2, Color clr) {
    glColor3f(clr.x, clr.y, clr.z); // Ustawienie koloru
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

double calculateRouteLength(const std::vector<Point>& route) {
    double totalLength = 0.0;
    for (size_t i = 1; i < route.size(); ++i) {
        totalLength += calculateDistance(route[i - 1], route[i]);
    }
    return totalLength;
}

void twoOptSwap(std::vector<Point>& route, int i, int k) {
    while (i < k) {
        std::swap(route[i], route[k]);
        i++;
        k--;
    }
}

void twoOpt(std::vector<Point>& route) {
    bool improvement = true;
    while (improvement) {
        improvement = false;
        double bestDistance = calculateRouteLength(route);

        for (int i = 1; i < route.size() - 2; ++i) {
            for (int k = i + 1; k < route.size() - 1; ++k) {
                twoOptSwap(route, i, k);
                double newDistance = calculateRouteLength(route);
                if (newDistance < bestDistance) {
                    bestDistance = newDistance;
                    improvement = true;
                }
                else {
                    twoOptSwap(route, i, k); // Revert the change
                }
            }
        }
    }
}