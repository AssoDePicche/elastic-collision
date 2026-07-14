#pragma once

#include "clock.h"

namespace core {
  class Layer {
    public:
      virtual ~Layer() = default;

      virtual void Render(const float) = 0;

      virtual void Update(const Clock::Tick &) = 0;
  };
}
