#include "tetris.h"

int main(int argc, char **argv)
{
	int ret = 0;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_Log("unable to initialize SDL2: %s", SDL_GetError());
		ret = -1;
		goto cleanup;
	}

	SDL_Window *window = SDL_CreateWindow("tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 600, 0);
	if (!window)
	{
		SDL_Log("unable to create window: %s", SDL_GetError());
		ret = -1;
		goto cleanup2;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_Log("unable to create renderer: %s", SDL_GetError());
		ret = -1;
		goto cleanup3;
	}

	tetris_map_t map;
	tetris_map_init(&map, 10, 20);

	tetramino_t tetramini[4];
	spawn_cube(tetramini, map.width / 2 - 1, -2);

	int timer = 1000;
	Uint32 last_ticks = SDL_GetTicks();

	for (;;)
	{
		SDL_Event event;

		Uint32 current_ticks = SDL_GetTicks();
		timer -= current_ticks - last_ticks;
		last_ticks = current_ticks;

		if (timer <= 0)
		{
			if (tetramino_move_all_down(tetramini, &map) == TETRAMINO_DEAD)
			{
				for (int i = 0; i < 4; i++)
				{
					if (tetramini[i].y == -1)
					{
						goto cleanup4;
					}
				}

				int rows[4];
				int res = check_for_full_lines(tetramini, &map, rows);

				if (res > 0)
				{
					remove_full_lines(&map, rows, res);
				}

				spawn_cube(tetramini, map.width / 2 - 1, -2);
			}
			timer = 1000;
		}

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				goto cleanup4;
			}
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_DOWN)
				{
					if (tetramino_move_all_down(tetramini, &map) == TETRAMINO_DEAD)
					{
						for (int i = 0; i < 4; i++)
						{
							if (tetramini[i].y == -1)
							{
								goto cleanup4;
							}
						}

						int rows[4];
						int res = check_for_full_lines(tetramini, &map, rows);

						if (res > 0)
						{
							remove_full_lines(&map, rows, res);
						}

						spawn_cube(tetramini, map.width / 2 - 1, -2);
					}
					timer = 1000;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					tetramino_move_all_right(tetramini, &map);
				}
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					tetramino_move_all_left(tetramini, &map);
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// draw map
		tetris_map_draw(&map, renderer, 30);

		//tetramino draw
		draw_block(tetramini, renderer, 30);

		SDL_RenderPresent(renderer);
	}

cleanup4:
	SDL_DestroyRenderer(renderer);
cleanup3:
	SDL_DestroyWindow(window);
cleanup2:
	SDL_Quit();
cleanup:
	return ret;
}
