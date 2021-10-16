#ifndef LIB_CANVAS_HPP_
#define LIB_CANVAS_HPP_

#include <cassert>
#include <vector>

class EPaperCanvasGray4 {
public:
  EPaperCanvasGray4(int height, int width)
      : height_(height), width4_(width / 4), data_(width / 4 * height) {
    assert(width / 4 * 4 == width);
  };

  int width() const { return width4_ * 4; }
  int height() const { return height_; };

  char operator()(int y, int x) const {
    return data_[width4_ * y + x / 4] & (0x03 << (6 - (x / 4) * 2));
  }
  void set(int y, int x, int value) {
    const int i = x / 4;
    data_[width4_ * y + x / 4] &= 0xFF ^ (3 << (6 - i * 2));
    data_[width4_ * y + x / 4] |= (value << (6 - i * 2));
  }
  void reset() { std::fill(data_.begin(), data_.end(), 0); }

  void *data() { return data_.data(); }
  const void *data() const { return data_.data(); }

private:
  int width4_, height_;
  std::vector<char> data_;
};

#endif // LIB_CANVAS_HPP_
