#include "vector.h"
#include <math.h>

float scale_factor = 512.0f;

Vector3D camera_pos = { 0.0f, 0.0f, -5.0f };
Vector3D cube_rotation = { 0.0f, 0.0f, 0.0f };

Vector2D project(Vector3D point3D) {
	// Simple perspective projection
	Vector2D point2D;
	point2D.x = (point3D.x * scale_factor) / point3D.z;
	point2D.y = (point3D.y * scale_factor) / point3D.z;

	return point2D;
}

Vector2D project_flatten(Vector3D point3D) {
	// Use this function to flatten and rotate the 3D points. Cubes will become planes
	Vector3D rotated_point = vector3d_rotate_y(point3D, cube_rotation.y);// Rotate the point around the cube's rotation angles
	rotated_point.z -= camera_pos.z; // Adjust for camera position

	// Simple perspective projection, project the rotated 3D points to the 2D plane
	Vector2D point2D;
	point2D.x = (rotated_point.x * scale_factor) / point3D.z;
	point2D.y = (rotated_point.y * scale_factor) / point3D.z;

	return point2D;
}

Vector3D vector3d_rotate_x(Vector3D v, float angle) {
	Vector3D result;
	result.x = v.x;
	result.y = v.y * cosf(angle) - v.z * sinf(angle);
	result.z = v.y * sinf(angle) + v.z * cosf(angle);
	return result;
}

Vector3D vector3d_rotate_y(Vector3D v, float angle) {
	Vector3D result;
	result.x = v.x * cosf(angle) - v.z * sinf(angle);
	result.y = v.y;
	result.z = v.x * sinf(angle) + v.z * cosf(angle);
	return result;
}

Vector3D vector3d_rotate_z(Vector3D v, float angle) {
	Vector3D result;
	result.x = v.x * cosf(angle) - v.y * sinf(angle);
	result.y = v.x * sinf(angle) + v.y * cosf(angle);
	result.z = v.z;
	return result;
}