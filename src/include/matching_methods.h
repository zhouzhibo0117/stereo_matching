//
// Created by Zhibo Zhou on 2019-05-06.
//

#ifndef STEREOPSIS_MATCHING_METHODS_H
#define STEREOPSIS_MATCHING_METHODS_H

#include <opencv2/opencv.hpp>

cv::Mat ssd(const cv::Mat &in1, const cv::Mat &in2, int max_offset,int kernel_size,const std::string &type);

cv::Mat msd(const cv::Mat &in1, const cv::Mat &in2, int max_offset,int kernel_size,const std::string &type);

cv::Mat sad(const cv::Mat &in1, const cv::Mat &in2, int max_offset,int kernel_size,const std::string &type);

cv::Mat mad(const cv::Mat &in1, const cv::Mat &in2, int max_offset,int kernel_size,const std::string &type);

cv::Mat ncc(const cv::Mat &in1, const cv::Mat &in2, int max_offset,int kernel_size,const std::string &type);

cv::Mat StereoMatching(const cv::Mat &in1, const cv::Mat &in2,const std::string &method, int max_offset=80,int kernel_size=3,const std::string &type="right");

#endif //STEREOPSIS_MATCHING_METHODS_H
