#include "scene.h"
#include "src/color.h"
#include <algorithm>
#include <cmath>
#include <optional>

Scene::Scene(const Color &sky) : ambience(sky) {}

Scene::~Scene() {
  for (auto *o : objects) {
    delete o;
  }
  for (auto *l : lightSources) {
    delete l;
  }
}

void Scene::AddObject(Object *obj) { objects.push_back(obj); }

void Scene::AddLightSource(LightSource *lsc) { lightSources.push_back(lsc); }

Bitmap Scene::Render(const Camera &c, size_t dimX, size_t dimY) const {
  Bitmap bmp(dimX, dimY);

  V3f viewDir(cos(c.phi) * cos(c.theta), cos(c.phi) * sin(c.theta), sin(c.phi));
  V3f jBasis = viewDir.Cross(V3f(0, 0, 1)).Normalized() * c.viewportWidth;
  V3f iBasis = viewDir.Cross(jBasis).Normalized() * c.viewportHeight;

  for (int i = 0; i < dimY; i++) {
    for (int j = 0; j < dimX; j++) {
      // compute the direction of rays of each pixel in viewport
      V3f vpPixelPos = viewDir + (j - (dimX - 1) / 2.0f) / dimX * jBasis +
                       (i - (dimY - 1) / 2.0f) / dimY * iBasis;
      Ray ray(c.pos + vpPixelPos, vpPixelPos.Normalized(), Color(Color(1, 1, 1)));

      bmp[i][j] = gatherLight(ray).ToPixel();
    }
  }

  return bmp;
}

Color Scene::gatherLight(const Ray &initRay) const {
  Color accumulatedLight;
  int nAccumulations = 10;
  for (int i = 0; i < nAccumulations; i++) {
    Ray ray = initRay;
    for (int j = 0; j < 5; j++) {
      if (auto res = collideNearestObject(ray)) {
        ray = *res;
      }
    }
    for (auto *l : lightSources) {
      if (!l->Collide(ray)) {
        ray.color = Color(ray.color * ambience);
      }
    }
    accumulatedLight = Color(accumulatedLight + ray.color);
  }
  return Color(accumulatedLight / nAccumulations);
}

std::optional<Ray> Scene::collideNearestObject(const Ray &ray) const {
  float minDist = INFINITY;
  std::optional<Ray> nearestReflection;
  for (auto *o : objects) {
    if (auto result = o->Collide(ray)) {
      auto newDist = (result->start - ray.start).SizeSquared();
      if (minDist > newDist) {
        minDist = newDist;
        nearestReflection = result;
      }
    }
  }
  return nearestReflection;
}
