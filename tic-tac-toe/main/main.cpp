#include <raylib.h>

#include <game/game.h>

int main(void) {
  Game* game = game_construct();

  InitWindow(WINDOW_SIZE, WINDOW_SIZE, "Tic-tac-toe");

  SetTargetFPS(60);

  SetExitKey(KEY_Q);

  while (!WindowShouldClose() && game->IsRunning()) {
    game->Update();

    BeginDrawing();

    ClearBackground(WHITE);

    game->Draw();

    EndDrawing();
  }

  game_destruct(game);

  return 0;
}
