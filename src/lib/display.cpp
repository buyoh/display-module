#include <cstdlib>

#include "./display.hpp"

extern "C" {
#include "../third_party/e-paper/EPD_4in2.h"
}

void EPaperDriver::initialize() {
  if (DEV_Module_Init() != 0) {
    abort();
  }
  EPD_4IN2_Init_4Gray();
}

int EPaperDriver::width() { return EPD_4IN2_WIDTH; }
int EPaperDriver::height() { return EPD_4IN2_HEIGHT; };

void EPaperDriver::release() {
  // EPD_4IN2_Init();  // ?
  // EPD_4IN2_Clear(); // ?
  EPD_4IN2_Sleep();
  DEV_Delay_ms(2000);
  DEV_Module_Exit();
}

void EPaperDriver::sleepDeviceMs(int ms) { DEV_Delay_ms(ms); }

void EPaperDriver::display(const EPaperCanvasGray4 &canvas) {
  assert(canvas.width() == width());
  assert(canvas.height() == height());

  // EPD_4IN2_Display(BlackImage);
  EPD_4IN2_4GrayDisplay((const uint8_t *)canvas.data());
}
