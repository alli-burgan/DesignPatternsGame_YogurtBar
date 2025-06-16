#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Game.h"
#include "StateInGame.h"


int main(int argc, char* args[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game = Game();

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		game.Input();
		game.Update();
		game.Render();

		if (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}

	return 0;
}