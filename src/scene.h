#ifndef __SCENE_H__
#define __SCENE_H__

#include "bitmap.h"
#include "object.h"
#include "vector.h"

#include <stddef.h>
#include <vector>

struct Camera {
  V3f pos;
  float theta, phi;
  float viewportDist;
  float viewportWidth, viewportHeight;
};

class Scene {
public:
  Scene(const Color &sky);
  ~Scene();
  void AddObject(Object *obj);
  void AddLightSource(LightSource *lsc);
  Bitmap Render(const Camera &c, size_t dimX, size_t dimY) const;

private:
  Color sky;
  std::vector<Object *> objects;
  std::vector<LightSource *> lightSources;
};

#endif // __SCENE_H__