#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>
#include <stddef.h>

template <size_t n, typename elem_t, typename real_t> struct Vec {
public:
  Vec() = default;
  Vec(const Vec &rhs) = default;
  template <typename... args> Vec(args... e);
  const elem_t &operator[](size_t idx) const;
  elem_t &operator[](size_t idx);
  Vec operator+(const Vec &o) const;
  Vec operator-(const Vec &o) const;
  Vec operator-() const;
  Vec operator*(const Vec &o) const; // element-wise product
  Vec operator*(elem_t k) const;
  Vec operator/(const Vec &o) const; // element-wise division
  Vec operator/(elem_t k) const;
  elem_t Dot(const Vec &o) const;
  elem_t SizeSquared() const;
  Vec Normalized() const;
  static Vec Interp(const Vec &a, const Vec &b, real_t k);

protected:
  elem_t elems[n];
};

template <size_t n, typename elem_t, typename real_t, typename Vec>
Vec operator*(elem_t k, const Vec &v);

template <size_t n, typename elem_t, typename real_t>
template <typename... args>
Vec<n, elem_t, real_t>::Vec(args... e) : elems{e...} {
  static_assert(sizeof...(e) == n, "Incorrect number of arguments");
}

template <size_t n, typename elem_t, typename real_t>
const elem_t &Vec<n, elem_t, real_t>::operator[](size_t idx) const {
  return elems[idx];
}

template <size_t n, typename elem_t, typename real_t>
elem_t &Vec<n, elem_t, real_t>::operator[](size_t idx) {
  return elems[idx];
}

template <size_t n, typename elem_t, typename real_t>
Vec<n, elem_t, real_t>
Vec<n, elem_t, real_t>::operator+(const Vec<n, elem_t, real_t> &o) const {
  Vec<n, elem_t, real_t> result;
  for (int i = 0; i < n; i++) {
    result[i] = elems[i] + o[i];
  }
  return result;
}

template <size_t n, typename elem_t, typename real_t>
Vec<n, elem_t, real_t>
Vec<n, elem_t, real_t>::operator-(const Vec<n, elem_t, real_t> &o) const {
  Vec<n, elem_t, real_t> result;
  for (int i = 0; i < n; i++) {
    result[i] = elems[i] - o[i];
  }
  return result;
}

template <size_t n, typename elem_t, typename real_t>
Vec<n, elem_t, real_t> Vec<n, elem_t, real_t>::operator-() const {
  Vec<n, elem_t, real_t> result;
  for (int i = 0; i < n; i++) {
    result[i] = -elems[i];
  }
  return result;
}

template <size_t n, typename elem_t, typename real_t>
Vec<n, elem_t, real_t>
Vec<n, elem_t, real_t>::operator*(const Vec<n, elem_t, real_t> &o) const {
  Vec<n, elem_t, real_t> result;
  for (int i = 0; i < n; i++) {
    result[i] = elems[i] * o[i];
  }
  return result;
}

template <size_t n, typename elem_t, typename real_t>
Vec<n, elem_t, real_t> Vec<n, elem_t, real_t>::operator*(elem_t k) const {
  Vec<n, elem_t, real_t> result;
  for (int i = 0; i < n; i++) {
    result[i] = elems[i] * k;
  }
  return result;
}

template <size_t n, typename elem_t, typename real_t>
Vec<n, elem_t, real_t>
Vec<n, elem_t, real_t>::operator/(const Vec<n, elem_t, real_t> &o) const {
  Vec<n, elem_t, real_t> result;
  for (int i = 0; i < n; i++) {
    result[i] = elems[i] / o[i];
  }
  return result;
}

template <size_t n, typename elem_t, typename real_t>
Vec<n, elem_t, real_t> Vec<n, elem_t, real_t>::operator/(elem_t k) const {
  Vec<n, elem_t, real_t> result;
  for (int i = 0; i < n; i++) {
    result[i] = elems[i] / k;
  }
  return result;
}

template <size_t n, typename elem_t, typename real_t>
elem_t Vec<n, elem_t, real_t>::Dot(const Vec<n, elem_t, real_t> &o) const {
  elem_t result = {}; // enforce zero-initialization
  for (int i = 0; i < n; i++) {
    result += elems[i] * o[i];
  }
  return result;
}

template <size_t n, typename elem_t, typename real_t>
elem_t Vec<n, elem_t, real_t>::SizeSquared() const {
  return this->Dot(*this);
}

template <size_t n, typename elem_t, typename real_t>
Vec<n, elem_t, real_t> Vec<n, elem_t, real_t>::Normalized() const {
  return *this / sqrt(SizeSquared());
}

template <size_t n, typename elem_t, typename real_t>
Vec<n, elem_t, real_t>
Vec<n, elem_t, real_t>::Interp(const Vec<n, elem_t, real_t> &a,
                               const Vec<n, elem_t, real_t> &b, real_t k) {
  return a * (1 - k) + b * k;
}

template <size_t n, typename elem_t, typename real_t>
Vec<n, elem_t, real_t> operator*(elem_t k, const Vec<n, elem_t, real_t> &v) {
  return v * k;
}

struct V2f : Vec<2, float, float> {
  V2f() = default;
  V2f(const V2f &rhs) = default;
  V2f(const Vec<2, float, float> &rhs);
  V2f(float x, float y);
  const float &x() const;
  const float &y() const;
  float &x();
  float &y();
};

struct V3f : Vec<3, float, float> {
  V3f() = default;
  V3f(const V3f &rhs) = default;
  V3f(const Vec<3, float, float> &rhs);
  V3f(float x, float y, float z);
  const float &x() const;
  const float &y() const;
  const float &z() const;
  float &x();
  float &y();
  float &z();
  V3f Cross(const V3f &o) const;
};

#endif // __VECTOR_H__