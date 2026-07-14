#include "game_layer.h"

#define MAX_BALLS 32

GameLayer::GameLayer() {
  balls.push_back(Ball::New());
}

GameLayer::~GameLayer() {
  for (auto& ball : balls) {
    ball->Destroy();
  }
}

void GameLayer::Render(const float alpha) {
  for (const auto& ball : balls) {
    ball->Draw();
  }
}

void GameLayer::Update(const core::Clock::Tick &tick) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && balls.size() < MAX_BALLS) {
    balls.push_back(Ball::New());
  }

  if (IsKeyPressed(KEY_R)) {
    for (auto &ball : balls) {
      ball->Destroy();
    }

    balls.clear();

    balls.push_back(Ball::New());
  }

  for (size_t i = 0; i < balls.size(); ++i) {
    for (size_t j = 0; j < balls.size(); ++j) {
      if (i == j) {
        continue;
      }

      balls[i]->Collide(balls[j]);
    }

    balls[i]->Update(tick.delta);
  }
}
