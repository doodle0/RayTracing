#include "tracing.h"

#include <random>

int rc = 0, pc = 0;

Ray::Ray(const V3f &start, const V3f &direction, const Color &color)
    : start(start), direction(direction), color(color) {}

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

Reflector::Reflector(Color color, float reflectivity)
    : color(color), reflectivity(reflectivity) {}

Ray Reflector::MakeChildRay(const CollisionInfo &collisionInfo) const {
  rc++;
  auto [ray, point, surface] = collisionInfo;
  V3f difDir = lambertian(surface);
  V3f refDir = reflection(ray.direction, surface);

  return Ray(point, V3f::Interp(difDir, refDir, reflectivity).Normalized(),
             Color(ray.color * color));
}

PerfectReflector::PerfectReflector(Color color) : Reflector(color, 1) {}

Ray PerfectReflector::MakeChildRay(const CollisionInfo &collisionInfo) const {
  pc++;
  auto [ray, point, surface] = collisionInfo;
  return Ray(point, reflection(ray.direction, surface),
             Color(ray.color * color));
}
