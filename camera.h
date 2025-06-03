#ifndef CAMERA_H
#define CAMERA_H

#include "point3d.h"


extern float cameraAzimuth;
extern float cameraElevation;
extern float cameraDistance;
extern Point3D lookAtPoint;
extern Point3D eyePosition;

void initCamera(); 
void updateCameraPosition();

#endif 