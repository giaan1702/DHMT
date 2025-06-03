#include <GL/freeglut.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

#include "config.h"
#include "point3d.h"
#include "camera.h"
#include "bspline.h"
#include "interaction.h"
#include "draw_utils.h"

// Biến toàn cục cho trạng thái ứng dụng và cửa sổ
int windowWidth = 1000;
int windowHeight = 750;

std::vector<Point3D> controlPoints_global; // Dữ liệu chính của ứng dụng
std::vector<float> knotVector_global;   // Dữ liệu chính của ứng dụng

// Mouse interaction state (cục bộ cho main.cpp vì chỉ callback dùng)
int lastMouseX_main = 0, lastMouseY_main = 0;
bool isRightMouseDown_main = false;


// Khai báo trước các hàm callback của GLUT
void display();
void reshape(int w, int h);
void mouseCallback(int button, int state, int x, int y);
void motionCallback(int x, int y);
void mouseWheelCallback(int wheel, int direction, int x, int y);
void keyboardCallback(unsigned char key, int x, int y);
void specialKeyboardCallback(int key, int x, int y);


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Ve duong cong B-spline 3D - Refactored");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(motionCallback);
    glutMouseWheelFunc(mouseWheelCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialKeyboardCallback);

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    initCamera(); // Gọi hàm khởi tạo camera từ camera.cpp

    glutMainLoop();
    return 0;
}

void reshape(int w, int h) {
    windowWidth = w; // Cập nhật biến toàn cục của main
    windowHeight = h;
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW); // Sẽ được xử lý trong display
}

void mouseCallback(int button, int state, int x, int y) {
    lastMouseX_main = x;
    lastMouseY_main = y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int clickedPointIdx = findClickedPointIndex(x, y, controlPoints_global, CLICK_RADIUS_PIXELS_CONFIG);

        if (clickedPointIdx != -1) {
            controlPoints_global.erase(controlPoints_global.begin() + clickedPointIdx);
            std::cout << "Da xoa diem dieu khien tai index: " << clickedPointIdx << std::endl;
        }
        else {
            GLdouble modelMatrix[16], projMatrix[16];
            GLint viewport[4];
            glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
            glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
            glGetIntegerv(GL_VIEWPORT, viewport);

            float winX = (float)x;
            float winY = (float)viewport[3] - (float)y;

            GLdouble worldX_ndc, worldY_ndc, worldZ_ndc_screen;
            gluProject(lookAtPoint.x, lookAtPoint.y, lookAtPoint.z,
                modelMatrix, projMatrix, viewport,
                &worldX_ndc, &worldY_ndc, &worldZ_ndc_screen);

            GLdouble worldX, worldY, worldZ;
            gluUnProject(winX, winY, worldZ_ndc_screen,
                modelMatrix, projMatrix, viewport,
                &worldX, &worldY, &worldZ);

            controlPoints_global.push_back({ (float)worldX, (float)worldY, (float)worldZ });
            std::cout << "Da them diem 3D: (" << worldX << ", " << worldY << ", " << worldZ << ")" << std::endl;
        }

        if (controlPoints_global.size() > B_SPLINE_DEGREE_CONFIG) {
            generateKnotVector(controlPoints_global, knotVector_global, B_SPLINE_DEGREE_CONFIG);
        }
        else {
            knotVector_global.clear();
        }
        glutPostRedisplay();

    }
    else if (button == GLUT_RIGHT_BUTTON) {
        isRightMouseDown_main = (state == GLUT_DOWN);
    }
}

void motionCallback(int x, int y) {
    int dx = x - lastMouseX_main;
    int dy = y - lastMouseY_main;

    if (isRightMouseDown_main) {
        cameraAzimuth += dx * 0.25f;
        cameraElevation -= dy * 0.25f;

        if (cameraElevation > 89.0f) cameraElevation = 89.0f;
        if (cameraElevation < -89.0f) cameraElevation = -89.0f;

        updateCameraPosition(); // Từ camera.h/.cpp
    }

    lastMouseX_main = x;
    lastMouseY_main = y;
    glutPostRedisplay();
}

void mouseWheelCallback(int wheel, int direction, int x, int y) {
    if (direction > 0) {
        cameraDistance -= 10.0f;
    }
    else if (direction < 0) {
        cameraDistance += 10.0f;
    }

    if (cameraDistance < 5.0f) cameraDistance = 5.0f;
    if (cameraDistance > 800.0f) cameraDistance = 800.0f;

    updateCameraPosition(); // Từ camera.h/.cpp
    glutPostRedisplay();
}

void keyboardCallback(unsigned char key, int x, int y) {
    switch (key) {
    case 'c': case 'C':
        controlPoints_global.clear();
        knotVector_global.clear();
        std::cout << "Da xoa cac diem dieu khien." << std::endl;
        break;
    case 's': case 'S':
        if (controlPoints_global.empty()) { std::cout << "Khong co diem.\n"; return; }
        {
            std::ofstream outFile("file.txt");
            if (outFile.is_open()) {
                outFile << "Du lieu duong cong B-spline 3D (Bac " << B_SPLINE_DEGREE_CONFIG << ")\n\n";
                outFile << "Cac diem dieu khien (" << controlPoints_global.size() << " diem):\n";
                outFile << "X Y Z\n";
                for (const auto& cp : controlPoints_global) {
                    outFile << std::fixed << std::setprecision(2) << cp.x << " " << cp.y << " " << cp.z << "\n";
                }
                if (!knotVector_global.empty()) {
                    outFile << "\nVector nut (" << knotVector_global.size() << " nut):\n";
                    for (size_t i = 0; i < knotVector_global.size(); ++i) {
                        outFile << std::fixed << std::setprecision(4) << knotVector_global[i] << (i == knotVector_global.size() - 1 ? "" : " ");
                    }
                    outFile << "\n";
                }
                if (controlPoints_global.size() > B_SPLINE_DEGREE_CONFIG && !knotVector_global.empty()) {
                    outFile << "\nCac diem duoc tao tren duong cong B-spline 3D (khoang 100 doan):\n";
                    outFile << "X Y Z\n";
                    int n_max_cp_idx = controlPoints_global.size() - 1;
                    float tMin = knotVector_global[B_SPLINE_DEGREE_CONFIG];
                    float tMax = knotVector_global[n_max_cp_idx + 1];
                    int num_segments = 100;
                    for (int k_seg = 0; k_seg <= num_segments; ++k_seg) {
                        float t_param = tMin + (tMax - tMin) * (float)k_seg / (float)num_segments;
                        if (k_seg == num_segments) t_param = tMax;
                        Point3D curvePt = calculateBsplinePoint(t_param, controlPoints_global, B_SPLINE_DEGREE_CONFIG, knotVector_global);
                        outFile << std::fixed << std::setprecision(2) << curvePt.x << " " << curvePt.y << " " << curvePt.z << "\n";
                    }
                }
                outFile.close();
                std::cout << "Da luu du lieu vao file.txt" << std::endl;
            }
            else { std::cerr << "Loi mo file.\n"; }
        }
        break;
    case 'r': case 'R':
        cameraAzimuth = 45.0f;
        cameraElevation = 30.0f;
        cameraDistance = 200.0f;
        lookAtPoint = { 0.0f, 0.0f, 0.0f };
        updateCameraPosition(); // Từ camera.h/.cpp
        break;
    }
    glutPostRedisplay();
}

void specialKeyboardCallback(int key, int x, int y) {
    float pan_speed_arrows = 2.5f * (cameraDistance / 150.0f);
    if (pan_speed_arrows < 0.05f) pan_speed_arrows = 0.05f;

    Point3D forwardVec, rightVec, actualUpVec;
    Point3D globalUp = { 0.0f, 1.0f, 0.0f };

    forwardVec = { lookAtPoint.x - eyePosition.x, lookAtPoint.y - eyePosition.y, lookAtPoint.z - eyePosition.z };
    float len_fwd = std::sqrt(forwardVec.x * forwardVec.x + forwardVec.y * forwardVec.y + forwardVec.z * forwardVec.z);
    if (len_fwd > 1e-5) {
        forwardVec.x /= len_fwd; forwardVec.y /= len_fwd; forwardVec.z /= len_fwd;
    }
    else { return; }

    rightVec.x = forwardVec.y * globalUp.z - forwardVec.z * globalUp.y;
    rightVec.y = forwardVec.z * globalUp.x - forwardVec.x * globalUp.z;
    rightVec.z = forwardVec.x * globalUp.y - forwardVec.y * globalUp.x;
    float len_right = std::sqrt(rightVec.x * rightVec.x + rightVec.y * rightVec.y + rightVec.z * rightVec.z);
    if (len_right > 1e-5) {
        rightVec.x /= len_right; rightVec.y /= len_right; rightVec.z /= len_right;
    }
    else {
        float azRad = cameraAzimuth * M_PI / 180.0f; // Sử dụng cameraAzimuth đã được khai báo extern
        rightVec = { std::cos(azRad), 0.0f, -std::sin(azRad) };
    }

    actualUpVec.x = rightVec.y * forwardVec.z - rightVec.z * forwardVec.y;
    actualUpVec.y = rightVec.z * forwardVec.x - rightVec.x * forwardVec.z;
    actualUpVec.z = rightVec.x * forwardVec.y - rightVec.y * forwardVec.x;
    // Không cần chuẩn hóa actualUpVec nếu rightVec và forwardVec đã chuẩn hóa và trực giao

    bool camera_panned = false;
    switch (key) {
    case GLUT_KEY_LEFT:
        lookAtPoint.x -= rightVec.x * pan_speed_arrows;
        lookAtPoint.y -= rightVec.y * pan_speed_arrows;
        lookAtPoint.z -= rightVec.z * pan_speed_arrows;
        camera_panned = true;
        break;
    case GLUT_KEY_RIGHT:
        lookAtPoint.x += rightVec.x * pan_speed_arrows;
        lookAtPoint.y += rightVec.y * pan_speed_arrows;
        lookAtPoint.z += rightVec.z * pan_speed_arrows;
        camera_panned = true;
        break;
    case GLUT_KEY_UP:
        lookAtPoint.x += actualUpVec.x * pan_speed_arrows;
        lookAtPoint.y += actualUpVec.y * pan_speed_arrows;
        lookAtPoint.z += actualUpVec.z * pan_speed_arrows;
        camera_panned = true;
        break;
    case GLUT_KEY_DOWN:
        lookAtPoint.x -= actualUpVec.x * pan_speed_arrows;
        lookAtPoint.y -= actualUpVec.y * pan_speed_arrows;
        lookAtPoint.z -= actualUpVec.z * pan_speed_arrows;
        camera_panned = true;
        break;
    }

    if (camera_panned) {
        updateCameraPosition(); // Từ camera.h/.cpp
        glutPostRedisplay();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eyePosition.x, eyePosition.y, eyePosition.z,
        lookAtPoint.x, lookAtPoint.y, lookAtPoint.z,
        0.0f, 1.0f, 0.0f);

    drawAxes(AXIS_LENGTH_CONFIG); // Từ draw_utils.h/.cpp

    if (!controlPoints_global.empty()) {
        glColor3f(1.0f, 0.65f, 0.0f);
        for (const auto& p : controlPoints_global) {
            glPushMatrix();
            glTranslatef(p.x, p.y, p.z);
            glutSolidSphere(POINT_RADIUS_CONFIG, 16, 16);
            glPopMatrix();
        }
    }

    if (controlPoints_global.size() > 1) {
        glColor3f(0.7f, 0.7f, 1.0f);
        glLineWidth(1.0f);
        glBegin(GL_LINE_STRIP);
        for (const auto& p : controlPoints_global) {
            glVertex3f(p.x, p.y, p.z);
        }
        glEnd();
    }

    if (controlPoints_global.size() > B_SPLINE_DEGREE_CONFIG) {
        // knotVector_global đã được cập nhật trong mouseCallback hoặc keyboardCallback
        if (!knotVector_global.empty()) { // Đảm bảo vector nút không rỗng
            glColor3f(0.1f, 1.0f, 0.5f);
            glLineWidth(2.5f);
            glBegin(GL_LINE_STRIP);

            int n_max_cp_idx = controlPoints_global.size() - 1;
            float t_min_param = knotVector_global[B_SPLINE_DEGREE_CONFIG];
            float t_max_param = knotVector_global[n_max_cp_idx + 1];

            const int num_curve_segments = 100;
            for (int k = 0; k <= num_curve_segments; ++k) {
                float t_param = t_min_param + (t_max_param - t_min_param) * (float)k / (float)num_curve_segments;
                if (k == num_curve_segments) t_param = t_max_param;
                Point3D curvePt = calculateBsplinePoint(t_param, controlPoints_global, B_SPLINE_DEGREE_CONFIG, knotVector_global);
                glVertex3f(curvePt.x, curvePt.y, curvePt.z);
            }
            glEnd();
        }
    }

    drawHUD(windowWidth, windowHeight, controlPoints_global, B_SPLINE_DEGREE_CONFIG); // Từ draw_utils.h/.cpp
    glutSwapBuffers();
}