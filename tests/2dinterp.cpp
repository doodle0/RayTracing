#include "bitmap.h"
#include "color.h"
#include "vector.h"
#include "fpng/fpng.h"
#include <stdio.h>

int main() {
  Bitmap bitmap(1024, 768);
  
  for (int i = 0; i < bitmap.h; i++) {
    for (int j = 0; j < bitmap.w; j++) {
      bitmap[i][j] =
          Color(Color::Interp(
                    Color::Interp(Color(), Color(1, 1, 0), float(i) / bitmap.h),
                    Color::Interp(Color(0, 1, 1), Color(1, 0, 1), float(i) / bitmap.h),
                    float(j) / bitmap.w))
              .ToPixel();
    }
  }

  bitmap.ExportPNG("2dinterp.png");
}
