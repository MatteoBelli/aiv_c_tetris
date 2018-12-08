#include "tetris.h"

void tetramino_init(struct tetramino *tetramino, struct tetris_map *tetris_map)
{
    tetramino->x = tetris_map->width / 2;
    tetramino->y = -1;
}

int tetramino_move_all_down(struct tetramino tetramini[4], struct tetris_map *tetris_map)
{
    int dead_cells[4];
    int can_move = 0;

    for (int i = 0; i < 4; i++)
    {
        if (tetramino_move_down_check(&tetramini[i], tetris_map, &dead_cells[i]) == TETRAMINO_DEAD)
        {
            can_move = 1;
        }
    }

    if (can_move == 1)
    {

        for (int i = 0; i < 4; i++)
        {
            *tetris_map[dead_cells[i]].cell = 1;
        }

        for (int i = 0; i < 4; i++)
        {
            tetramino_move_down(&tetramini[i]);
        }
    }
    return TETRAMINO_OK;
}

int tetramino_move_down_check(struct tetramino *tetramino, struct tetris_map *tetris_map, int *dead_cell)
{
    int current_index = tetris_map->width * tetramino->y + tetramino->x;
    int next_index = tetris_map->width * (tetramino->y + 1) + tetramino->x;

    *dead_cell = current_index;
    if (tetramino->y + 1 >= tetris_map->height)
    {
        return TETRAMINO_DEAD;
    }

    if (tetris_map->cell[next_index] == 1)
    {
        return TETRAMINO_DEAD;
    }

    return TETRAMINO_OK;
}

int tetramino_move_down(struct tetramino *tetramino)
{
    tetramino->y += 1;

    return TETRAMINO_OK;
}

int tetramino_move_right(struct tetramino *tetramino, struct tetris_map *tetris_map)
{
    if (tetramino->x >= tetris_map->width - 1)
    {
        return TETRAMINO_OK;
    }

    int right_index = tetris_map->width * tetramino->y + (tetramino->x + 1);
    if (!tetris_map->cell[right_index])
    {
        tetramino->x++;
    }

    return TETRAMINO_OK;
}

int tetramino_move_left(struct tetramino *tetramino, struct tetris_map *tetris_map)
{
    if (tetramino->x <= 0)
    {
        return TETRAMINO_OK;
    }

    int left_index = tetris_map->width * tetramino->y + (tetramino->x - 1);
    if (!tetris_map->cell[left_index])
    {
        tetramino->x--;
    }

    return TETRAMINO_OK;
}

void tetris_map_init(struct tetris_map *tetris_map, int width, int height)
{
    int size = sizeof(int) * width * height;

    tetris_map->cell = malloc(size);
    memset(tetris_map->cell, 0, size);
    tetris_map->width = width;
    tetris_map->height = height;
}