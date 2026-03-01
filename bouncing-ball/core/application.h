#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "layer.h"

namespace core {
  class Clock;

  class Application {
    public:
      Application();

      ~Application();

      Application(const Application &) = delete;

      Application &operator=(const Application &) = delete;

      void Run();

      void Stop();

      template<typename T, typename... Args>
      requires std::derived_from<T, Layer>
      void Push(Args&&... args) {
        stack.push_back(std::make_unique<T>(std::forward<Args>(args)...));
      }

    private:
      Clock clock;
      std::vector<std::unique_ptr<Layer>> stack;
      bool running = false;
  };
}
