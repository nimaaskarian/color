simple set of cli utilities to compute color contrast and relative luminance
<color> can be any string in form of #FFF or #FFFFFF or r,g,b

contrast [Flags] <color-1> <color-2>

[Flags]:
  --wcag-check, -w           check if passes the wcag standard and print the status. without it, contrast prints contrast ratio of the colors.



isdark [Flags] <color>

[Flags]:
  --print-luma, -l           print relative luminance of color. without it isdark prints 1 if color is dark and 0 if it isn't.
