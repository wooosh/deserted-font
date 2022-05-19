#include <ios>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// arguments: png glyphwidth spacing charorder
int main(int argc, char **argv) {
  if (argc != 5) {
    std::cerr << "incorrect # of arguments\n";
    std::abort();
  }

  const char *filename = argv[1];
  int charwidth = std::stoi(argv[2]);
  int spacing = std::stoi(argv[3]);
  std::string chars = argv[4];


  int img_w, img_h, num_channels;
  uint32_t *img = (uint32_t *) stbi_load(filename, &img_w, &img_h, &num_channels, 4);
  if (img == NULL) {
    std::cerr << "cannot read image\n";
    std::abort();
  }

  for (size_t i=0; i<chars.size(); i++) {
    std::cout << std::hex << "STARTCHAR U+00" << (int)chars[i] << std::dec << "\n"
              << "ENCODING " << (int) chars[i] << "\n"
              << "SWIDTH 600 0\n" // TODO: pixels = (scalable_width / 1000) * (resolution / 72)
              << "DWIDTH " << charwidth << " 0\n"
              << "BBX " << charwidth+1 << " " << img_h << " 0 -2\n"
              << "BITMAP\n";

    std::cout << std::uppercase <<std::hex;
    for (size_t y = 0; y < img_h; y++) {
      int buffer = 0;
      for (size_t x = 0; x < charwidth; x++) {
        uint32_t pixel = img[y*img_w + i*(charwidth+spacing) + x];
        bool bit = pixel == 0xFF000000;
        buffer |= bit;
        buffer <<= 1;
        if ((x+1) % 8 == 0) {
          std::cout << buffer;
          buffer = 0;
        }
      }
      if (charwidth % 8 != 0) {
        std::cout << buffer;
      }
      std::cout << "\n";
    }
    std::cout << std::dec;
    std::cout << "ENDCHAR\n";
  }
}
