//
// Created by Zhibo Zhou on 2019-05-06.
//

#ifndef STEREOPSIS_IMAGE_IO_H
#define STEREOPSIS_IMAGE_IO_H


#include <opencv2/opencv.hpp>

void ReadGroundTruthImage(cv::Mat &ground_truth_img,std::string input_folder_name, std::string img_name);

void ReadResultImage(cv::Mat &result_img,std::string method, std::string input_folder_name, std::string img_name);

void ReadBinocularImage(cv::Mat &left_img, cv::Mat &right_img, std::string folder_name, std::string img_name);

void WriteDisparityImage(cv::Mat &disparity_img, std::string method, std::string output_folder_name, std::string img_name);

#endif //STEREOPSIS_IMAGE_IO_H
