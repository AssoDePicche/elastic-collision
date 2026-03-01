#include "hud_layer.h"

#include <raylib.h>

void HUD_Layer::Render(const float alpha) {
  const char *copyright = "AssoDePicche © 2025";

  const int fontSize = 20;

  DrawText(copyright, 20, 20, fontSize, DARKGRAY);
}

void HUD_Layer::Update(const core::Clock::Tick &tick) {
}
