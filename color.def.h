typedef struct color {
  unsigned char r, g, b; 
} Color;

typedef struct srgb {
  double r, g, b;
} sRGB;

#define relative_luminance_rgb(r, g, b) (0.2126*(r)) + (0.7152*(g)) + (0.0722 * (b))

#define NORMALIZE_THRESHOLD 0.04045
#define NORMALIZE_LOWER_DIVIDE 12.92
#define NORMALIZE_UPPER_ADD 0.055
#define NORMALIZE_UPPER_DIVIDE 1.055
#define NORMALIZE_UPPER_POW 2.4
#define normalize_srgb_for_luma(param) \
{ \
  if (param <= NORMALIZE_THRESHOLD) \
    param = param/NORMALIZE_LOWER_DIVIDE; \
  else \
    param = pow(((param+NORMALIZE_UPPER_ADD)/NORMALIZE_UPPER_DIVIDE), NORMALIZE_UPPER_POW); \
 \
}

#define color_add(c, a,d) \
{ \
  c = a; \
  c.r += d.r; \
  c.g += d.g; \
  c.b += d.b; \
}

#define color_mul(c, a,m) \
{ \
  c = a; \
  c.r *= m; \
  c.g *= m; \
  c.b *= m; \
}
