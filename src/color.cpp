#include "color.h"

Color::Color(const V3f &v) : V3f(v) {}

Color::Color(float r, float g, float b) : V3f(r, g, b) {}

const float &Color::r() const { return elems[0]; }
const float &Color::g() const { return elems[1]; }
const float &Color::b() const { return elems[2]; }

Pixel Color::ToPixel() {
  return Pixel(std::clamp<int>(256 * r(), 0, 255),
               std::clamp<int>(256 * g(), 0, 255),
               std::clamp<int>(256 * b(), 0, 255));
}
