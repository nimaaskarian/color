#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include "color.h"

int main(int argc, char *argv[])
{
  Color color;
  int opt = 0;

  int c;
  bool print_luma = 0, printIsDark = 1;
  while (true) {
    static struct option long_options[] =
          {
            {"print-luma",     no_argument,       0, 'l'},
            {0, 0, 0, 0}
          };
    
    c = getopt_long (argc, argv, "w", long_options, 0);
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
  double luma = get_luma(color);
  // MIN_luma: 0
  // MAX_luma: 255
  // a color is dark when luma <= %50 * MAX_luma 
  if (print_luma) {
    int is_dark = luma <= 127.5;
    printf("%d\n", is_dark);
  } else {
    printf("luma: %f\n", luma);
  }

  return EXIT_SUCCESS;
}

