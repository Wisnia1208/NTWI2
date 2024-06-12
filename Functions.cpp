#include "Functions.h"

void drawPoints(const std::vector<std::pair<int, int>>& points) {
    //glBegin(GL_POINTS);
    int segments = 30;
    for (const auto& point : points) {
        float x = point.first;
        float y = point.second;
        float radius = 0.3f; // Promieñ okrêgu punktu

        // Rysowanie okrêgu jako wielok¹ta
        drawCircle(x, y, radius, segments);
    }
    glEnd();
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

