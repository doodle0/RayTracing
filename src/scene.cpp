#include "scene.h"

Scene::Scene(const Color &sky) : sky(sky) {}

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
      // cast rays for each pixel
      V3f vpPixelPos = viewDir + (j - (dimX - 1) / 2.0f) / dimX * jBasis +
                       (i - (dimY - 1) / 2.0f) / dimY * iBasis;
      Ray ray{c.pos + vpPixelPos, vpPixelPos.Normalized(), sky};

      // for now, just hit objects in arbitrary order
      for (auto *o : objects) {
        ray = o->Collide(ray);
      }
      bmp[i][j] = Color(ray.color).ToPixel();
    }
  }

  return bmp;
}
