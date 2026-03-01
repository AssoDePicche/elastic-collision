#pragma once

#include <cstdint>

#include <core/layer.h>

#define MAX_BALLS 32

#include "ball.h"

class GameLayer : public core::Layer {
  public:
    GameLayer();

    ~GameLayer();

    void Render(const float) override;

    void Update(const core::Clock::Tick &) override;

  private:
    Ball *balls[MAX_BALLS];
    size_t size;
};
