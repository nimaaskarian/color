#include <iostream>
#include <vector>
#include <execution>
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
  // std::for_each
   std::vector<char*> items(argv + optind, argv + argc);
   std::for_each(std::execution::par, items.begin(), items.end(), [null](char* s) {
          cv::Mat img = cv::imread(s);
          if (img.empty()) {
              std::cerr << "error: failed to load image\n";
              return;
          }
          cv::Mat img_srgb;
          img.convertTo(img_srgb, CV_32F, 1.0/255);
          std::vector<cv::Mat> bgr;
          cv::split(img_srgb, bgr);
          cv::Mat luminance_matrix = relative_luminance_rgb(bgr[2], bgr[1], bgr[0]);
          double luminance = cv::mean(luminance_matrix)[0];
          bool isdark = luminance < 0.5;
          if (null) {
            std::cout << isdark << ' ' << s << '\0';
          } else {
            std::cout << isdark << ' ' << s << std::endl;
          }
        }
    );
  return 0;
}
