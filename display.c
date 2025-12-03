#include <math.h>

#include "display.h"
#include "vector.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

int window_width = 800;
int window_height = 600;
uint32_t* pixel_buffer = NULL;

void draw_line_Bresenham(int x0, int y0, int x1, int y1, uint32_t color) {
	if (pixel_buffer != NULL) {
		int dx = abs(x1 - x0);
		int dy = abs(y1 - y0);
		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;
		int err = dx - dy;
		while (true) {
			draw_pixel(x0, y0, color);
			if (x0 == x1 && y0 == y1) break;
			int err2 = err * 2;
			if (err2 > -dy) {
				err -= dy;
				x0 += sx;
			}
			if (err2 < dx) {
				err += dx;
				y0 += sy;
			}
		}
	}
}

void draw_line_DDA(int x0, int y0, int x1, int y1, uint32_t color) {
	if (pixel_buffer != NULL) {
		int dx = x1 - x0;
		int dy = y1 - y0;

		int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

		float x_inc = dx / (float)steps;
		float y_inc = dy / (float)steps;

		float current_x = x0;
		float current_y = y0;
		for (int i = 0; i <= steps; i++) {
			draw_pixel((int)roundf(current_x), (int)roundf(current_y), color);
			current_x += x_inc;
			current_y += y_inc;
		}
	}
}

void draw_triangle(Vector2D p1, Vector2D p2, Vector2D p3, uint32_t color) {
	draw_line_DDA((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, color);
	draw_line_DDA((int)p2.x, (int)p2.y, (int)p3.x, (int)p3.y, color);
	draw_line_DDA((int)p3.x, (int)p3.y, (int)p1.x, (int)p1.y, color);
}

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