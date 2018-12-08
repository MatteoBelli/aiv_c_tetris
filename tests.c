#include "aiv_unit_test.h"
#include "tetris.h"

#define TETRAMINO_INIT(tetramino_pointer, map_pointer)  \
	{                                                   \
		tetramino_init(tetramino_pointer, map_pointer); \
	}


#define TETRAMINO_SETUP(width, height)             \
	tetramino_t tetramino;                         \
	tetris_map_t *tetris_map = NULL;               \
	tetris_map_init(tetris_map, width, height); \
	tetramino_init(&tetramino, tetris_map)

#define TETRAMINO_MOVE_DOWN(tetramino_pointer, map_pointer)                                        \
	{                                                                                              \
		int dead_cell;                                                                             \
		if (tetramino_move_down_check(tetramino_pointer, map_pointer, &dead_cell) == TETRAMINO_OK) \
		{                                                                                          \
			tetramino_move_down(tetramino_pointer);                                                \
		}                                                                                          \
		else                                                                                       \
		{                                                                                          \
			*tetris_map[dead_cell].cell = 1;                                                       \
		}                                                                                          \
	}

TEST(tetramino_init)
{
	TETRAMINO_SETUP(1, 1);

	ASSERT_THAT(tetramino.y == -1);
}

TEST(tetramino_move_down_check)
{
	TETRAMINO_SETUP(1, 1);
	int dead_cell;
	int res = tetramino_move_down_check(&tetramino, tetris_map, &dead_cell);

	ASSERT_THAT(res == TETRAMINO_OK);
}

TEST(tetramino_move_down_check_red_light)
{
	TETRAMINO_SETUP(1, 1);
	tetramino.y = 0;
	int dead_cell;
	int res = tetramino_move_down_check(&tetramino, tetris_map, &dead_cell);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_down_check_multiple_block)
{
	TETRAMINO_SETUP(1, 1);
	tetramino.y = 0;
	int dead_cell;
	tetramino_move_down_check(&tetramino, tetris_map, &dead_cell);
	*tetris_map[dead_cell].cell = 1;
	tetramino_t tetramino2;
	tetramino_init(&tetramino2, tetris_map);
	int res = tetramino_move_down_check(&tetramino2, tetris_map, &dead_cell);

	ASSERT_THAT(res == TETRAMINO_DEAD);
}

TEST(tetramino_move_down)
{
	TETRAMINO_SETUP(1, 1);
	tetramino_move_down(&tetramino);

	ASSERT_THAT(tetramino.y == 0);
}

TEST(tetramino_move_down_wrong_value)
{
	TETRAMINO_SETUP(1, 1);
	tetramino.y = 100;
	int dead_cell;
	if (tetramino_move_down_check(&tetramino, tetris_map, &dead_cell) == TETRAMINO_OK)
	{
		tetramino_move_down(&tetramino);
	}

	ASSERT_THAT(tetramino.y == 100);
}

TEST(tetramino_move_right_blocked)
{
	TETRAMINO_SETUP(1, 1);
	tetramino_move_right(&tetramino, tetris_map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_right)
{
	TETRAMINO_SETUP(2, 1);
	tetramino_move_right(&tetramino, tetris_map);

	ASSERT_THAT(tetramino.x == 1);
}

TEST(tetramino_move_right_multiple)
{
	TETRAMINO_SETUP(2, 1);
	tetramino_move_right(&tetramino, tetris_map);
	tetramino_move_right(&tetramino, tetris_map);

	ASSERT_THAT(tetramino.x == 1);
}

TEST(tetramino_move_left_blocked)
{
	TETRAMINO_SETUP(1, 1);
	tetramino_move_left(&tetramino, tetris_map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_left)
{
	TETRAMINO_SETUP(2, 1);
	tetramino.x = 1;
	tetramino.y = 0;
	tetramino_move_left(&tetramino, tetris_map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_move_left_multiple)
{
	TETRAMINO_SETUP(2, 1);
	tetramino.x = 1;
	tetramino.y = 0;
	tetramino_move_left(&tetramino, tetris_map);
	tetramino_move_left(&tetramino, tetris_map);

	ASSERT_THAT(tetramino.x == 0);
}

TEST(tetramino_busy_cell)
{
	TETRAMINO_SETUP(1, 1);

	TETRAMINO_MOVE_DOWN(&tetramino, tetris_map);
	TETRAMINO_MOVE_DOWN(&tetramino, tetris_map);

	tetramino_t tetramino2;
	tetramino_init(&tetramino2, tetris_map);

	TETRAMINO_MOVE_DOWN(&tetramino, tetris_map);
	TETRAMINO_MOVE_DOWN(&tetramino, tetris_map);

	ASSERT_THAT(tetramino2.y == -1);
}

TEST(tetramino_fill_two_blocks)
{
	TETRAMINO_SETUP(1, 2);

	TETRAMINO_MOVE_DOWN(&tetramino, tetris_map);
	TETRAMINO_MOVE_DOWN(&tetramino, tetris_map);
	TETRAMINO_MOVE_DOWN(&tetramino, tetris_map);

	ASSERT_THAT(tetramino.y == 1);

	tetramino_t tetramino2;
	tetramino_init(&tetramino2, tetris_map);

	TETRAMINO_MOVE_DOWN(&tetramino, tetris_map);
	TETRAMINO_MOVE_DOWN(&tetramino, tetris_map);
	TETRAMINO_MOVE_DOWN(&tetramino, tetris_map);

	ASSERT_THAT(tetramino2.y == 0);
}

TEST(tetramino_map_init)
{
	tetris_map_t tetris_map;
	tetris_map_init(&tetris_map, 1, 1);

	ASSERT_THAT(tetris_map.cell[0] == 0);
}

int main(int argc, char **argv)
{
	RUN_TEST(tetramino_init);
	RUN_TEST(tetramino_map_init);

	RUN_TEST(tetramino_move_down_check);
	RUN_TEST(tetramino_move_down_check_red_light);
	RUN_TEST(tetramino_move_down_check_multiple_block);

	RUN_TEST(tetramino_move_down);
	RUN_TEST(tetramino_move_down_wrong_value);

	RUN_TEST(tetramino_busy_cell);
	RUN_TEST(tetramino_fill_two_blocks);

	RUN_TEST(tetramino_move_right);
	RUN_TEST(tetramino_move_right_blocked);
	RUN_TEST(tetramino_move_right_multiple);

	RUN_TEST(tetramino_move_left);
	RUN_TEST(tetramino_move_left_blocked);
	RUN_TEST(tetramino_move_left_multiple);

	PRINT_TEST_RESULTS();
	return 0;
}
