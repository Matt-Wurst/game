#include "Game.h"

#include <stdio.h>


const int FPS = 60;
const int FRAME_TICKS = 1000 / FPS;


Game::Game(int width, int height, std::string title)
{
	//Start up SDL and create window
	if (!init(width, height, title))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
	}
}


Game::~Game()
{
	delete myTexture;
	myTexture = NULL;

	//Destroy window
	SDL_DestroyWindow(myWindow);
	myWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}




bool Game::init(int width, int height, std::string title)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		myWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (myWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
			if (myRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);


				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				else
				{
					//Get window surface
					myScreenSurface = SDL_GetWindowSurface(myWindow);
				}
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	bool success = true;

	myTexture = new Texture();
	success = myTexture->loadFromFile("res/error.png", myRenderer);

	return success;
}

SDL_Surface* Game::loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, myScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}




int Game::run()
{
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	int startTime = SDL_GetTicks();
	int nextTickTime = startTime;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		if (nextTickTime <= SDL_GetTicks()) 
		{
			nextTickTime += FRAME_TICKS;

			static int angle = 0;
			angle++;

			SDL_RenderClear(myRenderer);
			myTexture->render(100, 200, myRenderer, angle);
			SDL_RenderPresent(myRenderer);
		}

	}

	return 0;
}