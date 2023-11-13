#ifndef __SCENE_H__
#define __SCENE_H__

#include "bitmap.h"
#include "object.h"
#include "tracing.h"
#include "vector.h"

#include <stddef.h>
#include <utility>
#include <vector>

struct Camera {
  V3f pos;
  float theta, phi;
  float viewportDist;
  float viewportWidth, viewportHeight;
};

using CollisionTestResult = std::pair<CollisionResult, const Object*>;

class Scene {
public:
  Scene(const Color &ambience);
  ~Scene();
  void AddObject(Object *obj);
  void AddLightSource(LightSource *lsc);
  Bitmap Render(const Camera &c, size_t dimX, size_t dimY) const;

private:

  Color gatherLight(const Ray &ray, int depth, int nChilds) const;
  CollisionTestResult collideNearestObject(const Ray &ray) const;

  Color ambience;
  std::vector<Object *> objects;
  std::vector<LightSource *> lightSources;
};

#endif // __SCENE_H__