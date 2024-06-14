#ifndef Functions_h
#define Functions_h

#include <vector>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <algorithm>

struct Point {
    int x, y;
    int demand;
};

void drawCircle(float x, float y, float radius, int segments);
void drawPoints(const std::vector<Point>& points);
bool initOpenGL(GLFWwindow** window, int width, int height, const char* title);
void drawAxes();
double calculateDistance(Point a, Point b);
std::vector<std::vector<Point>> solveVRP(std::vector<Point>& points, int truckCapacity, int numTrucks);

#endif