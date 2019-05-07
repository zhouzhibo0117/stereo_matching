//
// Created by Zhibo Zhou on 2019-05-06.
//

#include "include/image_io.h"

void ReadGroundTruthImage(cv::Mat &ground_truth_img, std::string input_folder_name, std::string img_name) {
    ground_truth_img = cv::imread(input_folder_name + img_name + "/disp5.png");
}

void ReadResultImage(cv::Mat &result_img,std::string method, std::string input_folder_name, std::string img_name) {
    result_img = cv::imread(input_folder_name + img_name + "_" + method + ".png");
}

void ReadBinocularImage(cv::Mat &left_img, cv::Mat &right_img, std::string input_folder_name, std::string img_name) {
    left_img = cv::imread(input_folder_name + img_name + "/view1.png");
    right_img = cv::imread(input_folder_name + img_name + "/view5.png");
}

void
WriteDisparityImage(cv::Mat &disparity_img, std::string method, std::string output_folder_name, std::string img_name) {
    cv::imwrite(output_folder_name + img_name + "_" + method + ".png", disparity_img);
}