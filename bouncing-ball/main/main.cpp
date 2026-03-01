#include <raylib.h>
#include <raymath.h>
#include <stddef.h>

#include <core/application.h>
#include <core/layer.h>

#include <game/game_layer.h>

class HUD_Layer : public core::Layer {
  public:
    void Render(const float alpha) override {
      const char *copyright = "AssoDePicche © 2025";

      const int fontSize = 20;

      DrawText(copyright, 20, 20, fontSize, DARKGRAY);
    }

    void Update(const core::Clock::Tick &tick) override {
    }
};

int main(void) {
  core::Application application;

  application.Push<GameLayer>();

  application.Push<HUD_Layer>();

  application.Run();

  return 0;
}
