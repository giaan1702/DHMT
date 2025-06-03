#include "camera.h"
#include "config.h" 
#include <cmath>    


float cameraAzimuth = 45.0f;
float cameraElevation = 30.0f;
float cameraDistance = 200.0f;
Point3D lookAtPoint = { 0.0f, 0.0f, 0.0f };
Point3D eyePosition;

void initCamera() {
    updateCameraPosition();
}

void updateCameraPosition() {
    float azRad = cameraAzimuth * M_PI / 180.0f;
    float elRad = cameraElevation * M_PI / 180.0f;

    eyePosition.x = lookAtPoint.x + cameraDistance * std::cos(elRad) * std::sin(azRad);
    eyePosition.y = lookAtPoint.y + cameraDistance * std::sin(elRad);
    eyePosition.z = lookAtPoint.z + cameraDistance * std::cos(elRad) * std::cos(azRad);
}