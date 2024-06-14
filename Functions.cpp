#include "Functions.h"

void drawPoints(const std::vector<Point>& points) {
    //glBegin(GL_POINTS);
    int segments = 30;
    for (const auto& point : points) {
        float x = point.x;
        float y = point.y;
        float radius = point.demand/5; // Promieñ okrêgu punktu
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

        // Rysowanie okrêgu jako wielok¹ta
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
    glOrtho(1.0, 100.0, 1.0, 100.0, -1.0, 1.0); // Zakres wspó³rzêdnych od 1 do 100
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return true;
}

void drawAxes() {
    glColor3f(1.0f, 1.0f, 1.0f); // Bia³e linie osi

    // Oœ X
    glBegin(GL_LINES);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(100.0f, 1.0f);
    glEnd();

    // Oœ Y
    glBegin(GL_LINES);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, 100.0f);
    glEnd();

    // Podzia³ka na osi X
    glBegin(GL_LINES);
    for (int i = 10; i <= 100; i += 10) {
        glVertex2f(i, 0.5f);
        glVertex2f(i, 1.5f);
    }
    glEnd();

    // Podzia³ka na osi Y
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
    std::vector<std::vector<Point>> routes(numTrucks);
    std::vector<bool> visited(points.size(), false);
    int currentTruck = 0;
    int remainingCapacity = truckCapacity;

    for (int i = 0; i < points.size(); ++i) {
        if (visited[i]) continue;
        if (points[i].demand > remainingCapacity) {
            currentTruck++;
            if (currentTruck >= numTrucks) {
                std::cout << "Not enough trucks to handle all deliveries." << std::endl;
                return std::vector<std::vector<Point>> (0); // to do wywalanie porogramu albo b³êdu
            }
            remainingCapacity = truckCapacity;
        }
        routes[currentTruck].push_back(points[i]);
        visited[i] = true;
        remainingCapacity -= points[i].demand;

        Point lastPoint = points[i];
        while (remainingCapacity > 0) {
            int nextPoint = -1;
            double minDist = std::numeric_limits<double>::max();
            for (int j = 0; j < points.size(); ++j) {
                if (!visited[j] && points[j].demand <= remainingCapacity) {
                    double dist = calculateDistance(lastPoint, points[j]);
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
            lastPoint = points[nextPoint];
        }
    }

    return routes;

}