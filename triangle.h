#pragma once

#include "vector.h"

typedef struct {
	int a;
	int b;
	int c;
} TriangleFace;

typedef struct {
	Vector3D points[3];
} TriangleRender;
