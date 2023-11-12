#include "object.h"
#include "scene.h"
int main() {
    Camera cam{V3f(0, 0, 1), 0, 0, 1, 2, 1.5};
    Scene scene(Color(0.79, 0.94, 1));
    scene.AddObject(new Sphere(V3f(2.5, 0, 0.6), 0.6, Color(1, 1, 0.5), 0.99));
    scene.AddObject(new Sphere(V3f(4, 1, 0.4), 0.4, Color(0.9, 0.9, 0.9), 0.5));
    scene.AddObject(new Sphere(V3f(5, -2.5, 1.5), 1.5, Color(0.5, 0.8, 1), 0.99));
    scene.AddObject(new Sphere(V3f(10, -2, 1), 1, Color(1, 0.5, 0.5), 0.5));
    scene.AddObject(new Ground(Color(0.5, 0.5, 0.5), 0.5));
    scene.Render(cam, 1024, 768).ExportPNG("scene1.png");
}