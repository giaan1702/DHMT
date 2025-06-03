#ifndef DRAW_UTILS_H
#define DRAW_UTILS_H

#include <string>
#include <vector>
#include "point3d.h"

void drawAxes(float axisLength);

void renderText(float x, float y, void* font, const std::string& str,
    float r = 0.0f, float g = 0.0f, float b = 0.0f);

void drawHUD(int windowWidth, int windowHeight,
    const std::vector<Point3D>& controlPoints,
    int bSplineDegree); 

#endif 