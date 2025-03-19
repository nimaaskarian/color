#include <stdlib.h>
#include <stdio.h>
#include "color.h"

void print_color_rgb(Color color)
{
  printf("%d,%d,%d\n", color.r,color.g,color.b);
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    return EXIT_FAILURE;
  }
  Color c;
  get_color(&c, argv[1]);
  print_color_rgb(c);
  return EXIT_SUCCESS;
}
