#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include "color.h"

int main(int argc, char *argv[])
{
  Color color;

  int c;
  bool print_luminance = 0;
  while (true) {
    static struct option long_options[] =
          {
            {"print-luminance",     no_argument,       0, 'l'},
            {0, 0, 0, 0}
          };
    
    c = getopt_long (argc, argv, "l", long_options, 0);
    if (c == -1) {
      break;
    }
    switch (c) {
      case 0:
        break;
      case 'l':
      print_luminance = true;
    }
  }
  get_color(&color, argv[optind++]);
  double luminance = relative_luminance(color);
  if (print_luminance) {
    printf("%.3f\n", luminance);
  } else {
    int is_dark = luminance <= .5;
    printf("%d\n", is_dark);
  }

  return EXIT_SUCCESS;
}

