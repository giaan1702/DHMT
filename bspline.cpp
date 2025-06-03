#include "bspline.h"
#include <cmath>     
#include <algorithm> 

void generateKnotVector(const std::vector<Point3D>& controlPoints,
    std::vector<float>& knotVector,
    int degree) {
    knotVector.clear();
    int num_control_points = controlPoints.size();
    if (num_control_points <= degree) {
        return;
    }
    int num_knots = num_control_points + degree + 1;
    for (int i = 0; i < num_knots; ++i) {
        if (i <= degree) {
            knotVector.push_back(0.0f);
        }
        else if (i >= num_knots - 1 - degree) {
            knotVector.push_back(1.0f);
        }
        else {
            knotVector.push_back(static_cast<float>(i - degree) / (num_control_points - degree));
        }
    }
}

float coxDeBoor(float t, int i, int p,
    const std::vector<float>& knots,
    int max_cp_idx) {
    if (p == 0) {
        bool condition1 = (knots[i] <= t && t < knots[i + 1]);
        bool condition2 = (i == max_cp_idx && std::abs(t - knots[i + 1]) < 1e-5f && knots[i] <= knots[i + 1] + 1e-5f);
        return (condition1 || condition2) ? 1.0f : 0.0f;
    }
    float term1_coeff = 0.0f;
    float den1 = knots[i + p] - knots[i];
    if (std::abs(den1) > 1e-6) {
        term1_coeff = (t - knots[i]) / den1;
    }
    float term2_coeff = 0.0f;
    float den2 = knots[i + p + 1] - knots[i + 1];
    if (std::abs(den2) > 1e-6) {
        term2_coeff = (knots[i + p + 1] - t) / den2;
    }
    return term1_coeff * coxDeBoor(t, i, p - 1, knots, max_cp_idx) +
        term2_coeff * coxDeBoor(t, i + 1, p - 1, knots, max_cp_idx);
}

Point3D calculateBsplinePoint(float t,
    const std::vector<Point3D>& P,
    int p_degree,
    const std::vector<float>& U_knots) {
    Point3D curvePoint = { 0.0f, 0.0f, 0.0f };
    int n_max_cp_idx = P.size() - 1;

    if (U_knots.empty() || P.size() <= p_degree) {
        if (!P.empty()) return P[0];
        return curvePoint;
    }

    float t_clamped = t;
    if (std::abs(t - U_knots[n_max_cp_idx + 1]) < 1e-5f) {
        t_clamped = U_knots[n_max_cp_idx + 1];
    }
    else {
        t_clamped = std::max(U_knots[p_degree], std::min(t, U_knots[n_max_cp_idx + 1]));
    }

    for (int i = 0; i <= n_max_cp_idx; ++i) {
        float basisVal = coxDeBoor(t_clamped, i, p_degree, U_knots, n_max_cp_idx);
        if (basisVal > 0) {
            curvePoint.x += basisVal * P[i].x;
            curvePoint.y += basisVal * P[i].y;
            curvePoint.z += basisVal * P[i].z;
        }
    }
    return curvePoint;
}