#pragma once

#include <iostream>
#include <string>
#include <SDL.h>

#include "Vector2D.h"

/* Get the resource path for resources located in res/subDir */
std::string getResourcePath(const std::string &subDir = "") {
	//We need to choose the path separator properly based on which
	//platform we're running on, since Windows uses a different
	//separator than most systems
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	//This will hold the base resource path: Lessons/res/
	//We give it static lifetime so that we'll only need to call
	//SDL_GetBasePath once to get the executable path
	static std::string baseRes;
	if (baseRes.empty()) {
		//SDL_GetBasePath will return NULL if something went wrong in retrieving the path
		char *basePath = SDL_GetBasePath();
		if (basePath) {
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		//We replace the last bin/ with res/ to get the the resource path
		size_t pos = baseRes.rfind("bin");
		baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
	}
	//If we want a specific subdirectory path in the resource directory
	//append it to the base path. This would be something like Lessons/res/Lesson0
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}


void set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(rend, r, g, b, a);
	SDL_RenderDrawPoint(rend, x, y);
}

void draw_circle(SDL_Renderer *surface, int n_cx, int n_cy, int rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	if (rad < 3) return;

	for (int radius = rad - 2; radius <= rad; radius++)
	{
		double error = (double)-radius;
		double x = (double)radius - 0.5;
		double y = (double)0.5;
		double cx = n_cx - 0.5;
		double cy = n_cy - 0.5;

		while (x >= y)
		{
			set_pixel(surface, (int)(cx + x), (int)(cy + y), r, g, b, a);
			set_pixel(surface, (int)(cx + y), (int)(cy + x), r, g, b, a);

			if (x != 0)
			{
				set_pixel(surface, (int)(cx - x), (int)(cy + y), r, g, b, a);
				set_pixel(surface, (int)(cx + y), (int)(cy - x), r, g, b, a);
			}

			if (y != 0)
			{
				set_pixel(surface, (int)(cx + x), (int)(cy - y), r, g, b, a);
				set_pixel(surface, (int)(cx - y), (int)(cy + x), r, g, b, a);
			}

			if (x != 0 && y != 0)
			{
				set_pixel(surface, (int)(cx - x), (int)(cy - y), r, g, b, a);
				set_pixel(surface, (int)(cx - y), (int)(cy - x), r, g, b, a);
			}

			error += y;
			++y;
			error += y;

			if (error >= 0)
			{
				--x;
				error -= x;
				error -= x;
			}
		}
	}
}

void draw_cube(SDL_Renderer *surface, int n_cx, int n_cy, int weight, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Rect rect;
	rect.x = n_cx;
	rect.y = n_cy;
	rect.w = weight;
	rect.h = height;

	SDL_SetRenderDrawColor(surface, r, g, b, a);
	SDL_RenderDrawRect(surface, &rect);
	SDL_RenderFillRect(surface, &rect);

	SDL_SetRenderDrawColor(surface, 0, 0, 0, 255);

	SDL_RenderPresent(surface);
}

void draw_triangle(SDL_Renderer* surface, int leftX, int leftY, int rightX, int rightY, int topX, int topY, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(surface, r, g, b, a);

	//Drawing the lines we want. (-1, 0), (0, 1), (1, 0)
	SDL_RenderDrawLine(surface, leftX, leftY, topX, topY);
	SDL_RenderDrawLine(surface, rightX, rightY, topX, topY);
	SDL_RenderDrawLine(surface, leftX, leftY, rightX, rightY);

	//Update the Renderer.
	SDL_RenderPresent(surface);
}

void draw_line(SDL_Renderer* surface, Vector2D p1, Vector2D p2, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(surface, r, g, b, a);
	SDL_RenderDrawLine(surface, p1.x, p1.y, p2.x, p2.y);
}