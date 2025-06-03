#ifndef BSPLINE_H
#define BSPLINE_H

#include <vector>
#include "point3d.h"

void generateKnotVector(const std::vector<Point3D>& controlPoints,
    std::vector<float>& knotVector,
    int degree);

float coxDeBoor(float t, int i, int p,
    const std::vector<float>& knots,
    int max_cp_idx);

Point3D calculateBsplinePoint(float t,
    const std::vector<Point3D>& P,
    int p_degree,
    const std::vector<float>& U_knots);

#endif 