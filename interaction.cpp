#include "interaction.h"
#include <GL/freeglut.h> 
#include <cmath>         

int findClickedPointIndex(int mouse_x, int mouse_y,
    const std::vector<Point3D>& points,
    float clickRadiusPixels) {
    if (points.empty()) return -1;

    GLdouble modelMatrix[16], projMatrix[16];
    GLint viewport[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
    glGetIntegerv(GL_VIEWPORT, viewport);

    float screen_y_opengl = (float)viewport[3] - (float)mouse_y;

    for (size_t i = 0; i < points.size(); ++i) {
        GLdouble screen_px, screen_py, screen_pz;
        if (gluProject(points[i].x, points[i].y, points[i].z,
            modelMatrix, projMatrix, viewport,
            &screen_px, &screen_py, &screen_pz) == GL_FALSE) {
            continue;
        }

        if (screen_pz < 1.0 && screen_pz > 0.0) {
            float dx = (float)mouse_x - (float)screen_px;
            float dy = screen_y_opengl - (float)screen_py;
            float distSq = dx * dx + dy * dy;

            if (distSq < clickRadiusPixels * clickRadiusPixels) {
                return static_cast<int>(i);
            }
        }
    }
    return -1;
}