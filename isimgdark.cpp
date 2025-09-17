#include <cstdint>
#include <iostream>
#include <vector>
#include <opencv4/opencv2/core/version.hpp>
#include <opencv4/opencv2/core/cvdef.h>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include "color.h"

int main(int argc, char *argv[])
{
  for (int i = 1; argv[i]; i++) {
    cv::Mat img = cv::imread(argv[i]);
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
    std::cout << (dark > 0) << ' ' << argv[i] << std::endl;
  }
  return 0;
}
