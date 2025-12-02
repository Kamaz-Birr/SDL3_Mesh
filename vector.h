#pragma once

extern float scale_factor;

typedef struct {
	float x;
	float y;
} Vector2D;

typedef struct {
	float x;
	float y;
	float z;
} Vector3D;

Vector3D camera_pos;
Vector3D cube_rotation;

Vector2D project(Vector3D point3D);
Vector2D project_flatten(Vector3D point3D);
Vector3D vector3d_rotate_x(Vector3D v, float angle);
Vector3D vector3d_rotate_y(Vector3D v, float angle);
Vector3D vector3d_rotate_z(Vector3D v, float angle);