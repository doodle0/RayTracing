#include "vector.h"

V2f::V2f(const Vec<2, float, float> &rhs) : Vec<2, float, float>(rhs) {}
V2f::V2f(float x, float y) : Vec<2, float, float>(x, y) {}
const float &V2f::x() const { return elems[0]; }
const float &V2f::y() const { return elems[1]; }
float &V2f::x() { return elems[0]; }
float &V2f::y() { return elems[1]; }

V3f::V3f(const Vec<3, float, float> &rhs) : Vec<3, float, float>(rhs) {}
V3f::V3f(float x, float y, float z) : Vec<3, float, float>(x, y, z) {}
const float &V3f::x() const { return elems[0]; }
const float &V3f::y() const { return elems[1]; }
const float &V3f::z() const { return elems[2]; }
float &V3f::x() { return elems[0]; }
float &V3f::y() { return elems[1]; }
float &V3f::z() { return elems[2]; }

V3f V3f::Cross(const V3f &o) const {
  return V3f(y() * o.z() - z() * o.y(),
             z() * o.x() - x() * o.z(),
             x() * o.y() - y() * o.x());
}
