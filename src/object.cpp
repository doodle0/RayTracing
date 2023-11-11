#include "object.h"
#include <random>

static V3f randomDiffusion(const V3f &surface) {
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
  V3f result(sinTheta * std::cos(phi), sinTheta * std::sin(phi), cosTheta);

  // Return the result or the inversion of it depending on its direction
  // relative to the surface vector
  if (result.Dot(surface) < 0)
    return -result;
  return result;
}

Object::Object(const Color &color) : color(color) {}

Sphere::Sphere(V3f centerPos, float radius, Color color)
    : Object(color), centerPos(centerPos), radius(radius) {}

Ray Sphere::Collide(const Ray &ray) const {
  // my center, relative to ray.start
  V3f centerRel = centerPos - ray.start;
  // the foot of perpendicular from my center and the ray, relative to ray.start
  V3f footRel = centerRel.Dot(ray.direction) * ray.direction;
  // shortest vector to my center from the ray
  V3f distVec = centerRel - footRel;
  // half the distance between intersections, squared
  float hd2 = radius * radius - distVec.SizeSquared();

  // return itself if no collision
  if (hd2 < 0)
    return ray;

  // the collision point, absolute
  V3f collisionPoint = ray.start + footRel - sqrt(hd2) * ray.direction;

  // else diffuse the ray and return
  return Ray{collisionPoint, randomDiffusion(collisionPoint - centerPos),
             color};
}

Ground::Ground(const Color &color) : Object(color) {}

Ray Ground::Collide(const Ray &ray) const {
  if (ray.direction.z() < 0) {
    V3f collisionPoint = V3f(); // temporary
    return Ray{collisionPoint, randomDiffusion(V3f(0, 0, 1)), color};
  }
  return ray;
}
