#include <signal.h>

#include <cstdlib>
#include <iostream>
#include <optional>

#include "../lib/canvas.hpp"
#include "../lib/display.hpp"

namespace Main {

void initialize() {
  //
  EPaperDriver::getInstance().initialize();
}

void finalize() {
  //
  EPaperDriver::getInstance().release();
}

void handleSigint(int s) {
  finalize();
  std::exit(0);
}

std::vector<char> raw_data;
std::optional<EPaperCanvasGray4> canvas;

uint8_t castColor(uint8_t color) { return color >> 6; }

bool loop() {
  auto &driver = EPaperDriver::getInstance();
  const int h = driver.height();
  const int w = driver.width();
  const int size = h * w;
  if (!canvas)
    canvas = std::make_optional<EPaperCanvasGray4>(h, w);
  raw_data.resize(size);
  std::cin.read(raw_data.data(), size);

  {
    uint8_t *p1 = (uint8_t *)raw_data.data();
    uint8_t *p2 = (uint8_t *)canvas->data();
    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w / 4; ++x) {
        *(++p2) = (castColor(*(p1++)) << 6) | (castColor(*(p1++)) << 4) |
                  (castColor(*(p1++)) << 2) | castColor(*(p1++));
      }
    }
  }
  driver.display(*canvas);

  return !std::cin.eof();
}

int main() {
  initialize();
  signal(SIGINT, handleSigint);

  while (loop())
    ;

  finalize();
  return 0;
}

} // namespace Main

int main() { return Main::main(); }
