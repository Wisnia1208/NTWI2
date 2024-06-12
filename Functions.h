#ifndef Functions_h
#define Functions_h

#include <vector>
#include <GLFW/glfw3.h>
#include <iostream>

void drawCircle(float x, float y, float radius, int segments);
void drawPoints(const std::vector<std::pair<int, int>>& points);
bool initOpenGL(GLFWwindow** window, int width, int height, const char* title);
void drawAxes();

#endif