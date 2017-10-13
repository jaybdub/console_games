#include <stdio.h>
#include "src/tictactoe/tictactoe.h"

void print_board(t3_game_t * game) 
{
  for (int i = 0; i < 3; i++)
    printf("%d %d %d\n", game->board[i][0], game->board[i][1],
        game->board[i][2]);
}

int prompt_move(t3_game_t * game, int * x, int * y)
{
  printf("\nEnter move for Player %d: ", game->player);
  scanf("%d %d", x, y);
  return 1;
}

t3_status_t update_game(t3_game_t * game)
{
  // 1. print board
  // 2. prompt move
  // 3. make move if valid, 
  print_board(game);
  int x, y;
  do
    prompt_move(game, &x, &y);
  while (!t3_make_move(game, x, y));
  return t3_get_status(game);
}

int main()
{
  t3_game_t game = t3_game_create(PLAYER_1);
  while (update_game(&game) < 2) 
    continue;

  switch (t3_get_status(&game))
  {
  case STATUS_PLAYER_1_VICTORY:
    printf("Player 1 wins!\n");
    break;
  case STATUS_PLAYER_2_VICTORY:
    printf("Player 2 wins!\n");
    break;
  default:
    printf("Cats!\n");
    break;
  }

  return 0;
}
