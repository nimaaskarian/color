#include <iostream>
#include <getopt.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "color.h"

int main(int argc, char *argv[])
{
  int c;
  bool null = 0;
  while (!null) {
    static struct option long_options[] =
          {
            {"null",     no_argument,       0, 'l'},
            {0, 0, 0, 0}
          };
    
    c = getopt_long (argc, argv, "0", long_options, 0);
    if (c == -1) {
      break;
    }
    switch (c) {
      case 0:
        break;
      case 'l':
      null = true;
    }
  }
  for (; optind < argc; optind++) {
    cv::Mat img = cv::imread(argv[optind]);
    if (img.empty()) {
        std::cerr << "error: failed to load image\n";
        continue;
    }

    if (img.type() != CV_8UC3) {
        std::cerr << "error: image is not 8-bit 3-channel\n";
        continue;
    }
    int dark = 0;
    img.forEach<cv::Vec3b>([&dark](cv::Vec3b &pixel, const int * position) {
        Color color = {pixel[0], pixel[1], pixel[2]};
        double luminance = relative_luminance(color);
        if (luminance <= .5) {
          dark+=1;
        } else {
          dark-=1;
        }
    });
    if (null) {
      std::cout << (dark > 0) << ' ' << argv[optind] << '\0';
    } else {
      std::cout << (dark > 0) << ' ' << argv[optind] << std::endl;
    }
  }
  return 0;
}
