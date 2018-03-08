#include "SDL/include/SDL.h"
#include "SDL_Image/include/SDL_image.h"
#include "SDL_Mixer/include/SDL_mixer.h"

#pragma comment(lib,"SDL/libx86/SDL2.lib")
#pragma comment(lib,"SDL/libx86/SDL2main.lib")
#pragma comment(lib, "SDL_Image/libx86/SDL2_image.lib")
#pragma comment(lib, "SDL_Mixer/libx86/SDL2_mixer.lib")

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;


int main(int argc, char* argv[]) {
	SDL_Window* gWindow = nullptr;				// Window declaration
	SDL_Renderer* gRenderer = nullptr;			// Renderization
	SDL_Surface* gScreenSurface = nullptr;		// Window surface.
	SDL_Texture* background = nullptr;
	SDL_Texture* laser = nullptr;
	SDL_Texture* plane = nullptr;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	gWindow = SDL_CreateWindow("Gunner Plane", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

	gScreenSurface = IMG_Load("background1.png");
	background = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

	gScreenSurface = IMG_Load("plane1.png");
	plane = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

	gScreenSurface = IMG_Load("laser.png");
	laser = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);
	
	SDL_FreeSurface(gScreenSurface);

	SDL_Rect obj1;
	obj1.x = SCREEN_WIDTH / 2 - 50;
	obj1.y = SCREEN_HEIGHT / 2 - 50;
	obj1.w = 50;
	obj1.h = 50;

	SDL_Rect bullet;
	bullet.w = 60;
	bullet.h = 20;
	bullet.x = 0 - bullet.w;
	bullet.y = 0 - bullet.h;

	SDL_Event occur;
	bool running = 1;

	bool left = 0;
	bool right = 0;
	bool up = 0;
	bool down = 0;
	bool shoot = 0;

	while (running == 1)
	{
		SDL_PollEvent(&occur);

		switch (occur.type) {
		case SDL_QUIT:
			running = 0;
			break;

		case SDL_KEYUP:
			switch (occur.key.keysym.sym) {
			case SDLK_UP:
				up = 0;
				break;
			case SDLK_DOWN:
				down = 0;
				break;
			case SDLK_RIGHT:
				right = 0;
				break;
			case SDLK_LEFT:
				left = 0;
				break;
			case SDLK_SPACE:
				shoot = 0;
				break;
			}
			break;

		case SDL_KEYDOWN:
			switch (occur.key.keysym.sym) {
			case SDLK_UP:
				up = 1;
				break;
			case SDLK_DOWN:
				down = 1;
				break;
			case SDLK_RIGHT:
				right = 1;
				break;
			case SDLK_LEFT:
				left = 1;
				break;
			case SDLK_SPACE:
				shoot = 1;
				break;
			}
			break;
		}


		if (up && obj1.y != 0) obj1.y -= 1;
		if (down && obj1.y != (SCREEN_HEIGHT - 50)) obj1.y += 1;
		if (left && obj1.x != 0) obj1.x -= 1;
		if (right && obj1.x != (SCREEN_WIDTH - 50)) obj1.x += 1;
		if (shoot) {
			bullet.x = obj1.x;
			bullet.y = obj1.y + 10;
		}
		if (bullet.x > 0 && bullet.x < SCREEN_WIDTH - 30);
			bullet.x += 5;

		
		SDL_RenderClear(gRenderer);
		
		SDL_RenderCopy(gRenderer, background, 0, 0);

		SDL_RenderCopyEx(gRenderer, laser, 0, &bullet, 0, 0, SDL_FLIP_NONE);
		
		SDL_RenderCopyEx(gRenderer, plane, 0, &obj1, 0, 0, SDL_FLIP_NONE);
	
		SDL_RenderPresent(gRenderer);

	}

	IMG_Quit();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();

	return 0;
}
