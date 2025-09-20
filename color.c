#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "color.h"

Color black()
{
  Color black = {0, 0, 0};
  return black;
}

sRGB color2srgb(Color color)
{
  sRGB output;
  output.r = (double)color.r/255;
  output.g = (double)color.g/255;
  output.b = (double)color.b/255;
  return output;
}

Color srgb2color(sRGB color)
{
  Color output;
  output.r = (int)(color.r*255);
  output.g = (int)(color.g*255);
  output.b = (int)(color.b*255);
  return output;
}

double contrast_ratio(Color c1, Color c2)
{
  double l1 = relative_luminance(c1);
  double l2 = relative_luminance(c2);
  if (l1>l2) return ( l1 +0.05 )/( l2 +0.05);
   return ( l2 +0.05 )/( l1 +0.05);
}

double relative_luminance(Color color)
{

  sRGB srgb = color2srgb(color);

  normalize_srgb_for_luma(srgb.r);
  normalize_srgb_for_luma(srgb.g);
  normalize_srgb_for_luma(srgb.b);

  return relative_luminance_rgb(srgb.r, srgb.g, srgb.b);
}

void three_digit_hex2six(Color *color) 
{
  // if its a three digit hex color like #ABC, we want to have
  // #AABBCC so we do this:

  color->r += color->r*16;
  color->g += color->g*16;
  color->b += color->b*16;
}

static inline int read_uint_rgb_to_color(unsigned int r,unsigned int g,unsigned int b, Color *color)
{
  if (r > UINT8_MAX || g > UINT8_MAX || b > UINT8_MAX) {
    return EXIT_FAILURE;
  }
  color->r = (unsigned char)r;
  color->g = (unsigned char)g;
  color->b = (unsigned char)b;
  return EXIT_SUCCESS;
}

int get_color_from_hex(Color *color, char *str)
{
  unsigned int r,g,b;
  bool is_three_digit = false;
  int colorsFound = sscanf(str, "#%02x%02x%02x", &r,&g,&b);
  if(colorsFound != 3) {
    if (colorsFound == 2 && sscanf(str,"#%01x%01x%01x",&r,&g, &b) == 3) {
      is_three_digit = true;
    } else
      return EXIT_FAILURE;
  }
  if (read_uint_rgb_to_color(r, g, b, color)) {
    return EXIT_FAILURE;
  }
  if (is_three_digit) {
      three_digit_hex2six(color);
  }
  return EXIT_SUCCESS;
}

int get_color_from_rgb(Color *color, char*charPtr)
{
  unsigned int r,g,b;
  if (sscanf(charPtr, "%u,%u,%u", &r, &g, &b) != 3) {
    return EXIT_FAILURE;
  }
  if (read_uint_rgb_to_color(r, g, b, color)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int get_color(Color *c, char *str)
{
  if (get_color_from_hex(c, str) == EXIT_FAILURE)
    return get_color_from_rgb(c, str);
  return EXIT_SUCCESS;
}

void print_color(Color color)
{
  printf("#%02x%02x%02x\n", color.r,color.g,color.b);
}

void print_srgb(sRGB srgb)
{
  print_color(srgb2color(srgb));
}
