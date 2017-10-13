#include <stdio.h>
#include "src/tictactoe/tictactoe.h"
#include <assert.h>

void test__new_board()
{
  t3_game_t game = t3_game_create(PLAYER_1);
  assert(game.player == PLAYER_1);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      assert(game.board[i][j] == PLAYER_DEFAULT);
}

void test__move()
{
  t3_game_t game = t3_game_create(PLAYER_1);

  int result;
  result = t3_make_move(&game, 0, 4);
  assert(result == 0);
  assert(game.player == PLAYER_1);
  result = t3_make_move(&game, 0, 0);
  assert(result == 1);
  assert(game.player == PLAYER_2);
  assert(game.board[0][0] == PLAYER_1);
  result = t3_make_move(&game, 0, 0);
  assert(result == 0);
  assert(game.player == PLAYER_2);
}

void test__status()
{
  // simple player 1 victory
  t3_game_t game = t3_game_create(PLAYER_1);
  assert(t3_get_status(&game) == STATUS_PLAYER_1_TURN);
  t3_make_move(&game, 0, 0);
  assert(t3_get_status(&game) == STATUS_PLAYER_2_TURN);
  t3_make_move(&game, 1, 0);
  assert(t3_get_status(&game) == STATUS_PLAYER_1_TURN);
  t3_make_move(&game, 0, 1);
  assert(t3_get_status(&game) == STATUS_PLAYER_2_TURN);
  t3_make_move(&game, 1, 1);
  assert(t3_get_status(&game) == STATUS_PLAYER_1_TURN);
  t3_make_move(&game, 0, 2);
  assert(t3_get_status(&game) == STATUS_PLAYER_1_VICTORY);

  // test cats
  game = t3_game_create(PLAYER_1);
  t3_make_move(&game, 0, 0);
  t3_make_move(&game, 1, 1);
  t3_make_move(&game, 0, 2);
  t3_make_move(&game, 0, 1);
  t3_make_move(&game, 2, 1);
  t3_make_move(&game, 1, 2);
  t3_make_move(&game, 1, 0);
  t3_make_move(&game, 2, 0);
  t3_make_move(&game, 2, 2);
  assert(t3_get_status(&game) == STATUS_CATS);

}

int main()
{
  test__new_board();
  test__move();
  test__status();
  return 0;
}
