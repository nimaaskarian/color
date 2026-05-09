#include <getopt.h>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>

#include <execution>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

using json = nlohmann::json;
namespace fs = std::filesystem;

cv::Vec3f hexToBGR(const std::string &hex) {
    int r = std::stoi(hex.substr(1, 2), nullptr, 16);
    int g = std::stoi(hex.substr(3, 2), nullptr, 16);
    int b = std::stoi(hex.substr(5, 2), nullptr, 16);
    return cv::Vec3f(b, g, r);
}

cv::Vec3f BGR2Lab(const cv::Vec3f &color) {
    cv::Mat bgr(1, 1, CV_32FC3);
    bgr.at<cv::Vec3f>(0, 0) = color / 255.0f;

    cv::Mat lab;
    cv::cvtColor(bgr, lab, cv::COLOR_BGR2Lab);
    return lab.at<cv::Vec3f>(0, 0);
}

struct DominantColor {
    cv::Vec3f color;
    float weight;
};

// uses k-means
std::vector<DominantColor> extractDominantColors(const cv::Mat &img,
                                                 int K = 5) {
    cv::Mat data;
    img.convertTo(data, CV_32F);
    data = data.reshape(3, img.rows * img.cols);

    cv::Mat labels, centers;
    cv::kmeans(data, K, labels,
               cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT,
                                10, 1.0),
               3, cv::KMEANS_PP_CENTERS, centers);

    std::vector<int> counts(K, 0);
    for (int i = 0; i < labels.rows; i++) {
        counts[labels.at<int>(i)]++;
    }

    std::vector<DominantColor> result;
    int total = labels.rows;

    for (int i = 0; i < K; i++) {
        cv::Vec3f c;
        c[0] = centers.at<float>(i, 0);
        c[1] = centers.at<float>(i, 1);
        c[2] = centers.at<float>(i, 2);

        float weight = static_cast<float>(counts[i]) / total;

        result.push_back({c, weight});
    }

    return result;
}

std::vector<cv::Vec3f> loadPaletteFromJsonFile(const std::string &path) {
    std::ifstream f(path);
    json j;
    f >> j;

    std::vector<cv::Vec3f> colors;

    for (auto &[key, value] : j["colors"].items()) {
        colors.push_back(hexToBGR(value));
    }
    for (auto &[key, value] : j["special"].items()) {
        colors.push_back(hexToBGR(value));
    }

    return colors;
}

std::vector<cv::Vec3f> deduplicate(const std::vector<cv::Vec3f> &colors) {
    std::vector<cv::Vec3f> unique;

    for (const auto &c : colors) {
        bool found = false;
        for (const auto &u : unique) {
            if (cv::norm(c - u) < 1.0f) {
                found = true;
                break;
            }
        }
        if (!found)
            unique.push_back(c);
    }

    return unique;
}

float computePaletteDistance(const std::vector<DominantColor> &imgColors,
                             const std::vector<cv::Vec3f> &paletteColors) {
    float total = 0.0f;

    for (const auto &dc : imgColors) {
        cv::Vec3f lab1 = BGR2Lab(dc.color);

        float minDist = FLT_MAX;

        for (const auto &p : paletteColors) {
            cv::Vec3f lab2 = BGR2Lab(p);
            float dist = cv::norm(lab1 - lab2);
            minDist = std::min(minDist, dist);
        }

        total += dc.weight * minDist;
    }

    return total;
}

struct Palette {
    std::string path;
    std::vector<cv::Vec3f> colors;
};
int main(int argc, char *argv[]) {

    int c;
    std::string imagePath = "";
    bool nulldelimited = 0;
    struct passwd *pw = getpwuid(getuid());

    std::string paletteDir = pw->pw_dir;
    paletteDir += "/.config/wal-colorschemes/dark/";

    while (true) {
        static struct option long_options[] = {
            {"null", no_argument, 0, '0'},
            {"theme-dir", required_argument, 0, 't'},
            {0, 0, 0, 0}};

        c = getopt_long(argc, argv, "0i:t:", long_options, 0);
        if (c == -1) {
            break;
        }
        switch (c) {
        case 0:
            break;
        case 'i':
            imagePath = optarg;
            break;
        case 't':
            paletteDir = optarg;
            break;
        case '0':
            nulldelimited = true;
            break;
        }
    }
    if (optind == argc) {
        return 0;
    }
    char end;
    if (nulldelimited) {
        end = '\0';
    } else {
        end = '\n';
    }
    std::vector<Palette> palettes;
    for (const auto &entry : fs::directory_iterator(paletteDir)) {
        palettes.push_back({
            .path = entry.path().string(),
            .colors = loadPaletteFromJsonFile(entry.path().string()),
        });
    }

    std::for_each(
        std::execution::par, argv + optind, argv + argc,
        [paletteDir, palettes, end](char *filename) {
            cv::Mat img = cv::imread(filename);
            if (img.empty()) {
                std::cerr << "failed to a load image: " << filename << '\n';
            }

            cv::resize(img, img, cv::Size(1000, 1000));
            cv::Mat imgLab;
            cv::cvtColor(img, imgLab, cv::COLOR_BGR2Lab);

            std::vector<cv::Mat> channels;
            cv::split(imgLab, channels);

            // normalize L channel
            cv::normalize(channels[0], channels[0], 0, 255, cv::NORM_MINMAX);

            cv::merge(channels, imgLab);
            cv::cvtColor(imgLab, img, cv::COLOR_Lab2BGR);

            auto imgColors = extractDominantColors(img, 8);

            float bestScore = FLT_MAX;
            std::string bestPalette;
            for (auto &palette : palettes) {
                float score = computePaletteDistance(imgColors, palette.colors);
                if (score < bestScore) {
                    bestScore = score;
                    bestPalette = palette.path;
                }
            }

            std::cout << bestScore << '\t' << bestPalette << '\t' << filename
                      << end;
        });

    return 0;
}
