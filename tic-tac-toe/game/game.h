#ifndef __GAME__
#define __GAME__

#include <stdbool.h>

#define WINDOW_OFFSET 20
#define WINDOW_HALF_OFFSET (WINDOW_OFFSET / 2)
#define WINDOW_SIZE (640 + WINDOW_OFFSET)
#define WINDOW_CELL_SIZE (WINDOW_SIZE / 3)
#define WINDOW_FIRST_THIRD 0
#define WINDOW_SECOND_THIRD (WINDOW_SIZE / 3)
#define WINDOW_THIRD_THIRD (2 * WINDOW_SECOND_THIRD)

enum GameState {
  GAME_STATE_PLAYER_1_WON,
  GAME_STATE_PLAYER_2_WON,
  GAME_STATE_DRAW,
  GAME_STATE_UNFINISHED,
};

struct Game {
  GameState state;
  char *buffer;

  void Draw(void) const;

  bool IsRunning(void) const;

  void Update();
};

Game* game_construct(void);

void game_destruct(Game*);

#endif
