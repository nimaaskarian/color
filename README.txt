simple set of cli utilities to compute color contrast and relative luminance
<color> can be any string in form of #FFF or #FFFFFF or r,g,b

contrast:  prints contrast ratio of two colors
[Usage]
  contrast [Flags] <color-1> <color-2>

[Flags]
  --wcag-check, -w           check if passes the wcag standard and prints the status


isdark: prints whether the color is 
[Usage]
  isdark [Flags] <color>

[Flags]
  --print-luma, -l           print relative luminance of color instead


cbetween: prints colors between two colors
[Usage]
  cbetween [Flags] <color-1> <color-2>

[Flags]
  --include-self, -i         include the colors provided in the beginning and the end of the output
  --count, -c (default=8)    count of colors between (without the colors themselves).
