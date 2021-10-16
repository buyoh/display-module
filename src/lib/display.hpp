#ifndef LIB_DISPLAY_HPP_
#define LIB_DISPLAY_HPP_

#include "./canvas.hpp"

class EPaperDriver {
public:
  static EPaperDriver &getInstance() {
    static EPaperDriver instance;
    return instance;
  }

  void initialize();
  void release();

  void sleepDeviceMs(int ms);

  int width();
  int height();

  void display(const EPaperCanvasGray4 &canvas);

private:
  EPaperDriver() {}
};

#endif // LIB_DISPLAY_HPP_
