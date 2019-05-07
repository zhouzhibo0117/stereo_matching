//
// Created by Zhibo Zhou on 2019-05-06.
//

#include "include/basic_image_processing.h"

cv::Mat bgr2gray(const cv::Mat &bgr) {
    int width = bgr.size().width;
    int height = bgr.size().height;
    cv::Mat gray(height, width, 0);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uchar r = 0.333 * bgr.at<cv::Vec3b>(y, x)[2];
            uchar g = 0.333 * bgr.at<cv::Vec3b>(y, x)[1];
            uchar b = 0.333 * bgr.at<cv::Vec3b>(y, x)[0];
            gray.at<uchar>(y, x) = uchar(r + g + b);
        }
    }

    return gray;
}