#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "color.h"
#include "vector.h"

struct Ray {
  V3f start;
  V3f direction;
  Color color;
};

struct LightSource {
  V3f position;
  float radius;
};

class Object {
public:
  Object(const Color &color);
  virtual ~Object() = default;
  virtual Ray Collide(const Ray &ray) const = 0;

protected:
  Color color;
};

class Sphere : public Object {
public:
  Sphere(V3f centerPos, float radius, Color color);
  Ray Collide(const Ray &ray) const override;

private:
  V3f centerPos;
  float radius;
};

class Ground : public Object {
public:
  Ground(const Color &color);
  Ray Collide(const Ray &ray) const override;
};

#endif // __OBJECT_H__