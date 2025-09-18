#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>
#include "color.h"

int main(int argc, char *argv[])
{
  Color c1 , c2;
  unsigned int count = 8;

  int c;
  bool include_self = 0;
  while (true) {
    static struct option long_options[] =
          {
            {"include-self",   no_argument,             0, 'i'},
            {"count",          required_argument,       0, 'c'},
            {0, 0, 0, 0}
          };
    
    c = getopt_long (argc, argv, "c:i", long_options, 0);
    if (c == -1) {
      break;
    }
    switch (c) {
      case 0:
        break;
      case 'i':
      include_self = true;
      break;
      case 'c':
      count = atoi(optarg);
      break;
    }
  }
  // because we need one more step than specified number!
  count++;
  get_color(&c1, argv[optind++]);
  get_color(&c2, argv[optind++]);
  sRGB c1srgb = color2srgb(c1);
  sRGB c2srgb = color2srgb(c2);

  sRGB difference;
  difference.r = (c2srgb.r - c1srgb.r)/count;
  difference.g = (c2srgb.g - c1srgb.g)/count;
  difference.b = (c2srgb.b - c1srgb.b)/count;

  for (unsigned int i = 1-include_self; i < count+include_self; ++i) {
    sRGB color;
    color_mul(color, difference, i);
    color_add(color, color, c1srgb);
    print_srgb(color);
  }
  return EXIT_SUCCESS;
}
