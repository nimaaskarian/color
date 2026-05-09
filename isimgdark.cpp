#include "color.h"
#include <execution>
#include <getopt.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>

int main(int argc, char *argv[]) {
    using namespace cv;
    int c;
    bool nulldelimited = 0, print_luminance = 0;
    double threshold = 0.5;
    while (!nulldelimited || !print_luminance) {
        static struct option long_options[] = {
            {"null", no_argument, 0, '0'},
            {"luminance", no_argument, 0, 'l'},
            {"threshold", required_argument, 0, 't'},
            {0, 0, 0, 0}};

        c = getopt_long(argc, argv, "0lt:", long_options, 0);
        if (c == -1) {
            break;
        }
        switch (c) {
        case 0:
            break;
        case '0':
            nulldelimited = true;
            break;
        case 'l':
            print_luminance = true;
            break;
        case 't':
            threshold = atof(optarg);
            break;
        }
    }
    char end;
    if (nulldelimited) {
        end = '\0';
    } else {
        end = '\n';
    }
    std::for_each(std::execution::par, argv + optind, argv + argc,
                  [end, print_luminance, threshold](char *s) {
                      Mat img = imread(s);
                      if (img.empty()) {
                          std::cerr << "error: failed to load image\n";
                          return;
                      }
                      img.convertTo(img, CV_32F, 1.0 / 255.0);
                      Mat mask = img <= NORMALIZE_THRESHOLD;
                      Mat lower, upper;
                      Mat tmp =
                          (img + NORMALIZE_UPPER_ADD) / NORMALIZE_UPPER_DIVIDE;
                      pow(tmp, NORMALIZE_UPPER_POW, upper);
                      divide(img, NORMALIZE_LOWER_DIVIDE, lower);
                      Mat linear = Mat::zeros(img.size(), img.type());
                      upper.copyTo(linear);
                      lower.copyTo(linear, mask);
                      std::vector<Mat> bgr;
                      split(linear, bgr);

                      Mat luminance_matrix =
                          relative_luminance_rgb(bgr[2], bgr[1], bgr[0]);
                      double luminance = mean(luminance_matrix)[0];
                      if (print_luminance) {
                          std::cout << luminance << ' ' << s << end;
                      } else {
                          std::cout << (luminance < threshold) << ' ' << s
                                    << end;
                      }
                      std::cout.flush();
                  });
    return 0;
}
