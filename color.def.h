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
}

#define color_mul(c, a,m) \
{ \
  c = a; \
  c.r *= m; \
  c.g *= m; \
  c.b *= m; \
}
#ifdef __cplusplus
}
#endif
