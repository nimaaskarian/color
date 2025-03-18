#ifndef COLOR_H
#define COLOR_H
typedef struct Color {
  int r, g, b; 
} Color;

typedef struct sRGB {
  double r, g, b;
} StdColor;

#define color_add(c, a,b) \
{ \
  c = a; \
  c.r += b.r; \
  c.g += b.g; \
  c.b += b.b; \
} \

Color black();
StdColor color2stdcolor(Color color);
Color stdcolor2color(StdColor color);
double contrast_ratio(double luma1, double luma2);
void normalize_stdcolor_for_luma(double *param);
double relative_luminance(Color color);
void three_digit_hex2six(Color *color) ;
int get_color_from_hexstr(Color *color, char *str);
int get_color_from_rgbstr(Color *color, char*charPtr);
void print_color (Color color);
void print_stdcolor (StdColor srgb);
void printColorRgb(Color color);
double get_luma(Color color);
#endif
