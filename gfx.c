#include "tetris.h"

static void _fill_rect_internal(SDL_Renderer *renderer, SDL_Rect *rect, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, rect);
}

static void _draw_rect_internal(SDL_Renderer *renderer, SDL_Rect *rect, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawRect(renderer, rect);
}

void tetramino_draw(struct tetramino *tetramino, SDL_Renderer *renderer, int size)
{
    SDL_Rect rect;
    rect.x = tetramino->x * size;
    rect.y = tetramino->y * size;
    rect.h = size;
    rect.w = size;
    _draw_rect_internal(renderer, &rect, 255, 0, 0);
}

void draw_block(struct tetramino *tetramini, SDL_Renderer *renderer, int size)
{
    for (int i = 0; i < 4; i++)
    {
        tetramino_draw(&tetramini[i], renderer, size);
    }
}

void tetris_map_draw(struct tetris_map *map, SDL_Renderer *renderer, int size)
{
    int y, x;
    for (y = 0; y < map->height; y++)
    {
        for (x = 0; x < map->width; x++)
        {
            int index = map->width * y + x;
            if (map->cells[index] != 0)
            {
                SDL_Rect rect;
                rect.x = x * size;
                rect.y = y * size;
                rect.h = size;
                rect.w = size;
                _fill_rect_internal(renderer, &rect, 255, 255, 255);
            }
        }
    }
}