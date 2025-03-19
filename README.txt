simple set of cli utilities to compute color contrast and relative luminance
<c> (<c-n>) can be any string in form of #FFF or #FFFFFF or r,g,b

contrast:  prints contrast ratio of two colors
[Usage]
  contrast [Flags] <c-1> <c-2>

[Flags]
  --wcag-check, -w                       check if passes the wcag standard and prints the status
  --compare <c-3>, -c <c-3>              check which of <c-1> or <c-2> has a higher contrast ratio with <c-3>, prints it (ignores other options)


isdark: prints 1 if the color is dark, 0 if its not
[Usage]
  isdark [Flags] <c>

[Flags]
  --print-luminance, -l             print relative luminance of color instead


cbetween: prints colors between two colors
[Usage]
  cbetween [Flags] <c-1> <c-2>

[Flags]
  --include-self, -i                include the colors provided in the beginning and the end of the output
  --count, -c (default=8)           count of colors between (without the colors themselves).
