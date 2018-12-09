#include "Game.h"

#include <cstdlib>



const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const std::string SCREEN_TITLE = "GAME";


int main(int argc, char* args[])
{
	Game * game = new Game(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
	game->run();

	system("PAUSE");
	return 0;
}