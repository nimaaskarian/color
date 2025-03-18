#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "color.h"

Color black()
{
  Color output;
  output.r = 0;
  output.g = 0;
  output.b = 0;
  return output;
}

sRGB color2srgb(Color color)
{
  sRGB output;
  output.r = (double)color.r/255;
  output.g = (double)color.g/255;
  output.b = (double)color.b/255;
  return output;
}

Color stdcolor2color(sRGB color)
{
  Color output;
  output.r = (int)(color.r*255);
  output.g = (int)(color.g*255);
  output.b = (int)(color.b*255);
  return output;
}

double contrast_ratio(double luma1, double luma2)
{
  if (luma1>luma2)
     return ( luma1 +0.05 )/( luma2 +0.05);
  else
     return ( luma2 +0.05 )/( luma1 +0.05);
}

void normalize_srgb_for_luma(double *restrict param)
{
  if (*param <= 0.04045)
    *param = *param/12.92;
  else
    *param = pow(((*param+0.055)/1.055), 2.4);

}
double relative_luminance(Color color)
{

  sRGB srgb = color2srgb(color);

  normalize_srgb_for_luma(&srgb.r);
  normalize_srgb_for_luma(&srgb.g);
  normalize_srgb_for_luma(&srgb.b);

  return 0.2126*srgb.r + 0.7152*srgb.g + 0.0722 * srgb.b;
}

void three_digit_hex2six(Color *restrict color) 
{
  // if its a three digit hex color like #ABC, we want to have
  // #AABBCC so we do this:

  color->r += color->r*16;
  color->g += color->g*16;
  color->b += color->b*16;
}

int get_color_from_hex(Color *restrict color, char *restrict str)
{
  int colorsFound = sscanf(str, "#%02x%02x%02x", &color->r,&color->g,&color->b);
  if(colorsFound != 3) {
    if (colorsFound == 2 && sscanf(str,"#%01x%01x%01x",&color->r,&color->g, &color->b) == 3) {
      three_digit_hex2six(color);
    } else
      return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int get_color_from_rgb(Color *restrict color, char*charPtr)
{
  if (sscanf(charPtr, "%d,%d,%d", &color->r, &color->g, &color->b) != 3) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int get_color(Color *restrict c, char *restrict str)
{
  if (get_color_from_hex(c, str) == EXIT_FAILURE)
    return get_color_from_rgb(c, str);
  return EXIT_SUCCESS;
}

void print_color (Color color)
{
  printf("#%02x%02x%02x\n", color.r,color.g,color.b);
}

void print_srgb (sRGB srgb)
{
  print_color(stdcolor2color(srgb));
}

void printColorRgb(Color color)
{
  printf("%d,%d,%d\n", color.r,color.g,color.b);
}

double get_luminance(Color color)
{
  return sqrt(0.299*color.r*color.r+0.587*color.g*color.g+0.114*color.b*color.b);
}
