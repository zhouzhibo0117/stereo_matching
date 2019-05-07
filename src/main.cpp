
#include "include/image_io.h"
#include "include/matching_methods.h"
#include "include/error_analysis.h"

#include <iostream>
#include <opencv2/opencv.hpp>

int main() {

    const std::string img_name[] = {
            "Aloe",
            "Baby1",
            "Baby2",
            "Baby3",
            "Bowling1",
            "Bowling2",
            "Cloth1",
            "Cloth2",
            "Cloth3",
            "Cloth4",
            "Flowerpots",
            "Lampshade1",
            "Lampshade2",
            "Midd1",
            "Midd2",
            "Monopoly",
            "Plastic",
            "Rocks1",
            "Rocks2",
            "Wood1",
            "Wood2"
    };

    const std::string method_name[] = {
            "SSD",
            "MSD",
            "SAD",
            "MAD",
            "NCC"
    };

    const std::string data_folder_name = "../data/ALL-2views/";
    const std::string result_folder_name = "../results/";

    for (auto &name : img_name) {
        cv::Mat left_img, right_img;
        cv::Mat disparity_img;
        cv::Mat ground_truth_img;
        cv::Mat result_img;

        // Reading files.
        ReadGroundTruthImage(ground_truth_img, data_folder_name, name);
        ReadBinocularImage(left_img, right_img, data_folder_name, name);

        for (auto &method : method_name) {
            // Matching binocular images.
            disparity_img = StereoMatching(left_img, right_img, method,80,1);
            // Writing output image.
            WriteDisparityImage(disparity_img, method, result_folder_name + method + "/", name);
            // Analyze error.
            ReadResultImage(result_img, method, result_folder_name + method + "/", name);
            AnalyzeError(ground_truth_img, result_img, method);
        }
    }

    return 0;
}


