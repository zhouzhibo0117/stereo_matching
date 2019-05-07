//
// Created by Zhibo Zhou on 2019-05-06.
//

#include "include/error_analysis.h"

#include <fstream>

double AnalyzeError(cv::Mat &ground_truth_right,cv::Mat &test_img_right, std::string type) {

    int width = ground_truth_right.size().width;
    int height = ground_truth_right.size().height;

    int bad_pixels_right = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int delta = abs(test_img_right.at<uchar>(y, x) - ground_truth_right.at<uchar>(y, x));
            if (delta > 2 && test_img_right.at<uchar>(y, x) != 0)
            {
                bad_pixels_right++;
            }
        }
    }

    double rate_right = double(height * width - bad_pixels_right) / (height * width); //
//    printf("  Accuracy: %.4lf%% \n", rate_right * 100);
    printf("%.4lf%% \n", rate_right * 100);

    return rate_right;
}