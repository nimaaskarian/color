#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include "color.h"

int main(int argc, char *argv[])
{
  Color color;

  int c;
  bool print_luma = 0;
  while (true) {
    static struct option long_options[] =
          {
            {"print-luma",     no_argument,       0, 'l'},
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
      print_luma = true;
    }
  }
  get_color(&color, argv[optind++]);
  double luminance = get_luminance(color);
  // min: 0
  // max: 255
  // a color is dark when luminance <= 127.5 (0.5*max) 
  if (print_luma) {
    printf("%.3f\n", luminance);
  } else {
    int is_dark = luminance <= 127.5;
    printf("%d\n", is_dark);
  }

  return EXIT_SUCCESS;
}

