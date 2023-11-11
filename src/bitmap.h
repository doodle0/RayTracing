#ifndef __BITMAP_H__
#define __BITMAP_H__

#include "fpng/fpng.h"
#include <string>
#include <vector>

struct Pixel {
    uint8_t r, g, b;

    Pixel();
    Pixel(int r, int g, int b);
};

class Bitmap {
public:
  typedef std::vector<Pixel> bitmap_row_t;
  typedef std::vector<bitmap_row_t> bitmap_t;

  Bitmap(int w, int h);

  bitmap_row_t &operator[](size_t idx);
  bitmap_t &GetMap();
  void ExportPNG(std::string path) const;

  const unsigned int w, h;
  const unsigned int nChans = 3;

private:
  Pixel *createPixelArray() const;

  bitmap_t map;
};

#endif // __BITMAP_H__