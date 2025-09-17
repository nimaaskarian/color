#ifndef COLOR_H
#define COLOR_H
#ifdef __cplusplus
extern "C" {
#endif
typedef struct color {
  unsigned char r, g, b; 
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
Color srgb2color(sRGB color);
double contrast_ratio(Color c1, Color c2);
void normalize_srgb_for_luma(double *param);
double relative_luminance(Color color);
void three_digit_hex2six(Color *color);
int get_color_from_hex(Color *color, char *str);
int get_color_from_rgb(Color *color, char*charPtr);
int get_color(Color *c, char *str);
void print_color(Color color);
void print_srgb(sRGB srgb);
#ifdef __cplusplus
}
#endif
#endif //COLOR_H
