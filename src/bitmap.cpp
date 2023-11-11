#include "bitmap.h"

//
// struct Pixel
//

Pixel::Pixel() : r(0), g(0), b(0) {}
Pixel::Pixel(int r, int g, int b) : r(r), g(g), b(b) {}

//
// class Bitmap
//

Bitmap::Bitmap(int w, int h) : w(w), h(h) {
  map.resize(h);
  for (auto &r : map) {
    r.resize(w);
  }
}

Bitmap::bitmap_t &Bitmap::GetMap() { return map; }

Bitmap::bitmap_row_t &Bitmap::operator[](size_t idx) {
  return map[idx];
}

void Bitmap::ExportPNG(std::string path) const {
  Pixel *pImage = createPixelArray();
  fpng::fpng_encode_image_to_file(path.c_str(), pImage, w, h, nChans);
  delete[] pImage;
}

Pixel *Bitmap::createPixelArray() const {
  auto *array = new Pixel[w * h];
  auto *p = array;
  for (auto &r : map) {
    std::copy(r.begin(), r.end(), p);
    p += w;
  }
  return array;
}