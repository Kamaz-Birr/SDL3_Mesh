#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;

extern int window_width;
extern int window_height;
extern uint32_t* pixel_buffer;

void setup(void);
void draw_grid(uint32_t color, int spacing);
void draw_bg_points(uint32_t color);
void draw_rectangle(int x, int y, int width, int height, uint32_t color);
void draw_pixel(int x, int y, uint32_t color);
void render_pixel_buffer(void);
void clear_pixel_buffer(uint32_t color);
