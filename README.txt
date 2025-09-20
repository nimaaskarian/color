simple set of cli utilities to compute color contrast and relative luminance
<c> (<cn>) can be any string in form of #FFF or #FFFFFF or r,g,b

contrast:  prints contrast ratio of two colors
[Usage]
  contrast [Flags] <c1> <c2>

[Flags]
  --wcag-check, -w                  check if passes the WCAG 2.x standard and prints the status
  --compare <c3>, -c <c3>           check which of <c1> or <c2> has a higher contrast ratio with <c3>, prints it (ignores other options)


isdark: prints 1 if the color is dark, 0 if its not
[Usage]
  isdark [Flags] <c1> <c2> ... <cn>

[Flags]
  --luminance, -l                   print relative luminance of color instead


gradient: makes a gradient of colors between two colors
[Usage]
  gradient [Flags] <c1> <c2>

[Flags]
  --include-self, -i                include the colors provided in the beginning and the end of the output
  --count, -c (default=8)           count of colors between (without the colors themselves).


as-rgb: prints color as rgb
[Usage]
  as-rgb <c>

isimgdark: prints 1 if the image is dark, 0 if its not
[Usage]
isimgdark [Flags] <img1> <img2> ... <imgn>

[Flags]
  --null, -0                        print null delimited lines, instead of newlines. corresponds to grep -z, cut -z, xargs -0
  --luminance, -l                   print relative luminance of image instead
