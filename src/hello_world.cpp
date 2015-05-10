#include <iostream>
#include "SDL.h"
#include "SDL_opengl.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include "point.h"
#include <vector>

using std::cout;
using std::vector;

bool isGlError() {
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		cout << "GL Error " << gluErrorString(error);
		return true;
	}
	return false;
}

float getRandomFloat() {
	const int maxValue = 10000;
	int next = rand() % maxValue;
	return next / 10000.f;
}

bool getRandomBoolean() {
	return rand() % 1 == 0;
}

int main(int argc, char* argv[])
{
	const int WIDTH = 640;
	const int HEIGHT = 480;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Failed initalization - " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
		"MyWindow",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
	);

	if (window == NULL) {
		cout << "Window could not be created - " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == NULL) {
		cout << "Error creating GL context " << SDL_GetError() << "\n";
		return 1;
	}

	if (SDL_GL_SetSwapInterval(1) < 0) {
		cout << "Error setting vsync " << SDL_GetError() << "\n";
		cout << "Linux VMs do not like Vsync it seems...not exiting" << "\n";
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (isGlError()) { return 1; }
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (isGlError()) { return 1; }
	glClearColor(0.f, 0.f, 0.f, 1.f);

	if (isGlError()) { return 1; }

	glClear(GL_COLOR_BUFFER_BIT);

	vector<Point> points(4, Point(0.f, 0.f, getRandomFloat(), getRandomFloat(), getRandomFloat()));
	points[0].setX(-0.5f);
	points[0].setY(-0.5f);
	points[1].setX(0.5f);
	points[1].setY(-0.5f);
	points[2].setX(0.5f);
	points[2].setY(0.5f);
	points[3].setX(-0.5f);
	points[3].setY(0.5f);

	bool run = true;
	SDL_Event event;
	while (run) {
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_QUADS);

		for (vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {
			it->nudgePoint();
			it->nudgeColor();
			it->draw();
		}

		glEnd();

		SDL_GL_SwapWindow(window);

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				run = false;
			}
		}

		SDL_Delay(10);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}