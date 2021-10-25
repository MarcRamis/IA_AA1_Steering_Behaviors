#pragma once
#include <string>
#include <SDL.h>

/* Get the resource path for resources located in res/subDir */
std::string getResourcePath(const std::string &subDir = "");

/* draw utilities */
void set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void draw_circle(SDL_Renderer *surface, int n_cx, int n_cy, int rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void draw_cube(SDL_Renderer *surface, int n_cx, int n_cy, int weight, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void draw_triangle(SDL_Renderer* surface, int leftX, int leftY, int rightX, int rightY, int topX, int TopY, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void draw_line(SDL_Renderer* surface, Vector2D p1, Vector2D p2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);