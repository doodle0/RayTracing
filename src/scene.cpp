#include "scene.h"

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
      Ray ray(c.pos + vpPixelPos, vpPixelPos.Normalized(),
              Color(Color(1, 1, 1)));

      bmp[i][j] = gatherLight(ray, 4, 20).ToPixel();
    }
  }

  return bmp;
}

Color Scene::gatherLight(const Ray &ray, int depth, int nChilds) const {
  if (depth <= 0)
    return Color(ray.color * ambience);

  auto [colResult, colObj] = collideNearestObject(ray);
  if (!colResult) {
    // check if the ray collides with a light source
    for (auto *l : lightSources) {
      if (l->Collide(ray)) {
        return Color(ray.color * l->GetColor());
      }
    }
    // if not, return the ambient color
    return Color(ray.color * ambience);
  }

  auto refl = colObj->GetReflector();

  // how many child rays to generate for accumulating light
  int nAccumulations = nChilds;

  // if the collided material has a perfect reflector,
  // make only one child ray
  if (dynamic_cast<const PerfectReflector *>(refl)) {
    nAccumulations = 1;
  }

  Color accumulatedLight;
  for (int i = 0; i < nAccumulations; i++) {
    // generate a child ray using the collision info
    auto chd = refl->MakeChildRay(*colResult);
    accumulatedLight = Color(accumulatedLight + gatherLight(chd, depth - 1, nChilds / 2));
  }
  return Color(accumulatedLight / nAccumulations);
}

CollisionTestResult Scene::collideNearestObject(const Ray &ray) const {
  float minDist = INFINITY;
  CollisionTestResult nearest;
  for (const auto *o : objects) {
    if (auto result = o->Collide(ray)) {
      auto newDist = (result->point - ray.start).SizeSquared();
      if (minDist > newDist) {
        minDist = newDist;
        nearest = make_pair(result, o);
      }
    }
  }
  return nearest;
}
