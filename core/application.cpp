#include "application.h"

namespace raylib {
#include <raylib.h>
}

#include "clock.h"

namespace core {
  Application::Application() : clock(0.25f) {}

  Application::~Application() {
    raylib::CloseWindow();
  }

  void Application::Run() {
    raylib::InitWindow(640, 640, "Bouncing Balls");

    raylib::SetTargetFPS(60);

    raylib::SetExitKey(raylib::KEY_Q);

    raylib::SetRandomSeed(0);

    running = true;

    const float deltaTime = 1.0f / static_cast<float>(60.0f);

    float accumulator = 0.0f;

    while (running) {
      if (raylib::WindowShouldClose()) {
        Stop();
      }

      const Clock::Tick tick = clock.tick();

      accumulator += tick.delta;

      while (accumulator >= deltaTime) {
        for (const auto& layer : stack) {
          layer->Update(tick);
        }

        accumulator -= deltaTime;
      }

      const float alpha = accumulator / deltaTime;

      raylib::BeginDrawing();

      raylib::ClearBackground(raylib::WHITE);

      for (const auto& layer : stack) {
        layer->Render(alpha);
      }

      raylib::EndDrawing();
    }
  }

  void Application::Stop() {
    running = false;
  }
}
