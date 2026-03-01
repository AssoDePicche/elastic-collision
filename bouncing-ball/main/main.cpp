#include <core/application.h>

#include <game/game_layer.h>
#include <game/hud_layer.h>

int main(void) {
  core::Application application;

  application.Push<GameLayer>();

  application.Push<HUD_Layer>();

  application.Run();

  return 0;
}
