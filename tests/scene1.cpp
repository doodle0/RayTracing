#include "object.h"
#include "scene.h"
int main() {
    Camera cam{V3f(0, 0, 1), 0, 0, 1, 2, 1.5};
    Scene scene(Color(0.57, 0.88, 1));
    scene.AddObject(new Sphere(V3f(5, 1, 0.5), 0.5, Color(1, 0, 0)));
    scene.AddObject(new Sphere(V3f(5, -2, 1), 1, Color(0, 1, 0)));
    scene.AddObject(new Sphere(V3f(10, -2, 1), 1, Color(0, 0, 1)));
    scene.AddObject(new Ground(Color(0.5, 0.5, 0.5)));
    scene.Render(cam, 1024, 768).ExportPNG("scene1.png");
}