#include "game.h"

#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

#define BOARD_PLAYER_1 'X'
#define BOARD_PLAYER_2 'O'
#define BOARD_BLANK '_'
#define BOARD_ROWS 3
#define BOARD_COLUMNS 3

#define INDEX2D1D(X, Y) (BOARD_ROWS * Y + X)
#define INDEX1D2D(INDEX) \
  (Vector2) { .x = INDEX % BOARD_ROWS, .y = INDEX / BOARD_COLUMNS, }

Game* game_construct(void) {
  Game* game= (Game*)malloc(sizeof(Game));

  game->buffer = (char*)malloc(sizeof(char) * BOARD_ROWS * BOARD_COLUMNS);

  for (size_t index = 0; index < BOARD_ROWS * BOARD_COLUMNS; ++index) {
    game->buffer[index] = BOARD_BLANK;
  }

  game->state = GAME_STATE_UNFINISHED;

  return game;
}

void game_destruct(Game* game) {
  free(game->buffer);

  free(game);
}

static void draw_game_board(void) {
  DrawLine(0, WINDOW_SECOND_THIRD, WINDOW_SIZE, WINDOW_SECOND_THIRD, BLACK);

  DrawLine(0, WINDOW_THIRD_THIRD, WINDOW_SIZE, WINDOW_THIRD_THIRD, BLACK);

  DrawLine(WINDOW_SECOND_THIRD, 0, WINDOW_SECOND_THIRD, WINDOW_SIZE, BLACK);

  DrawLine(WINDOW_THIRD_THIRD, 0, WINDOW_THIRD_THIRD, WINDOW_SIZE, BLACK);
}

static void draw_player_1(const int x, const int y) {
  DrawLine(x, y, WINDOW_CELL_SIZE + x, WINDOW_CELL_SIZE + y, RED);

  DrawLine(WINDOW_CELL_SIZE + x, y, x, WINDOW_CELL_SIZE + y, RED);
}

static void draw_player_2(const int x, const int y) {
  const int radius = (WINDOW_CELL_SIZE / 2) - WINDOW_OFFSET;

  const int inner_radius = radius - WINDOW_HALF_OFFSET;

  const int outer_radius = radius + WINDOW_HALF_OFFSET;

  DrawRing(
      (Vector2){
          .x = x + radius + WINDOW_OFFSET,
          .y = y + radius + WINDOW_OFFSET,
      },
      inner_radius, outer_radius, 0, 360, 30, BLUE);
}

static int current_cell_third(int point) {
  if (point < WINDOW_SECOND_THIRD) {
    return WINDOW_FIRST_THIRD;
  }

  if (point < WINDOW_THIRD_THIRD) {
    return WINDOW_SECOND_THIRD;
  }

  return WINDOW_THIRD_THIRD;
}

static void draw_hover(void) {
  if (!IsCursorOnScreen()) {
    return;
  }

  const Vector2 mouse = GetMousePosition();

  const int x = current_cell_third(mouse.x);

  const int y = current_cell_third(mouse.y);

  DrawRectangleRoundedLinesEx(
      (Rectangle){
          .x = x + WINDOW_OFFSET / 2,
          .y = y + WINDOW_OFFSET / 2,
          .width = WINDOW_CELL_SIZE - WINDOW_OFFSET,
          .height = WINDOW_CELL_SIZE - WINDOW_OFFSET,
      },
      .15, 1, 4, BLUE);
}

void Game::Draw(void) const {
  draw_hover();

  draw_game_board();

  for (size_t index = 0; index < BOARD_ROWS * BOARD_COLUMNS; ++index) {
    const Vector2 point = Vector2Scale(INDEX1D2D(index), WINDOW_CELL_SIZE);

    const int x = point.x;

    const int y = point.y;

    switch (this->buffer[index]) {
      case BOARD_PLAYER_1:
        draw_player_1(x, y);
        break;
      case BOARD_PLAYER_2:
        draw_player_2(x, y);
        break;
      case BOARD_BLANK:
        break;
    }
  }
}

static bool cells_are_equal(const Game* game, const size_t i, const size_t j,
                            const size_t k, const char buffer) {
  return game->buffer[i] == game->buffer[j] &&
         game->buffer[i] == game->buffer[k] && game->buffer[i] == buffer;
}

static bool row_cells_are_equal(const Game* game, const size_t row,
                                const char player) {
  const size_t i = INDEX2D1D(0, row);

  const size_t j = INDEX2D1D(1, row);

  const size_t k = INDEX2D1D(2, row);

  return cells_are_equal(game, i, j, k, player);
}

static bool column_cells_are_equal(const Game* game, const size_t column,
                                   const char player) {
  const size_t i = INDEX2D1D(column, 0);

  const size_t j = INDEX2D1D(column, 1);

  const size_t k = INDEX2D1D(column, 2);

  return cells_are_equal(game, i, j, k, player);
}

static bool primary_diagonal_cells_are_equal(const Game* game,
                                             const char player) {
  const size_t i = INDEX2D1D(0, 0);

  const size_t j = INDEX2D1D(1, 1);

  const size_t k = INDEX2D1D(2, 2);

  return cells_are_equal(game, i, j, k, player);
}

static bool secondary_diagonal_cells_are_equal(const Game* game,
                                               const char player) {
  const size_t i = INDEX2D1D(0, 2);

  const size_t j = INDEX2D1D(1, 1);

  const size_t k = INDEX2D1D(2, 0);

  return cells_are_equal(game, i, j, k, player);
}

static bool have_player_won(const Game* game, const char player) {
  if (primary_diagonal_cells_are_equal(game, player)) {
    return true;
  }

  if (secondary_diagonal_cells_are_equal(game, player)) {
    return true;
  }

  for (size_t index = 0; index < BOARD_ROWS; ++index) {
    if (row_cells_are_equal(game, index, player)) {
      return true;
    }

    if (column_cells_are_equal(game, index, player)) {
      return true;
    }
  }

  return false;
}

static GameState current_game_state(const Game* game) {
  if (have_player_won(game, BOARD_PLAYER_1)) {
    return GAME_STATE_PLAYER_1_WON;
  }

  if (have_player_won(game, BOARD_PLAYER_2)) {
    return GAME_STATE_PLAYER_2_WON;
  }

  // TODO: check for game_draw

  return GAME_STATE_UNFINISHED;
}

static void game_input(Game* game) {
  if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      !IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    return;
  }

  const Vector2 position = GetMousePosition();

  const int x = (int)(BOARD_COLUMNS * position.x / WINDOW_SIZE);

  const int y = (int)(BOARD_ROWS * position.y / WINDOW_SIZE);

  const size_t index = INDEX2D1D(x, y);

  if (game->buffer[index] != BOARD_BLANK) {
    return;
  }

  const char player =
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ? BOARD_PLAYER_1 : BOARD_PLAYER_2;

  game->buffer[index] = player;
}

void Game::Update() {
  game_input(this);

  this->state = current_game_state(this);
}

bool Game::IsRunning() const {
  return this->state == GAME_STATE_UNFINISHED;
}
