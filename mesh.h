#pragma once

#include "vector.h"
#include "triangle.h"

#define N_MESH_VERTICES 8
#define N_MESH_FACES (12) // 6 faces, 2 triangles per face

extern Vector3D mesh_vertices[N_MESH_VERTICES];
extern TriangleFace mesh_faces[N_MESH_FACES];