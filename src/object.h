#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "color.h"
#include "tracing.h"
#include "vector.h"

class Object;

class Object {
public:
  Object(const Color &color, float reflectivity);
  virtual ~Object();
  const Reflector *GetReflector() const;
  virtual CollisionResult Collide(const Ray &ray) const = 0;

protected:
  Reflector *reflector;
};

class Sphere : public Object {
public:
  Sphere(V3f centerPos, float radius, Color color, float reflectivity);
  CollisionResult Collide(const Ray &ray) const override;

protected:
  V3f centerPos;
  float radius;
};

class Ground : public Object {
public:
  Ground(const Color &color, float reflectivity);
  CollisionResult Collide(const Ray &ray) const override;
};

struct LightSource : public Sphere {
public:
  LightSource(V3f centerPos, float radius, Color color);
  const Color &GetColor() const;

protected:
  Color color;
};

#endif // __OBJECT_H__