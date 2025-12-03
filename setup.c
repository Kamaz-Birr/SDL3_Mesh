#include "setup.h"
#include "d_array.h"

TriangleRender triangle_renders[N_MESH_FACES];

void setup(void) {
	// Any setup code can go here
	pixel_buffer = (uint32_t*)SDL_malloc(window_width * window_height * sizeof(uint32_t));

	// Create the texture that we will use to render the pixel buffer to the screen
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);

	// Populate the triangle mesh array with vertex information
	for (int i = 0; i < N_MESH_FACES; i++) {
		TriangleFace face = mesh_faces[i];
		// printf("Processing Face %d: Indices(%d, %d, %d)\n", i, face.a, face.b, face.c);
		
		// Get the vertices of the triangle
		Vector3D face_vertices[3];
		face_vertices[0] = mesh_vertices[face.a - 1];
		face_vertices[1] = mesh_vertices[face.b - 1];
		face_vertices[2] = mesh_vertices[face.c - 1];
		
		// Populate the triangle render structure
		triangle_renders[i].points[0] = face_vertices[0];
		triangle_renders[i].points[1] = face_vertices[1];
		triangle_renders[i].points[2] = face_vertices[2];
	}
}