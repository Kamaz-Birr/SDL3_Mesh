#define SDL_MAIN_USE_CALLBACKS

#include <stdio.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "setup.h"


// Initialize SDL and create a window
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) == false) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Could Not Initialise SDL!", SDL_GetError(), NULL);
		return SDL_APP_FAILURE;
	}

	// Full screen dimensions can be obtained like this:
	const SDL_DisplayMode* display_mode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
	window_width = display_mode->w;
	window_height = display_mode->h;

	if (SDL_CreateWindowAndRenderer("SDL3 3D Mesh", window_width, window_height, 0, &window, &renderer) == false) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Could Not Create Window/Renderer!", SDL_GetError(), NULL);
		return SDL_APP_FAILURE;
	}

	setup();

	// initialisation successful
	return SDL_APP_CONTINUE;
}

// This function runs once per frame and is the heart of the program
SDL_AppResult SDL_AppIterate(void* appstate) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Draw here
	// Loop all tringle faces
	cube_rotation.x += 0.01f;
	cube_rotation.y += 0.01f;
	cube_rotation.z += 0.01f;

	for(int i = 0; i < N_MESH_FACES; i++) {
		// Rotate the vertices
		Vector3D v1 = triangle_renders[i].points[0];
		Vector3D v2 = triangle_renders[i].points[1];
		Vector3D v3 = triangle_renders[i].points[2];

		v1 = vector3d_rotate_x(v1, cube_rotation.x);
		v1 = vector3d_rotate_y(v1, cube_rotation.y);
		v1 = vector3d_rotate_z(v1, cube_rotation.z);
		v1.z -= camera_pos.z; // Adjust for camera position
		v2 = vector3d_rotate_x(v2, cube_rotation.x);
		v2 = vector3d_rotate_y(v2, cube_rotation.y);
		v2 = vector3d_rotate_z(v2, cube_rotation.z);
		v2.z -= camera_pos.z; // Adjust for camera position
		v3 = vector3d_rotate_x(v3, cube_rotation.x);
		v3 = vector3d_rotate_y(v3, cube_rotation.y);
		v3 = vector3d_rotate_z(v3, cube_rotation.z);
		v3.z -= camera_pos.z; // Adjust for camera position
		// Project the 3D points to 2D
		Vector2D p1 = project(v1);
		Vector2D p2 = project(v2);
		Vector2D p3 = project(v3);
		// Offset to center of screen
		p1.x += window_width / 2;
		p1.y += window_height / 2;
		p2.x += window_width / 2;
		p2.y += window_height / 2;
		p3.x += window_width / 2;
		p3.y += window_height / 2;
		// Draw the triangle edges
		draw_rectangle((int)p1.x, (int)p1.y, 4, 4, 0xFFFFFF00);
		draw_rectangle((int)p2.x, (int)p2.y, 4, 4, 0xFFFFFF00);
		draw_rectangle((int)p3.x, (int)p3.y, 4, 4, 0xFFFFFF00);
	}

	draw_bg_points(0xFFCCCCCC); // ARGB format
	render_pixel_buffer();
	clear_pixel_buffer(0xFF000000); // ARGB format

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;
}

// This function runs when a new event occurs
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	switch (event->type) {
	case SDL_EVENT_QUIT:
		return SDL_APP_SUCCESS;
	case SDL_EVENT_KEY_DOWN:
		if (event->key.key == SDLK_ESCAPE) {
			return SDL_APP_SUCCESS;
		}
	default:
		break;
	}

	return SDL_APP_CONTINUE;
}

// This function runs once at shutdown
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	// SDL will clean up the window/renderer for us.
}