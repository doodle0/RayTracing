#include "object.h"
#include "src/color.h"
#include <cstdio>
#include <optional>
#include <random>

static V3f randomUnitVector() {
  // Create a random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(0.0, 1.0);
  std::uniform_real_distribution<double> angleDis(0.0, 2.0 * M_PI);
  std::uniform_real_distribution<double> cosThetaDis(-1.0, 1.0);

  // Generate random values for spherical coordinates
  double phi = angleDis(gen);
  double cosTheta = cosThetaDis(gen);
  double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

  // Convert spherical coordinates to Cartesian coordinates
  return V3f(sinTheta * std::cos(phi), sinTheta * std::sin(phi), cosTheta);
}

static V3f reflection(const V3f &ray, const V3f &surface) {
  return (ray - 2 * ray.Dot(surface) * surface).Normalized();
}

static V3f lambertian(const V3f &surface) {
  return (surface + randomUnitVector()).Normalized();
}

Ray Object::makeChildRay(const Ray &ray, const V3f &collisionPointAbs,
                         const V3f &surface) const {
  V3f difDir = lambertian(surface);
  V3f refDir = reflection(ray.direction, surface);

  return Ray(collisionPointAbs,
             V3f::Interp(difDir, refDir, reflectivity).Normalized(),
             Color(ray.color * color));
}

Ray::Ray(const V3f &start, const V3f &direction, const Color &color)
    : start(start), direction(direction), color(color) {
  // if (direction.SizeSquared() > 1.001 || direction.SizeSquared() < 0.999)
  //   printf("%f\n", direction.SizeSquared());
}

Object::Object(const Color &color, float reflectivity)
    : color(color), reflectivity(reflectivity) {}

Sphere::Sphere(V3f centerPos, float radius, Color color, float reflectivity)
    : Object(color, reflectivity), centerPos(centerPos), radius(radius) {}

std::optional<Ray> Sphere::Collide(const Ray &ray) const {
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

  return makeChildRay(ray, collisionPointAbs,
                      (collisionPointAbs - centerPos).Normalized());
}

Ground::Ground(const Color &color, float reflectivity)
    : Object(color, reflectivity) {}

std::optional<Ray> Ground::Collide(const Ray &ray) const {
  if (ray.direction.z() < 0) {
    // extend ray.direction so it touches the ground
    V3f rayDirExt = (-ray.direction * ray.start.z() / ray.direction.z());

    // then remove z element from the result
    V3f collisionPointAbs = (ray.start + rayDirExt) * V3f(1, 1, 0);

    return makeChildRay(ray, collisionPointAbs, V3f(0, 0, 1));
  }
  return {};
}

LightSource::LightSource(V3f centerPos, float radius, Color color)
    : Sphere(centerPos, radius, color, 0) {}
