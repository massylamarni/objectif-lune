#include "time.h"

namespace core {
static std::chrono::high_resolution_clock::time_point last;
static float delta = 0.0f;

void time_update() {
  auto now = std::chrono::high_resolution_clock::now();

  if (last.time_since_epoch().count() == 0) {
    last = now;
    delta = 0.0f;
    return;
  }

  delta = std::chrono::duration<float>(now - last).count();

  last = now;
}

float time_delta() { return delta; }
} // namespace core