#include "display.h"
#include "vector.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

int window_width = 800;
int window_height = 600;
uint32_t* pixel_buffer = NULL;

//void setup(void) {
//	// Any setup code can go here
//	// Allocate the required memory for the pixel buffer
//	pixel_buffer = (uint32_t*)SDL_malloc(window_width * window_height * sizeof(uint32_t));
//
//	// Create the texture that we will use to render the pixel buffer to the screen
//	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
//}

void draw_grid(uint32_t color, int spacing) {
	if (pixel_buffer != NULL) {
		// Draw vertical lines
		for (int x = 0; x < window_width; x += spacing) {
			for (int y = 0; y < window_height; y++) {
				pixel_buffer[y * window_width + x] = color;
			}
		}
		// Draw horizontal lines
		for (int y = 0; y < window_height; y += spacing) {
			for (int x = 0; x < window_width; x++) {
				pixel_buffer[y * window_width + x] = color;
			}
		}
	}
}

void draw_bg_points(uint32_t color) {
	if (pixel_buffer != NULL) {
		for (int y = 0; y < window_height; y += 10) {
			for (int x = 0; x < window_width; x += 10) {
				draw_pixel(x, y, color);
			}
		}
	}
}

void draw_rectangle(int x, int y, int width, int height, uint32_t color) {
	if (pixel_buffer != NULL) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int current_y = y + i;
				int current_x = x + j;
				draw_pixel(current_x, current_y, color);
			}
		}
	}
}

void draw_pixel(int x, int y, uint32_t color) {
	if (pixel_buffer != NULL) {
		if (x >= 0 && x < window_width && y >= 0 && y < window_height) {
			// Set the pixel in the buffer
			pixel_buffer[y * window_width + x] = color;
		}
	}
}

void render_pixel_buffer(void) {
	if (pixel_buffer != NULL && texture != NULL) {
		// Update the texture with the pixel buffer data
		SDL_UpdateTexture(texture, NULL, pixel_buffer, window_width * sizeof(uint32_t));
		// Copy the texture to the renderer
		SDL_RenderTexture(renderer, texture, NULL, NULL);
	}
}

void clear_pixel_buffer(uint32_t color) {
	if (pixel_buffer != NULL) {
		int total_pixels = window_width * window_height;
		for (int i = 0; i < total_pixels; i++) {
			pixel_buffer[i] = color;
		}
	}
}