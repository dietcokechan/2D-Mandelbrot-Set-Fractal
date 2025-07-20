#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <Windows.h>
#include <string>
#include <math.h>

int WIDTH = 800;
int HEIGHT = 800;

long double min = -2.84;
long double max = 1.0;
int MAX_ITERATIONS = 300;

// to increment or decrement each frame to be able to zoom
long double factor = 1;

// range
long double map(long double value, long double in_min, long double in_max, long double out_min, long double out_max)
{

	return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

}

int main(int argc, char* argv[]) 
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	// window res
	// you can change 1600x900 to fit your screen
	// SDL_CreateWindowAndRenderer(1600, 900, 0, &window, &renderer);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

	int count = 0;
	
	while (1) 
	{

		max -= 0.1 * factor;
		min += 0.15 * factor;
		factor *= 0.9349;
		MAX_ITERATIONS += 5;

		if (count > 30)
		{
			MAX_ITERATIONS *= 1.02;
		}

		SDL_RenderPresent(renderer);

		for (int x = 0; x < WIDTH; x++) 
		{   
			// to exit screen if 1600x900
			if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
				return 0;
			if (GetKeyState('H') & 0x8000)
				return 0;

			// the "scene" for the mandelbrot equation
			for (int y = 0; y < HEIGHT; y++) 
			{
				// x = a and y = b
				long double a = map(x, 0, WIDTH, min, max);
				long double b = map(y, 0, HEIGHT, min, max);

				// i = initial
				long double ai = a;
				long double bi = b;

				// determines how many times for loop runs before shooting off to infinity
				int n = 0;

				for (int i = 0; i < MAX_ITERATIONS; i++)
				{
					// mandelbrot set equation beginning
					long double a1 = a * a - b * b;
					long double b1 = 2 * a * b;

					a = a1 + ai;
					b = b1 + bi;
					// mandelbrot set equation ending

					if ((a + b) > 2)
					{
						// to break out of the loop before it shoots off to infinity
						break;
					}

					n++;
				}

				// coloring
				int bright = map(n, 0, MAX_ITERATIONS, 0, 255);

				if ((n == MAX_ITERATIONS) || (bright < 20))
				{

					bright = 0;

				}

				int red = map(sqrt(bright), 0, sqrt(255), 0, 255);
				int green = bright;
				int blue = map(sqrt(bright), 0, sqrt(255), 0, 255);

				SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
				SDL_RenderDrawPoint(renderer, x, y);

			}
		}

		// screenshot each time it zooms
		SDL_Surface* sshot = SDL_GetWindowSurface(window);
		SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ABGR8888, sshot->pixels, sshot->pitch);
		std::string file = std::to_string(count) + ".bmp";
		SDL_SaveBMP(sshot, file.c_str());
		SDL_FreeSurface(sshot);

		count++;

	}

	return 0;

}