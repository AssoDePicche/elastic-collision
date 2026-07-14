#pragma once

#include <core/layer.h>

class HUD_Layer : public core::Layer {
  public:
    void Render(const float alpha) override; 

    void Update(const core::Clock::Tick &) override;
};

