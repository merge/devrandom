
#include <SDL/SDL.h>

#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 5;

int main(void)
{
	int x = -1, y = -1;
	int ticks = 0;
	int delta;
	
	SDL_Event ev;
	SDL_Rect r;
	r.w = r.h = BLOCK_SIZE;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Surface *main = SDL_SetVideoMode(480, 640, 0, SDL_FULLSCREEN | SDL_ANYFORMAT | SDL_DOUBLEBUF);

	if (!main && !(main = SDL_SetVideoMode(640, 480, 0, SDL_FULLSCREEN | SDL_ANYFORMAT | SDL_DOUBLEBUF)))
	{
		puts("Failed to setup video mode. Giving up!");
		return -1;
	}

	SDL_ShowCursor(SDL_DISABLE);

	SDL_FillRect(main, NULL, SDL_MapRGB(main->format, 255, 255, 255));

	ticks = SDL_GetTicks();

	while (1)
	{
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
				case SDL_MOUSEMOTION:
					printf("x: %d - y: %d\n", ev.motion.x, ev.motion.y);
					x = ev.motion.x;
					y = ev.motion.y;
					break;
				case SDL_MOUSEBUTTONDOWN:
					printf("x: %d - y: %d - button %d\n", ev.button.x, ev.button.y, ev.button.button);
					x = ev.motion.x;
					y = ev.motion.y;
					break;
				case SDL_KEYDOWN:
				case SDL_QUIT:
					SDL_ShowCursor(SDL_ENABLE);
					SDL_Quit();
					return 0;
			}

		}

		SDL_FillRect(main, NULL, SDL_MapRGB(main->format, 255, 255, 255));

		if (x != -1)
		{
			r.x = x;
			r.y = y;
			r.w = r.h = BLOCK_SIZE;
			SDL_FillRect(main, &r, SDL_MapRGB(main->format, 0, 0, 0));
		}

		SDL_Flip(main);

		delta = SDL_GetTicks() - ticks;
		if (delta < 1000/24)
			{
				SDL_Delay(1000/24 - delta);
				ticks = SDL_GetTicks();
			}

	}

}
