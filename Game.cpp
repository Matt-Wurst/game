#include "Game.h"

#include <stdio.h>


const int FPS = 60;
const int FRAME_TICKS = 1000 / FPS;


Game::Game(int width, int height, std::string title)
{
	myWidth = width;
	myHeight = height;
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

				myTextureLoader = new TextureLoader(myRenderer);

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

	//myTexture = new Texture();
	//success = myTexture->loadFromFile("res/error.png", myRenderer);
	myTexture = myTextureLoader->load("res/error.png");

	myPlayer = Player(128, 128, myTexture);

	//myLevelMap.loadTestMap(myRenderer);
	myLevelMap.loadFile("res/levels/test.json", myRenderer);
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
			if (e.type == SDL_QUIT)
			{
				quit = true;
				//system("PAUSE");
			}
			else
			{
				manageEvent(e);
			}
		}

		if (nextTickTime <= SDL_GetTicks()) 
		{
			nextTickTime += FRAME_TICKS;
			render();
			logic();
		}

	}

	return 0;
}


void Game::manageEvent(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN) 
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP: 
				printf("Up arrow key pressed\n");
				break;
			case SDLK_DOWN:
				printf("Down arrow key pressed\n");
				break;
			case SDLK_LEFT:
				printf("Left arrow key pressed\n");
				break;
			case SDLK_RIGHT:
				printf("Right arrow key pressed\n");
				break;
		}
	}
}


void Game::render()
{
	//Clear
	SDL_RenderClear(myRenderer);

	int mouseX;
	int mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);

	mouseX -= myWidth / 2;
	mouseY -= myHeight / 2;

	int camOffsetX = myPlayer.getPosX() - myWidth / 2;
	int camOffsetY = myPlayer.getPosY() - myHeight / 2;

	camOffsetX += mouseX / 5;
	camOffsetY += mouseY / 5;

	//everything
	myLevelMap.renderFloor(camOffsetX, camOffsetY);

	myPlayer.render(camOffsetX, camOffsetY);

	myLevelMap.renderCeiling(camOffsetX, camOffsetY);

	//Draw
	SDL_RenderPresent(myRenderer);
}


void Game::logic()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	int v = 200;
	int vx = 0;
	int vy = 0;
	if (currentKeyStates[SDL_SCANCODE_W]) vy -= v;
	if (currentKeyStates[SDL_SCANCODE_A]) vx -= v;
	if (currentKeyStates[SDL_SCANCODE_S]) vy += v;
	if (currentKeyStates[SDL_SCANCODE_D]) vx += v;
	myPlayer.setMovement(vx, vy);
	myPlayer.tick();
}