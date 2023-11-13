#ifndef __COLOR_H__
#define __COLOR_H__

#include "vector.h"
#include "bitmap.h"

struct Color : V3f {
  Color() = default;
  Color(const Color &rhs) = default;
  Color(const V3f &v);
  Color(float r, float g, float b);
  const float &r() const;
  const float &g() const;
  const float &b() const;
  float &r();
  float &g();
  float &b();
  Pixel ToPixel();
};

#endif // __COLOR_H__