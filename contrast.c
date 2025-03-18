#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

#include "color.h"

int main(int argc, char *argv[])
{
  bool wcag_check = 0;
  int c;
  while (true) {
    static struct option long_options[] =
          {
            {"wcag-check",     no_argument,       0, 'w'},
            {0, 0, 0, 0}
          };
    
    c = getopt_long (argc, argv, "w", long_options, 0);
    if (c == -1) {
      break;
    }
    switch (c) {
      case 0:
        break;
      case 'w':
      wcag_check = true;
    }
  }
  Color c1, c2;
  int opt = 0;
  if (argc - optind < 2) {
    fprintf(stderr, "no colors provided\n");
    exit(EXIT_FAILURE);
  }
  if (get_color_from_hexstr(&c1, argv[optind]) == EXIT_FAILURE)
      get_color_from_rgbstr(&c1,argv[optind]);
  optind++;
  if (get_color_from_hexstr(&c2, argv[optind]) == EXIT_FAILURE)
      get_color_from_rgbstr(&c2,argv[optind]);

  double l1 = relative_luminance(c1);
  double l2 = relative_luminance(c2);
  if (wcag_check) {
    double ratio = contrast_ratio(l1, l2);
    if (ratio >= 7.) {
      puts("full AAA pass");
    } else if (ratio >= 4.5) {
      puts("large: AAA; normal: AA; graphical: pass");
    } else if (ratio >= 3.) {
      puts("large: AA; graphical: pass");
    } else {
      puts("failed");
    }
  } else {
    printf("%.3f\n", contrast_ratio(l1,l2));
  }

  return EXIT_SUCCESS;
}
