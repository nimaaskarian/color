#ifndef COLOR_H
#define COLOR_H
typedef struct color {
  int r, g, b; 
} Color;

typedef struct srgb {
  double r, g, b;
} sRGB;

#define color_add(c, a,d) \
{ \
  c = a; \
  c.r += d.r; \
  c.g += d.g; \
  c.b += d.b; \
} \

#define color_mul(c, a,m) \
{ \
  c = a; \
  c.r *= m; \
  c.g *= m; \
  c.b *= m; \
} \
Color black();
sRGB color2srgb(Color color);
Color stdcolor2color(sRGB color);
double contrast_ratio(double luma1, double luma2);
void normalize_srgb_for_luma(double *restrict param);
double relative_luminance(Color color);
void three_digit_hex2six(Color *restrict color);
int get_color_from_hex(Color *restrict color, char *restrict str);
int get_color_from_rgb(Color *restrict color, char*charPtr);
int get_color(Color *restrict c, char *restrict str);
void print_color (Color color);
void print_srgb (sRGB srgb);
void printColorRgb(Color color);
double get_luma(Color color);
#endif //COLOR_H
