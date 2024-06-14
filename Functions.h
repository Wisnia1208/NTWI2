#ifndef Functions_h
#define Functions_h

#include <vector>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>

struct Point {
    int x, y;
    int demand;
};

struct Color {
    float x, y, z;
};

void drawCircle(float x, float y, float radius, int segments);
void drawPoints(const std::vector<Point>& points);
bool initOpenGL(GLFWwindow** window, int width, int height, const char* title);
void drawAxes();
double calculateDistance(Point a, Point b);
std::vector<std::vector<Point>> solveVRP(std::vector<Point>& points, int truckCapacity, int numTrucks);
void drawLine(int x1, int y1, int x2, int y2, Color clr);
double calculateRouteLength(const std::vector<Point>& route);
void twoOptSwap(std::vector<Point>& route, int i, int k);
void twoOpt(std::vector<Point>& route);

#endif