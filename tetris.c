#include "tetris.h"

void tetramino_init(struct tetramino *tetramino, int x, int y)
{
    tetramino->x = x;
    tetramino->y = y;
}

void spawn_cube(struct tetramino *tetramini, int x, int y)
{
    int i = 0;
    for (i = 0; i < 2; i++)
    {
        tetramino_init(&tetramini[i], x + i, y);
    }
    y++;
    for (i = 0; i < 2; i++)
    {
        tetramino_init(&tetramini[i + 2], x + i, y);
    }
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
            tetris_map->cells[dead_cells[i]] = 1;
        }
        return TETRAMINO_DEAD;
    }
    for (int i = 0; i < 4; i++)
    {
        tetramino_move_down(&tetramini[i]);
    }
    return TETRAMINO_OK;
}

int tetramino_move_down_check(struct tetramino *tetramino, struct tetris_map *tetris_map, int *dead_cell)
{
    int current_index = tetris_map->width * tetramino->y + tetramino->x;
    int next_index = tetris_map->width * (tetramino->y + 1) + tetramino->x;

    *dead_cell = current_index;
    if (tetramino->y >= tetris_map->height - 1)
    {
        return TETRAMINO_DEAD;
    }

    if (tetris_map->cells[next_index] == 1)
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

int tetramino_move_right_check(struct tetramino *tetramino, struct tetris_map *tetris_map)
{
    if (tetramino->x >= tetris_map->width - 1)
    {
        return TETRAMINO_DEAD;
    }

    int right_index = tetris_map->width * tetramino->y + (tetramino->x + 1);
    if (tetris_map->cells[right_index] == 1)
    {
        return TETRAMINO_DEAD;
    }

    return TETRAMINO_OK;
}

int tetramino_move_right(struct tetramino *tetramino)
{
    tetramino->x++;
    return TETRAMINO_OK;
}

int tetramino_move_left_check(struct tetramino *tetramino, struct tetris_map *tetris_map)
{
    if (tetramino->x <= 0)
    {
        return TETRAMINO_DEAD;
    }

    int left_index = tetris_map->width * tetramino->y + (tetramino->x - 1);
    if (tetris_map->cells[left_index] == 1)
    {
        return TETRAMINO_DEAD;
    }

    return TETRAMINO_OK;
}

int tetramino_move_left(struct tetramino *tetramino)
{
    tetramino->x--;
    return TETRAMINO_OK;
}

void tetris_map_init(struct tetris_map *tetris_map, int width, int height)
{
    int size = sizeof(int) * width * height;

    tetris_map->cells = malloc(size);
    memset(tetris_map->cells, 0, size);
    tetris_map->width = width;
    tetris_map->height = height;
}