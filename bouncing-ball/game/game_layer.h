#pragma once

#include <cstdint>
#include <vector>

#include <core/layer.h>

#include "ball.h"

class GameLayer : public core::Layer {
  public:
    GameLayer();

    ~GameLayer();

    void Render(const float) override;

    void Update(const core::Clock::Tick &) override;

  private:
    std::vector<Ball *>balls;
};
