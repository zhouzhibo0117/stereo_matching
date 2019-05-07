//
// Created by Zhibo Zhou on 2019-05-06.
//

#ifndef STEREOPSIS_ERROR_ANALYSIS_H
#define STEREOPSIS_ERROR_ANALYSIS_H

#include <opencv2/opencv.hpp>

double AnalyzeError(cv::Mat &ground_truth_right,cv::Mat &test_img_right, std::string type);

#endif //STEREOPSIS_ERROR_ANALYSIS_H
