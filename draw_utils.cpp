#include "draw_utils.h"
#include "config.h" 
#include <GL/freeglut.h>
#include <string>
#include <vector>
#include <sstream>   
#include <iomanip>   

void drawAxes(float axisLength) {
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    // X-axis (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(axisLength, 0.0f, 0.0f);
    // Y-axis (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, axisLength, 0.0f);
    // Z-axis (Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, axisLength);
    glEnd();
}

void renderText(float x, float y, void* font, const std::string& str,
    float r, float g, float b) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (char c : str) {
        glutBitmapCharacter(font, c);
    }
}

void drawHUD(int windowWidth, int windowHeight,
    const std::vector<Point3D>& controlPoints, 
    int bSplineDegree) {
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    glDisable(GL_DEPTH_TEST);

    float textY = windowHeight - 20.0f;
    float lineSpacing = 18.0f;
    void* font = GLUT_BITMAP_HELVETICA_12;

    renderText(10, textY, font, "B-Spline 3D (Dieu khien moi)", 0.8f, 0.8f, 1.0f); textY -= lineSpacing * 1.5f;
    renderText(10, textY, font, "LMB Click: Them diem / Xoa diem", 1.0f, 1.0f, 1.0f); textY -= lineSpacing;
    renderText(10, textY, font, "RMB Drag: Xoay Camera (Orbit)", 1.0f, 1.0f, 1.0f); textY -= lineSpacing;
    renderText(10, textY, font, "MMB Wheel: Zoom Camera", 1.0f, 1.0f, 1.0f); textY -= lineSpacing;
    renderText(10, textY, font, "Mui ten: Di chuyen Camera (Pan)", 1.0f, 1.0f, 1.0f); textY -= lineSpacing;
    renderText(10, textY, font, "'c': Xoa Het | 's': Luu File | 'r': Reset View", 1.0f, 1.0f, 1.0f); textY -= lineSpacing * 1.5f;

    std::string req_msg = "Can " + std::to_string(bSplineDegree + 1) + " diem cho B-spline bac " + std::to_string(bSplineDegree) + ".";
    renderText(10, textY, font, req_msg, 0.7f, 0.7f, 0.7f); textY -= lineSpacing;

    textY -= lineSpacing / 2.0f;
    renderText(10, textY, font, "Cac diem dieu khien:", 0.8f, 1.0f, 0.8f); textY -= lineSpacing;
    for (size_t i = 0; i < controlPoints.size(); ++i) {
        if (textY < 20) {
            renderText(15, textY, font, "...", 0.9f, 0.9f, 0.9f);
            break;
        }
        std::stringstream ss;
        ss << "P" << i << ": (" << std::fixed << std::setprecision(1) << controlPoints[i].x
            << ", " << controlPoints[i].y << ", " << controlPoints[i].z << ")";
        renderText(15, textY, font, ss.str(), 0.9f, 0.9f, 0.9f);
        textY -= lineSpacing;
    }

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION); glPopMatrix();
    glMatrixMode(GL_MODELVIEW); glPopMatrix();
}