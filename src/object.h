#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "color.h"
#include "vector.h"

struct Ray {
  Ray(const V3f &start, const V3f &direction, const Color &color);
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
  Object(const Color &color, float reflectivity);
  virtual ~Object() = default;
  virtual std::optional<Ray> Collide(const Ray &ray) const = 0;

protected:
  Ray makeChildRay(const Ray &ray, const V3f &collisionPointAbs,
                   const V3f &surface) const;
  Color color;
  float reflectivity;
};

class Sphere : public Object {
public:
  Sphere(V3f centerPos, float radius, Color color, float reflectivity);
  std::optional<Ray> Collide(const Ray &ray) const override;

private:
  V3f centerPos;
  float radius;
};

class Ground : public Object {
public:
  Ground(const Color &color, float reflectivity);
  std::optional<Ray> Collide(const Ray &ray) const override;
};

#endif // __OBJECT_H__