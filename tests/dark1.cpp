#include "color.h"
#include "object.h"
#include "scene.h"

extern int rc, pc;

int main() {
    Camera cam{V3f(0, 0, 1), 0, 0, 1, 2, 1.5};
    Scene scene(Color(0, 0, 0));

    scene.AddObject(new Sphere(V3f(2, 0, 0.6), 0.6, Color(1, 1, 0.5), 1));
    scene.AddObject(new Sphere(V3f(4, 2, 0.4), 0.4, Color(0.9, 0.9, 0.9), 0.5));
    scene.AddObject(new Sphere(V3f(5, -2.5, 1.5), 1.5, Color(0.5, 0.8, 1), 1));
    scene.AddObject(new Sphere(V3f(1.5, -1, 0.3), 0.3, Color(1, 0.5, 0.5), 0.5));
    scene.AddObject(new Ground(Color(1, 1, 1), 0));

    scene.AddLightSource(new LightSource(V3f(-5, 5, 20), 10, Color(1, 1, 1)));

    scene.Render(cam, 400, 300).ExportPNG("dark1.png");

    printf("%d %d\n", rc, pc);
}