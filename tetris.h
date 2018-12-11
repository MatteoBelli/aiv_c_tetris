#include <string.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include ".\SDL\SDL.h"

#define TETRAMINO_OK 0
#define TETRAMINO_DEAD -1

struct tetramino
{
    int x;
    int y;
};

struct tetris_map
{
    int width;
    int height;
    int *cells;
};

typedef struct tetramino tetramino_t;
typedef struct tetris_map tetris_map_t;

void tetramino_init(struct tetramino *tetramino, int x, int y);
void spawn_cube(struct tetramino *tetramini, int x, int y);

int tetramino_move_all_down(struct tetramino *tetramini, struct tetris_map *tetris_map);
int tetramino_move_down_check(struct tetramino *tetramino, struct tetris_map *tetris_map, int *dead_cell);
int tetramino_move_down(struct tetramino *tetramino);

int tetramino_move_all_right(struct tetramino *tetramini, struct tetris_map *tetris_map);
int tetramino_move_right_check(struct tetramino *tetramino, struct tetris_map *tetris_map);
int tetramino_move_right(struct tetramino *tetramino);

int tetramino_move_all_left(struct tetramino *tetramini, struct tetris_map *tetris_map);
int tetramino_move_left_check(struct tetramino *tetramino, struct tetris_map *tetris_map);
int tetramino_move_left(struct tetramino *tetramino);

void draw_block(struct tetramino *tetramini,SDL_Renderer *renderer, int size);
void tetramino_draw(struct tetramino *tetramino, SDL_Renderer *renderer, int size);

void tetris_map_init(struct tetris_map *tetris_map, int width, int height);
void tetris_map_draw(struct tetris_map *map, SDL_Renderer *renderer, int size);

int check_for_full_lines(struct tetramino *tetramini, struct tetris_map *tetris_map, int *rows);
void remove_full_lines(struct tetris_map *tetris_map, int *rows, int len);