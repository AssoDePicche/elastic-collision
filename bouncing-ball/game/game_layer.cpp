#include "game_layer.h"

GameLayer::GameLayer() {
  balls[size++] = Ball::New();
}

GameLayer::~GameLayer() {
  for (size_t index = 0; index < size; ++index) {
    balls[index]->Destroy();
  }
}

void GameLayer::Render(const float alpha) {
  for (size_t index = 0; index < size; ++index) {
    balls[index]->Draw();
  }
}

void GameLayer::Update(const core::Clock::Tick &tick) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && size < MAX_BALLS) {
    balls[size++] = Ball::New();
  }

  if (IsKeyPressed(KEY_R)) {
    for (size_t index = 0; index < size; ++index) {
      balls[index]->Destroy();
    }

    size = 0;

    balls[size++] = Ball::New();
  }

  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      if (i == j) {
        continue;
      }

      balls[i]->Collide(balls[j]);
    }

    balls[i]->Update(tick.delta);
  }
}
