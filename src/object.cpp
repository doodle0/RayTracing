#include "object.h"
#include <cstdio>
#include <optional>

Object::Object(const Color &color, float reflectivity) {
  if (reflectivity >= 1) {
    reflector = new PerfectReflector(color);
  } else {
    reflector = new Reflector(color, reflectivity);
  }
}

Object::~Object() { delete reflector; }

const Reflector *Object::GetReflector() const { return reflector; }

Sphere::Sphere(V3f centerPos, float radius, Color color, float reflectivity)
    : Object(color, reflectivity), centerPos(centerPos), radius(radius) {}

CollisionResult Sphere::Collide(const Ray &ray) const {
  // my center, relative to ray.start
  V3f centerRel = centerPos - ray.start;
  // the foot of perpendicular from my center and the ray, relative to ray.start
  V3f footRel = centerRel.Dot(ray.direction) * ray.direction;
  // shortest vector to my center from the ray
  V3f distVec = centerRel - footRel;
  // half the distance between intersections, squared
  float hd2 = radius * radius - distVec.SizeSquared();

  // return null if no collision
  if (hd2 < 0)
    return {};

  // the point of collision, relative
  V3f collisionPointRel = footRel - sqrt(hd2) * ray.direction;

  // if the collision point is in the negative direction,
  // it is also not a collision
  if (collisionPointRel.Dot(ray.direction) < 0)
    return {};

  // the point of collision, absolute
  V3f collisionPointAbs = ray.start + collisionPointRel;

  return CollisionInfo{ray, collisionPointAbs,
                       (collisionPointAbs - centerPos).Normalized()};
}

Ground::Ground(const Color &color, float reflectivity)
    : Object(color, reflectivity) {}

CollisionResult Ground::Collide(const Ray &ray) const {
  if (ray.direction.z() >= 0)
    return {};

  // extend ray.direction so it touches the ground
  V3f rayDirExt = (-ray.direction * ray.start.z() / ray.direction.z());

  // then remove z element from the result
  V3f collisionPointAbs = (ray.start + rayDirExt) * V3f(1, 1, 0);

  return CollisionInfo{ray, collisionPointAbs, V3f(0, 0, 1)};
}

LightSource::LightSource(V3f centerPos, float radius, Color color)
    : Sphere(centerPos, radius, color, 0), color(color) {}

const Color &LightSource::GetColor() const { return color; }
