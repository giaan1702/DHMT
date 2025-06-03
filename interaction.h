#ifndef INTERACTION_H
#define INTERACTION_H

#include <vector>
#include "point3d.h"


int findClickedPointIndex(int mouse_x, int mouse_y,
    const std::vector<Point3D>& points,
    float clickRadiusPixels);

#endif 