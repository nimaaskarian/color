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
  double luma = get_luma(color);
  // MIN_luma: 0
  // MAX_luma: 255
  // a color is dark when luma <= %50 * MAX_luma 
  if (print_luma) {
    printf("luma: %f\n", luma);
  } else {
    int is_dark = luma <= 127.5;
    printf("%d\n", is_dark);
  }

  return EXIT_SUCCESS;
}

