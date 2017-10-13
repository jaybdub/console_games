#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdint.h>

#define BOARD_SIZE 3

/*********************************************************************************
    TYPES
 *********************************************************************************/

typedef enum
{
  PLAYER_DEFAULT = 0,
  PLAYER_1 = 1,
  PLAYER_2 = 2
} t3_player_t;

typedef enum
{
  STATUS_PLAYER_1_TURN = 0,
  STATUS_PLAYER_2_TURN = 1,
  STATUS_PLAYER_1_VICTORY = 2,
  STATUS_PLAYER_2_VICTORY = 3,
  STATUS_CATS
} t3_status_t;

typedef struct 
{
  t3_player_t player;
  t3_player_t board[BOARD_SIZE][BOARD_SIZE];
} t3_game_t;

/*********************************************************************************
    DECLARATIONS
 *********************************************************************************/

t3_game_t t3_game_create(t3_player_t first_player);
int t3_make_move(t3_game_t * game, uint8_t x, uint8_t y);
t3_status_t t3_get_status(t3_game_t * game);
int t3_has_open_slot(t3_game_t * game);
t3_status_t t3_player_victory_status(t3_player_t player);
t3_status_t t3_player_turn_status(t3_player_t player);


/*********************************************************************************
    DEFINITIONS
 *********************************************************************************/

t3_game_t t3_game_create(t3_player_t first_player) {
  t3_game_t game;
  game.player = first_player;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      game.board[i][j] = PLAYER_DEFAULT;
  return game;
}

int t3_make_move(t3_game_t * game, uint8_t x, uint8_t y)
{
  // Coordinates are out of range.
  if (x >= BOARD_SIZE || y >= BOARD_SIZE)
    return 0;

  // Slot is not empty.
  if (game->board[x][y])
    return 0;

  // Set board and update player.
  game->board[x][y] = game->player;

  if (game->player == PLAYER_1)
    game->player = PLAYER_2;
  else
    game->player = PLAYER_1;

  return 1;
}

int t3_has_open_slot(t3_game_t * game)
{
  // check to see if there are any open slots
  int open_slots = 0;
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      if (game->board[i][j] == PLAYER_DEFAULT)
        open_slots = 1;
  return open_slots;
}

t3_status_t t3_player_victory_status(t3_player_t player)
{
  if (player == PLAYER_1)
    return STATUS_PLAYER_1_VICTORY;
  else
    return STATUS_PLAYER_2_VICTORY;
}

t3_status_t t3_player_turn_status(t3_player_t player)
{
  if (player == PLAYER_1)
    return STATUS_PLAYER_1_TURN;
  else
    return STATUS_PLAYER_2_TURN;
}

t3_status_t t3_get_status(t3_game_t * game)
{
  // check center
  if (game->board[1][1])
  {
    const t3_player_t player = game->board[1][1];

    // column
    if (game->board[0][1] == player && game->board[2][1] == player)
      return t3_player_victory_status(player);

    // row
    if (game->board[1][0] == player && game->board[1][2] == player)
      return t3_player_victory_status(player);

    // diagonal 1
    if (game->board[0][0] == player && game->board[2][2] == player)
      return t3_player_victory_status(player);

    // diagonal 2
    if (game->board[0][2] == player && game->board[2][0] == player)
      return t3_player_victory_status(player);
  }

  // check top row
  if (game->board[0][1]) 
  {
    const t3_player_t player = game->board[0][1];
    if (game->board[0][0] == player && game->board[0][2] == player)
      return t3_player_victory_status(player);
  }

  // check bottom row
  if (game->board[2][1])
  {
    const t3_player_t player = game->board[2][1];
    if (game->board[2][0] == player && game->board[2][2] == player)
      return t3_player_victory_status(player);
  }
   
  // check left column
  if (game->board[1][0])
  {
    const t3_player_t player = game->board[1][0];
    if (game->board[0][0] == player && game->board[2][0] == player)
      return t3_player_victory_status(player);
  }
  
  // check right column
  if (game->board[1][2])
  {
    const t3_player_t player = game->board[1][2];
    if (game->board[0][2] == player && game->board[2][2] == player)
      return t3_player_victory_status(player);
  }

  if (t3_has_open_slot(game))
    return t3_player_turn_status(game->player);

  return STATUS_CATS;
}

#endif  // TICTACTOE_H
