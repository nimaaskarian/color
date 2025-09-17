#include <cstdint>
#include <iostream>
#include <vector>
#include <getopt.h>
#include <opencv4/opencv2/core/version.hpp>
#include <opencv4/opencv2/core/cvdef.h>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include "color.h"

int main(int argc, char *argv[])
{
  int c;
  bool null = 0;
  while (true) {
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
    std::vector<cv::Mat> three_channels;
    cv::split(img, three_channels);
    int dark = 0;
    for(int i=0; i<img.rows; i++) {
      for(int j=0; j<img.cols; j++)
      {
          Color color = {three_channels[0].at<uint8_t>(i, j), three_channels[1].at<uint8_t>(i, j), three_channels[2].at<uint8_t>(i, j)};
          double luminance = relative_luminance(color);
          if (luminance <= .5) {
            dark+=1;
          } else {
            dark-=1;
          }
      }
    }
    if (null) {
      std::cout << (dark > 0) << ' ' << argv[optind] << '\0';
    } else {
      std::cout << (dark > 0) << ' ' << argv[optind] << std::endl;
    }
  }
  return 0;
}
