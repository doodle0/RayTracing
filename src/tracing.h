#ifndef __TRACING_H__
#define __TRACING_H__

#include "color.h"
#include "vector.h"
#include <optional>

struct Ray {
  Ray(const V3f &start, const V3f &direction, const Color &color);
  V3f start;
  V3f direction;
  Color color;
};

struct CollisionInfo {
  Ray ray;
  V3f point;
  V3f surfaceNormal;
};

using CollisionResult = std::optional<CollisionInfo>;

class Reflector {
public:
  Reflector(Color color, float reflectivity);
  virtual ~Reflector() = default;
  virtual Ray MakeChildRay(const CollisionInfo &collisionInfo) const;

protected:
  Color color;
  float reflectivity;
};

class PerfectReflector : public Reflector {
public:
  PerfectReflector(Color color);
  Ray MakeChildRay(const CollisionInfo &collisionInfo) const override;
};

#endif // __TRACING_H__