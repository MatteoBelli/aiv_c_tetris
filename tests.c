#include "aiv_unit_test.h"
#include "tetris.h"

#define TETRAMINO_SETUP(width, height, x, y)     \
	tetramino_t tetramino;                       \
	tetris_map_t tetris_map;                     \
	tetris_map_init(&tetris_map, width, height); \
	tetramino_init(&tetramino, x, y)

#define TETRAMINO_MOVE_DOWN(tetramino_pointer, map_pointer)                                        \
	{                                                                                              \
		int dead_cell;                                                                             \
		if (tetramino_move_down_check(tetramino_pointer, map_pointer, &dead_cell) == TETRAMINO_OK) \
		{                                                                                          \
			tetramino_move_down(tetramino_pointer);                                                \
		}                                                                                          \
		else                                                                                       \
		{                                                                                          \
			map_pointer->cells[dead_cell] = 1;                                                     \
		}                                                                                          \
	}

#define TETRAMINO_MOVE_RIGHT(tetramino_pointer, map_pointer)                            \
	{                                                                                   \
		if (tetramino_move_right_check(tetramino_pointer, map_pointer) == TETRAMINO_OK) \
		{                                                                               \
			tetramino_move_right(tetramino_pointer);                                    \
		}                                                                               \
	}

#define TETRAMINO_MOVE_LEFT(tetramino_pointer, map_pointer)                            \
	{                                                                                  \
		if (tetramino_move_left_check(tetramino_pointer, map_pointer) == TETRAMINO_OK) \
		{                                                                              \
			tetramino_move_left(tetramino_pointer);                                    \
		}                                                                              \
	}

TEST(tetramino_init)
{
	TETRAMINO_SETUP(1, 1, 5, 7);

	ASSERT_THAT(tetramino.x == 5);
	ASSERT_THAT(tetramino.y == 7)
}

TEST(spawn_cube)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, 0);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 0);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(spawn_line)
{
	tetramino_t tetramini[4];
	spawn_line(tetramini, 0, 0);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 2);
	ASSERT_THAT(tetramini[2].y == 0);

	ASSERT_THAT(tetramini[3].x == 3);
	ASSERT_THAT(tetramini[3].y == 0);
}

TEST(spawn_right_l)
{
	tetramino_t tetramini[4];
	spawn_right_l(tetramini, 3, 0);

	ASSERT_THAT(tetramini[0].x == 3);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 3);
	ASSERT_THAT(tetramini[1].y == 1);

	ASSERT_THAT(tetramini[2].x == 2);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(spawn_left_l)
{
	tetramino_t tetramini[4];
	spawn_left_l(tetramini, 0, 0);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 0);
	ASSERT_THAT(tetramini[1].y == 1);

	ASSERT_THAT(tetramini[2].x == 1);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 2);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(spawn_right_z)
{
	tetramino_t tetramini[4];
	spawn_right_z(tetramini, 2, 0);

	ASSERT_THAT(tetramini[0].x == 2);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 1);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 0);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(spawn_left_z)
{
	tetramino_t tetramini[4];
	spawn_left_z(tetramini, 0, 0);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 1);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 2);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(spawn_triangle)
{
	tetramino_t tetramini[4];
	spawn_triangle(tetramini, 1, 0);

	ASSERT_THAT(tetramini[0].x == 1);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 0);
	ASSERT_THAT(tetramini[1].y == 1);

	ASSERT_THAT(tetramini[2].x == 1);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 2);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(move_all_down)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, -2);

	tetris_map_t map;
	tetris_map_init(&map, 2, 2);

	int res = tetramino_move_all_down(tetramini, &map);

	ASSERT_THAT(res == TETRAMINO_OK);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == -1);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == -1);

	ASSERT_THAT(tetramini[2].x == 0);
	ASSERT_THAT(tetramini[2].y == 0);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 0);
}

TEST(move_all_down_end_map)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, -2);

	tetris_map_t map;
	tetris_map_init(&map, 2, 1);

	int res = tetramino_move_all_down(tetramini, &map);
	res = tetramino_move_all_down(tetramini, &map);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(move_all_down_occupied_cell)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, -2);

	tetris_map_t map;
	tetris_map_init(&map, 2, 1);

	int res = tetramino_move_all_down(tetramini, &map);
	res = tetramino_move_all_down(tetramini, &map);

	tetramino_t tetramini2[4];
	spawn_cube(tetramini2, 0, -2);

	res = tetramino_move_all_down(tetramini2, &map);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_down_check)
{
	TETRAMINO_SETUP(1, 1, 0, -1);
	int dead_cell;
	int res = tetramino_move_down_check(&tetramino, &tetris_map, &dead_cell);

	ASSERT_THAT(res == TETRAMINO_OK);
}

TEST(tetramino_move_down_check_red_light)
{
	TETRAMINO_SETUP(1, 1, 0, 0);
	int dead_cell;
	int res = tetramino_move_down_check(&tetramino, &tetris_map, &dead_cell);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_down_check_multiple_block)
{
	TETRAMINO_SETUP(1, 1, 0, -1);
	tetramino.y = 0;

	int dead_cell;
	tetramino_move_down_check(&tetramino, &tetris_map, &dead_cell);
	tetris_map.cells[dead_cell] = 1;

	tetramino_t tetramino2;
	tetramino_init(&tetramino2, 0, -1);

	int res = tetramino_move_down_check(&tetramino2, &tetris_map, &dead_cell);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_down)
{
	TETRAMINO_SETUP(1, 1, 0, -1);
	tetramino_move_down(&tetramino);

	ASSERT_THAT(tetramino.y == 0);
}

TEST(tetramino_move_down_wrong_value)
{
	TETRAMINO_SETUP(1, 1, 0, -1);
	tetramino.y = 100;
	int dead_cell;
	if (tetramino_move_down_check(&tetramino, &tetris_map, &dead_cell) == TETRAMINO_OK)
	{
		tetramino_move_down(&tetramino);
	}

	ASSERT_THAT(tetramino.y == 100);
}

TEST(move_all_right)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, 0);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);

	int res = tetramino_move_all_right(tetramini, &map);

	ASSERT_THAT(res == TETRAMINO_OK);

	ASSERT_THAT(tetramini[0].x == 1);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 2);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 1);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 2);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(move_all_right_border)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, 0);

	tetris_map_t map;
	tetris_map_init(&map, 3, 2);

	int res = tetramino_move_all_right(tetramini, &map);
	res = tetramino_move_all_right(tetramini, &map);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_right_check)
{
	TETRAMINO_SETUP(2, 1, 0, -1);

	int res = tetramino_move_right_check(&tetramino, &tetris_map);

	ASSERT_THAT(res == TETRAMINO_OK);
}

TEST(tetramino_move_right_check_blocked)
{
	TETRAMINO_SETUP(1, 1, 0, -1);

	int res = tetramino_move_right_check(&tetramino, &tetris_map);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_right_blocked)
{
	TETRAMINO_SETUP(1, 1, 0, -1);

	tetris_map_t *map = &tetris_map;
	TETRAMINO_MOVE_RIGHT(&tetramino, map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_right)
{
	TETRAMINO_SETUP(2, 1, 0, 0);

	tetris_map_t *map = &tetris_map;
	TETRAMINO_MOVE_RIGHT(&tetramino, map);

	ASSERT_THAT(tetramino.x == 1);
}

TEST(tetramino_move_right_multiple)
{
	TETRAMINO_SETUP(2, 1, 0, 0);

	tetris_map_t *map = &tetris_map;
	TETRAMINO_MOVE_RIGHT(&tetramino, map);
	TETRAMINO_MOVE_RIGHT(&tetramino, map);

	ASSERT_THAT(tetramino.x == 1);
}

TEST(move_all_left)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 1, 0);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);

	int res = tetramino_move_all_left(tetramini, &map);

	ASSERT_THAT(res == TETRAMINO_OK);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 0);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(move_all_left_border)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 1, 0);

	tetris_map_t map;
	tetris_map_init(&map, 3, 2);

	int res = tetramino_move_all_left(tetramini, &map);
	res = tetramino_move_all_left(tetramini, &map);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_left_check)
{
	TETRAMINO_SETUP(2, 1, 1, -1);

	int res = tetramino_move_left_check(&tetramino, &tetris_map);

	ASSERT_THAT(res == TETRAMINO_OK);
}

TEST(tetramino_move_left_check_blocked)
{
	TETRAMINO_SETUP(1, 1, 0, -1);

	int res = tetramino_move_left_check(&tetramino, &tetris_map);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_left_blocked)
{
	TETRAMINO_SETUP(1, 1, 0, -1);

	tetris_map_t *map = &tetris_map;
	TETRAMINO_MOVE_LEFT(&tetramino, map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_left)
{
	TETRAMINO_SETUP(2, 1, 1, -1);

	tetris_map_t *map = &tetris_map;
	TETRAMINO_MOVE_LEFT(&tetramino, map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_left_multiple)
{
	TETRAMINO_SETUP(2, 1, 1, -1);

	tetris_map_t *map = &tetris_map;
	TETRAMINO_MOVE_LEFT(&tetramino, map);
	TETRAMINO_MOVE_LEFT(&tetramino, map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_busy_cell)
{
	TETRAMINO_SETUP(1, 1, 0, -1);

	tetris_map_t *map_pointer = &tetris_map;

	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);
	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);

	tetramino_t tetramino2;
	tetramino_init(&tetramino2, 0, -1);

	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);
	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);

	ASSERT_THAT(tetramino2.y == -1);
}

TEST(tetramino_fill_two_blocks)
{
	TETRAMINO_SETUP(1, 2, 0, -1);

	tetris_map_t *map_pointer = &tetris_map;

	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);
	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);
	TETRAMINO_MOVE_DOWN(&tetramino, map_pointer);

	ASSERT_THAT(tetramino.y == 1);

	tetramino_t tetramino2;
	tetramino_init(&tetramino2, 0, -1);

	TETRAMINO_MOVE_DOWN(&tetramino2, map_pointer);
	TETRAMINO_MOVE_DOWN(&tetramino2, map_pointer);
	TETRAMINO_MOVE_DOWN(&tetramino2, map_pointer);

	ASSERT_THAT(tetramino2.y == 0);
}

TEST(try_rotate_cube)
{
	tetramino_t tetramini[4];
	int pivot = 0;
	spawn_cube(tetramini, 0, 0);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);

	rotate_block(tetramini, pivot, &map);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 0);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(rotate_triangle)
{
	tetramino_t tetramini[4];
	int pivot = 2;
	spawn_triangle(tetramini, 1, 0);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);

	rotate_block(tetramini, pivot, &map);

	ASSERT_THAT(tetramini[0].x == 2);
	ASSERT_THAT(tetramini[0].y == 1);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 0);

	ASSERT_THAT(tetramini[2].x == 1);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 1);
	ASSERT_THAT(tetramini[3].y == 2);
}

TEST(rotate_triangle_red_light)
{
	tetramino_t tetramini[4];
	int pivot = 2;
	spawn_triangle(tetramini, 1, 0);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);
	map.cells[9] = 1;

	rotate_block(tetramini, pivot, &map);

	ASSERT_THAT(tetramini[0].x == 1);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 0);
	ASSERT_THAT(tetramini[1].y == 1);

	ASSERT_THAT(tetramini[2].x == 1);
	ASSERT_THAT(tetramini[2].y == 1);

	ASSERT_THAT(tetramini[3].x == 2);
	ASSERT_THAT(tetramini[3].y == 1);
}

TEST(rotate_line)
{
	tetramino_t tetramini[4];
	int pivot = 2;
	spawn_line(tetramini, 0, 2);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);

	rotate_block(tetramini, pivot, &map);

	ASSERT_THAT(tetramini[0].x == 2);
	ASSERT_THAT(tetramini[0].y == 0);

	ASSERT_THAT(tetramini[1].x == 2);
	ASSERT_THAT(tetramini[1].y == 1);

	ASSERT_THAT(tetramini[2].x == 2);
	ASSERT_THAT(tetramini[2].y == 2);

	ASSERT_THAT(tetramini[3].x == 2);
	ASSERT_THAT(tetramini[3].y == 3);
}

TEST(rotate_line_red_light)
{
	tetramino_t tetramini[4];
	int pivot = 2;
	spawn_line(tetramini, 0, 2);

	tetris_map_t map;
	tetris_map_init(&map, 4, 4);
	map.cells[2] = 1;

	rotate_block(tetramini, pivot, &map);

	ASSERT_THAT(tetramini[0].x == 0);
	ASSERT_THAT(tetramini[0].y == 2);

	ASSERT_THAT(tetramini[1].x == 1);
	ASSERT_THAT(tetramini[1].y == 2);

	ASSERT_THAT(tetramini[2].x == 2);
	ASSERT_THAT(tetramini[2].y == 2);

	ASSERT_THAT(tetramini[3].x == 3);
	ASSERT_THAT(tetramini[3].y == 2);
}

TEST(tetramino_map_init)
{
	tetris_map_t tetris_map;
	tetris_map_init(&tetris_map, 1, 1);

	ASSERT_THAT(tetris_map.cells[0] == 0);
}

TEST(remove_full_line)
{
	tetris_map_t map;
	tetris_map_init(&map, 4, 2);

	map.cells[4] = 1;
	map.cells[5] = 1;
	map.cells[6] = 1;
	map.cells[7] = 1;

	int rows[4];
	rows[0] = 1;

	remove_full_lines(&map, rows, 1);

	ASSERT_THAT(map.cells[4] == 0);
	ASSERT_THAT(map.cells[5] == 0);
	ASSERT_THAT(map.cells[6] == 0);
	ASSERT_THAT(map.cells[7] == 0);
}

TEST(remove_multiple_lines)
{
	tetris_map_t map;
	tetris_map_init(&map, 4, 4);

	map.cells[4] = 1;
	map.cells[5] = 1;
	map.cells[6] = 1;
	map.cells[7] = 1;

	map.cells[8] = 1;
	map.cells[9] = 1;
	map.cells[10] = 1;
	map.cells[11] = 1;

	map.cells[12] = 1;
	map.cells[13] = 1;
	map.cells[14] = 1;
	map.cells[15] = 1;

	int rows[4];
	rows[0] = 1;
	rows[1] = 2;
	rows[2] = 3;

	remove_full_lines(&map, rows, 3);

	ASSERT_THAT(map.cells[4] == 0);
	ASSERT_THAT(map.cells[5] == 0);
	ASSERT_THAT(map.cells[6] == 0);
	ASSERT_THAT(map.cells[7] == 0);

	ASSERT_THAT(map.cells[8] == 0);
	ASSERT_THAT(map.cells[9] == 0);
	ASSERT_THAT(map.cells[10] == 0);
	ASSERT_THAT(map.cells[11] == 0);

	ASSERT_THAT(map.cells[12] == 0);
	ASSERT_THAT(map.cells[13] == 0);
	ASSERT_THAT(map.cells[14] == 0);
	ASSERT_THAT(map.cells[15] == 0);
}

TEST(check_for_full_lines)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, 0);

	tetris_map_t map;
	tetris_map_init(&map, 2, 2);

	map.cells[0] = 1;
	map.cells[1] = 1;
	map.cells[2] = 1;
	map.cells[3] = 1;

	int rows[4];
	int res = check_for_full_lines(tetramini, &map, rows);

	ASSERT_THAT(res == 2);
	ASSERT_THAT(rows[0] == 0);
	ASSERT_THAT(rows[1] == 1);
}

TEST(check_for_full_lines_same_positions)
{
	tetramino_t tetramini[4];
	tetramini[0].x = 0;
	tetramini[0].y = 0;

	tetramini[1].x = 0;
	tetramini[1].y = 0;

	tetramini[2].x = 0;
	tetramini[2].y = 0;

	tetramini[3].x = 0;
	tetramini[3].y = 0;

	tetris_map_t map;
	tetris_map_init(&map, 2, 1);

	map.cells[0] = 1;
	map.cells[1] = 1;

	int rows[4];
	int res = check_for_full_lines(tetramini, &map, rows);

	ASSERT_THAT(res == 1);
	ASSERT_THAT(rows[0] == 0);
}

TEST(check_for_full_lines_columns)
{
	tetramino_t tetramini[4];
	tetramini[0].x = 0;
	tetramini[0].y = 0;

	tetramini[1].x = 0;
	tetramini[1].y = 1;

	tetramini[2].x = 0;
	tetramini[2].y = 2;

	tetramini[3].x = 0;
	tetramini[3].y = 3;

	tetris_map_t map;
	tetris_map_init(&map, 2, 4);

	map.cells[0] = 1;
	map.cells[1] = 1;
	map.cells[2] = 1;
	map.cells[3] = 1;
	map.cells[4] = 1;
	map.cells[5] = 1;
	map.cells[6] = 1;
	map.cells[7] = 1;

	int rows[4];
	int res = check_for_full_lines(tetramini, &map, rows);

	ASSERT_THAT(res == 4);
	ASSERT_THAT(rows[0] == 0);
	ASSERT_THAT(rows[1] == 1);
	ASSERT_THAT(rows[2] == 2);
	ASSERT_THAT(rows[3] == 3);
}

TEST(check_for_full_lines_red_light)
{
	tetramino_t tetramini[4];
	spawn_cube(tetramini, 0, 0);

	tetris_map_t map;
	tetris_map_init(&map, 4, 2);

	map.cells[0] = 1;
	map.cells[1] = 1;
	map.cells[2] = 0;
	map.cells[3] = 0;
	map.cells[4] = 1;
	map.cells[5] = 1;
	map.cells[6] = 0;
	map.cells[7] = 0;

	int rows[4];
	int res = check_for_full_lines(tetramini, &map, rows);

	ASSERT_THAT(res == 0);
}

int main(int argc, char **argv)
{
	RUN_TEST(tetramino_init);
	RUN_TEST(tetramino_map_init);

	RUN_TEST(spawn_cube);
	RUN_TEST(spawn_line);
	RUN_TEST(spawn_right_l);
	RUN_TEST(spawn_left_l);
	RUN_TEST(spawn_right_z);
	RUN_TEST(spawn_left_z);
	RUN_TEST(spawn_triangle);

	RUN_TEST(tetramino_move_down_check);
	RUN_TEST(tetramino_move_down_check_red_light);
	RUN_TEST(tetramino_move_down_check_multiple_block);

	RUN_TEST(tetramino_move_down);
	RUN_TEST(tetramino_move_down_wrong_value);

	RUN_TEST(tetramino_busy_cell);
	RUN_TEST(tetramino_fill_two_blocks);

	RUN_TEST(move_all_right);
	RUN_TEST(move_all_right_border);
	RUN_TEST(tetramino_move_right_check);
	RUN_TEST(tetramino_move_right_check_blocked);
	RUN_TEST(tetramino_move_right);
	RUN_TEST(tetramino_move_right_blocked);
	RUN_TEST(tetramino_move_right_multiple);

	RUN_TEST(move_all_left);
	RUN_TEST(move_all_left_border);
	RUN_TEST(tetramino_move_left_check);
	RUN_TEST(tetramino_move_left_check_blocked);
	RUN_TEST(tetramino_move_left);
	RUN_TEST(tetramino_move_left_blocked);
	RUN_TEST(tetramino_move_left_multiple);

	RUN_TEST(move_all_down);
	RUN_TEST(move_all_down_end_map);
	RUN_TEST(move_all_down_occupied_cell);

	RUN_TEST(remove_full_line);
	RUN_TEST(remove_multiple_lines);

	RUN_TEST(try_rotate_cube);

	RUN_TEST(rotate_triangle);
	RUN_TEST(rotate_triangle_red_light);

	RUN_TEST(rotate_line);
	RUN_TEST(rotate_line_red_light);

	RUN_TEST(check_for_full_lines);
	RUN_TEST(check_for_full_lines_same_positions);
	RUN_TEST(check_for_full_lines_columns);
	RUN_TEST(check_for_full_lines_red_light);

	PRINT_TEST_RESULTS();
	return 0;
}
