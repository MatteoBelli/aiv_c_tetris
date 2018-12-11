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

int tetramino_move_all_down(struct tetramino *tetramini, struct tetris_map *tetris_map)
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

int tetramino_move_all_right(struct tetramino *tetramini, struct tetris_map *tetris_map)
{
    for (int i = 0; i < 4; i++)
    {
        if (tetramino_move_right_check(&tetramini[i], tetris_map) == TETRAMINO_DEAD)
        {
            return TETRAMINO_DEAD;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        tetramino_move_right(&tetramini[i]);
    }

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

int tetramino_move_all_left(struct tetramino *tetramini, struct tetris_map *tetris_map)
{
    for (int i = 0; i < 4; i++)
    {
        if (tetramino_move_left_check(&tetramini[i], tetris_map) == TETRAMINO_DEAD)
        {
            return TETRAMINO_DEAD;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        tetramino_move_left(&tetramini[i]);
    }

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

int check_for_full_lines(struct tetramino *tetramini, struct tetris_map *tetris_map, int *rows)
{
    //total line to remove from indexes
    int ret = 0;
    for (int i = 0; i < 4; i++)
    {
        int current_index = tetris_map->width * tetramini[i].y + tetramini[i].x;
        int row = current_index / tetris_map->width;

        int line_full = 1;
        for (int x = 0; x < tetris_map->width; x++)
        {
            //current index of the row
            current_index = tetris_map->width * row + x;
            if (tetris_map->cells[current_index] == 1 && line_full)
            {
                continue;
            }
            line_full = 0;
        }

        if (line_full)
        {
            int finded = 0;
            for (int j = 0; j < ret; j++)
            {
                //index of the tetraminoes when reach the ground or when the value of the current line is 1
                if (rows[j] == row)
                {
                    finded = 1;
                }
            }

            if (!finded)
            {
                rows[ret] = row;
                ret++;
            }
        }
    }

    return ret;
}

void remove_full_lines(struct tetris_map *tetris_map, int *rows, int len)
{
    for (int i = 0; i < len; i++)
    {
        size_t size = sizeof(int) * tetris_map->width * rows[i];
        SDL_memcpy(tetris_map->cells + tetris_map->width, tetris_map->cells, size);
    }
}