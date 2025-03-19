#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

#include "color.h"

int main(int argc, char *argv[])
{
  bool wcag_check = false, compare = false;
  int c;
  Color c1, c2, c3;
  while (true) {
    static struct option long_options[] =
          {
            {"wcag-check",     no_argument,          0, 'w'},
            {"compare",        required_argument,    0, 'c'},
            {0, 0, 0, 0}
          };
    
    c = getopt_long (argc, argv, "wc:", long_options, 0);
    if (c == -1) {
      break;
    }
    switch (c) {
      case 0:
        break;
      case 'w':
        wcag_check = true;
        break;
      case 'c':
        compare = true;
        get_color(&c3, optarg);
        break;
    }
  }
  if (argc - optind < 2) {
    fprintf(stderr, "no colors provided\n");
    exit(EXIT_FAILURE);
  }
  get_color(&c1, argv[optind++]);
  get_color(&c2, argv[optind++]);

  if (compare) {
    double ratio1 = contrast_ratio(c1, c3);
    double ratio2 = contrast_ratio(c2, c3);
    if (ratio1 >= ratio2) {
      print_color(c1);
    } else {
      print_color(c2);
    }
  } else {
    double ratio = contrast_ratio(c1, c2);
    if (wcag_check) {
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
      printf("%.3f\n", ratio);
    }
  }

  return EXIT_SUCCESS;
}
