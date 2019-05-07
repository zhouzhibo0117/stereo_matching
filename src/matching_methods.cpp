//
// Created by Zhibo Zhou on 2019-05-06.
//

#include "include/matching_methods.h"
#include "include/basic_image_processing.h"

cv::Mat ssd(const cv::Mat &in1, const cv::Mat &in2, int max_offset, int kernel_size, const std::string &type) {
    int width = in1.size().width;
    int height = in1.size().height;

    cv::Mat depth(height, width, 0);
    std::vector<std::vector<int> > min_ssd; // store min SSD values

    cv::Mat left = bgr2gray(in1);
    cv::Mat right = bgr2gray(in2);

    for (int i = 0; i < height; ++i) {
        std::vector<int> tmp(width, std::numeric_limits<int>::max());
        min_ssd.push_back(tmp);
    }

    std::cout << "Start SSD Matching ... ";

    for (int offset = 0; offset <= max_offset; offset++) {
        cv::Mat tmp(height, width, 0);
        // shift image depend on type to save calculation time
        if (type == "left") {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < offset; x++) {
                    tmp.at<uchar>(y, x) = right.at<uchar>(y, x);
                }

                for (int x = offset; x < width; x++) {
                    tmp.at<uchar>(y, x) = right.at<uchar>(y, x - offset);
                }
            }
        } else if (type == "right") {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width - offset; x++) {
                    tmp.at<uchar>(y, x) = left.at<uchar>(y, x + offset);
                }

                for (int x = width - offset; x < width; x++) {
                    tmp.at<uchar>(y, x) = left.at<uchar>(y, x);
                }
            }
        } else {
            cv::Mat tmpnull(0, 0, 0);
            return tmpnull;
        }

        // calculate each pixel's SSD value
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int start_x = std::max(0, x - kernel_size);
                int start_y = std::max(0, y - kernel_size);
                int end_x = std::min(width - 1, x + kernel_size);
                int end_y = std::min(height - 1, y + kernel_size);
                int sum_sd = 0;

                if (type == "left") {
                    for (int i = start_y; i <= end_y; i++) {
                        for (int j = start_x; j <= end_x; j++) {
                            int delta = abs(left.at<uchar>(i, j) - tmp.at<uchar>(i, j));
                            sum_sd += delta * delta;
                        }
                    }
                } else {
                    for (int i = start_y; i <= end_y; i++) {
                        for (int j = start_x; j <= end_x; j++) {
                            int delta = abs(right.at<uchar>(i, j) - tmp.at<uchar>(i, j));
                            sum_sd += delta * delta;
                        }
                    }
                }

                // smaller SSD value found
                if (sum_sd < min_ssd[y][x]) {
                    min_ssd[y][x] = sum_sd;
                    // for better visualization
                    depth.at<uchar>(y, x) = (uchar) (offset * 3);
                }
            }
        }
//        std::cout << "Operating with an offset of " << offset << " pixels." << std::endl;
    }

    std::cout << " Finished. " << std::endl;

    return depth;
}

cv::Mat msd(const cv::Mat &in1, const cv::Mat &in2, int max_offset, int kernel_size, const std::string &type) {
    int width = in1.size().width;
    int height = in1.size().height;

    cv::Mat depth(height, width, 0);
    std::vector<std::vector<double> > min_msd; // store min SSD values

    cv::Mat left = bgr2gray(in1);
    cv::Mat right = bgr2gray(in2);

    for (int i = 0; i < height; ++i) {
        std::vector<double> tmp(width, std::numeric_limits<double>::max());
        min_msd.push_back(tmp);
    }

    std::cout << "Start MSD Matching ... ";

    for (int offset = 0; offset <= max_offset; offset++) {
        cv::Mat tmp(height, width, 0);
        // shift image depend on type to save calculation time
        if (type == "left") {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < offset; x++) {
                    tmp.at<uchar>(y, x) = right.at<uchar>(y, x);
                }

                for (int x = offset; x < width; x++) {
                    tmp.at<uchar>(y, x) = right.at<uchar>(y, x - offset);
                }
            }
        } else if (type == "right") {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width - offset; x++) {
                    tmp.at<uchar>(y, x) = left.at<uchar>(y, x + offset);
                }

                for (int x = width - offset; x < width; x++) {
                    tmp.at<uchar>(y, x) = left.at<uchar>(y, x);
                }
            }
        } else {
            cv::Mat tmpnull(0, 0, 0);
            return tmpnull;
        }

        // calculate each pixel's SSD value
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int start_x = std::max(0, x - kernel_size);
                int start_y = std::max(0, y - kernel_size);
                int end_x = std::min(width - 1, x + kernel_size);
                int end_y = std::min(height - 1, y + kernel_size);
                int sum_sd = 0;
                double mean_sd = 0.0;

                if (type == "left") {
                    for (int i = start_y; i <= end_y; i++) {
                        for (int j = start_x; j <= end_x; j++) {
                            int delta = abs(left.at<uchar>(i, j) - tmp.at<uchar>(i, j));
                            sum_sd += delta * delta;
                        }
                    }
                    mean_sd = double(sum_sd) / double((end_y - start_y) * (end_x - start_x));
                } else {
                    for (int i = start_y; i <= end_y; i++) {
                        for (int j = start_x; j <= end_x; j++) {
                            int delta = abs(right.at<uchar>(i, j) - tmp.at<uchar>(i, j));
                            sum_sd += delta * delta;
                        }
                    }
                    mean_sd = double(sum_sd) / double((end_y - start_y) * (end_x - start_x));
                }

                if (mean_sd < min_msd[y][x]) {
                    min_msd[y][x] = mean_sd;
                    // for better visualization
                    depth.at<uchar>(y, x) = (uchar) (offset * 3);
                }
            }
        }
//        std::cout << "Operating with an offset of " << offset << " pixels." << std::endl;
    }

    std::cout << " Finished. " << std::endl;

    return depth;
}

cv::Mat sad(const cv::Mat &in1, const cv::Mat &in2, int max_offset, int kernel_size, const std::string &type) {
    int width = in1.size().width;
    int height = in1.size().height;

    cv::Mat depth(height, width, 0);
    std::vector<std::vector<int> > min_sad; // store min SAD values

    cv::Mat left = bgr2gray(in1);
    cv::Mat right = bgr2gray(in2);

    for (int i = 0; i < height; ++i) {
        std::vector<int> tmp(width, std::numeric_limits<int>::max());
        min_sad.push_back(tmp);
    }

    std::cout << "Start SAD Matching ... ";

    for (int offset = 0; offset <= max_offset; offset++) {
        cv::Mat tmp(height, width, 0);
        // shift image depend on type to save calculation time
        if (type == "left") {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < offset; x++) {
                    tmp.at<uchar>(y, x) = right.at<uchar>(y, x);
                }

                for (int x = offset; x < width; x++) {
                    tmp.at<uchar>(y, x) = right.at<uchar>(y, x - offset);
                }
            }
        } else if (type == "right") {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width - offset; x++) {
                    tmp.at<uchar>(y, x) = left.at<uchar>(y, x + offset);
                }

                for (int x = width - offset; x < width; x++) {
                    tmp.at<uchar>(y, x) = left.at<uchar>(y, x);
                }
            }
        } else {
            cv::Mat tmpnull(0, 0, 0);
            return tmpnull;
        }

        // calculate each pixel's SSD value
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int start_x = std::max(0, x - kernel_size);
                int start_y = std::max(0, y - kernel_size);
                int end_x = std::min(width - 1, x + kernel_size);
                int end_y = std::min(height - 1, y + kernel_size);
                int sum_ad = 0;

                if (type == "left") {
                    for (int i = start_y; i <= end_y; i++) {
                        for (int j = start_x; j <= end_x; j++) {
                            int delta = abs(left.at<uchar>(i, j) - tmp.at<uchar>(i, j));
                            sum_ad += delta;
                        }
                    }
                } else {
                    for (int i = start_y; i <= end_y; i++) {
                        for (int j = start_x; j <= end_x; j++) {
                            int delta = abs(right.at<uchar>(i, j) - tmp.at<uchar>(i, j));
                            sum_ad += delta;
                        }
                    }
                }

                // smaller SAD value found
                if (sum_ad < min_sad[y][x]) {
                    min_sad[y][x] = sum_ad;
                    // for better visualization
                    depth.at<uchar>(y, x) = (uchar) (offset * 3);
                }
            }
        }
//        std::cout << "Operating with an offset of " << offset << " pixels." << std::endl;
    }

    std::cout << " Finished. " << std::endl;

    return depth;
}

cv::Mat mad(const cv::Mat &in1, const cv::Mat &in2, int max_offset, int kernel_size, const std::string &type) {
    int width = in1.size().width;
    int height = in1.size().height;

    cv::Mat depth(height, width, 0);
    std::vector<std::vector<double> > min_mad; // store min SAD values

    cv::Mat left = bgr2gray(in1);
    cv::Mat right = bgr2gray(in2);

    for (int i = 0; i < height; ++i) {
        std::vector<double> tmp(width, std::numeric_limits<double>::max());
        min_mad.push_back(tmp);
    }

    std::cout << "Start SAD Matching ... ";

    for (int offset = 0; offset <= max_offset; offset++) {
        cv::Mat tmp(height, width, 0);
        // shift image depend on type to save calculation time
        if (type == "left") {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < offset; x++) {
                    tmp.at<uchar>(y, x) = right.at<uchar>(y, x);
                }

                for (int x = offset; x < width; x++) {
                    tmp.at<uchar>(y, x) = right.at<uchar>(y, x - offset);
                }
            }
        } else if (type == "right") {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width - offset; x++) {
                    tmp.at<uchar>(y, x) = left.at<uchar>(y, x + offset);
                }

                for (int x = width - offset; x < width; x++) {
                    tmp.at<uchar>(y, x) = left.at<uchar>(y, x);
                }
            }
        } else {
            cv::Mat tmpnull(0, 0, 0);
            return tmpnull;
        }

        // calculate each pixel's SSD value
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int start_x = std::max(0, x - kernel_size);
                int start_y = std::max(0, y - kernel_size);
                int end_x = std::min(width - 1, x + kernel_size);
                int end_y = std::min(height - 1, y + kernel_size);
                int sum_ad = 0;
                double mean_ad = 0.0;

                if (type == "left") {
                    for (int i = start_y; i <= end_y; i++) {
                        for (int j = start_x; j <= end_x; j++) {
                            int delta = abs(left.at<uchar>(i, j) - tmp.at<uchar>(i, j));
                            sum_ad += delta;
                        }
                    }
                    mean_ad = double(sum_ad) / double((end_y - start_y) * (end_x - start_x));
                } else {
                    for (int i = start_y; i <= end_y; i++) {
                        for (int j = start_x; j <= end_x; j++) {
                            int delta = abs(right.at<uchar>(i, j) - tmp.at<uchar>(i, j));
                            sum_ad += delta;
                        }
                    }
                    mean_ad = double(sum_ad) / double((end_y - start_y) * (end_x - start_x));
                }

                // smaller SAD value found
                if (mean_ad < min_mad[y][x]) {
                    min_mad[y][x] = mean_ad;
                    // for better visualization
                    depth.at<uchar>(y, x) = (uchar) (offset * 3);
                }
            }
        }
//        std::cout << "Operating with an offset of " << offset << " pixels." << std::endl;
    }

    std::cout << " Finished. " << std::endl;

    return depth;
}

cv::Mat ncc(const cv::Mat &in1, const cv::Mat &in2, int max_offset, int kernel_size, const std::string &type) {
    int width = in1.size().width;
    int height = in1.size().height;

    cv::Mat left = bgr2gray(in1);
    cv::Mat right = bgr2gray(in2);

    cv::Mat depth(height, width, 0);
    std::vector<std::vector<double> > max_ncc; // store max NCC value

    for (int i = 0; i < height; ++i) {
        std::vector<double> tmp(width, -2);
        max_ncc.push_back(tmp);
    }

//    std::cout << "Start NCC Matching ... ";

    for (int offset = 1; offset <= max_offset; offset++) {
        cv::Mat tmp(height, width, 0);
        // shift image depend on type to save calculation time
        if (type == "left") {

            for (int y = 0; y < height; y++) {

                for (int x = 0; x < offset; x++) {
                    tmp.at<uchar>(y, x) = right.at<uchar>(y, x);

                }

                for (int x = offset; x < width; x++) {
                    tmp.at<uchar>(y, x) = right.at<uchar>(y, x - offset);
                }
            }
        } else if (type == "right") {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width - offset; x++) {
                    tmp.at<uchar>(y, x) = left.at<uchar>(y, x + offset);
                }

                for (int x = width - offset; x < width; x++) {
                    tmp.at<uchar>(y, x) = left.at<uchar>(y, x);
                }
            }
        } else {
            cv::Mat tmpnull(0, 0, 0);
            return tmpnull;
        }

        // calculate each pixel's NCC value
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int start_x = std::max(0, x - kernel_size);
                int start_y = std::max(0, y - kernel_size);
                int end_x = std::min(width - 1, x + kernel_size);
                int end_y = std::min(height - 1, y + kernel_size);
                double n = (end_y - start_y) * (end_x - start_x);
                double res_ncc = 0;

                if (type == "left") {
                    double left_mean = 0, right_mean = 0;
                    double left_std = 0, right_std = 0;
                    double numerator = 0;

                    for (int i = start_y; i <= end_y; i++) {
                        for (int j = start_x; j <= end_x; j++) {
                            left_mean += left.at<uchar>(i, j);
                            right_mean += tmp.at<uchar>(i, j);
                        }
                    }

                    left_mean /= n;
                    right_mean /= n;

                    for (int i = start_y; i <= end_y; i++) {
                        for (int j = start_x; j <= end_x; j++) {
                            left_std += pow(left.at<uchar>(i, j) - left_mean, 2);
                            right_std += pow(tmp.at<uchar>(i, j) - right_mean, 2);
                            numerator += (left.at<uchar>(i, j) - left_mean) * (tmp.at<uchar>(i, j) - right_mean);
                        }
                    }

                    numerator /= n;
                    left_std /= n;
                    right_std /= n;
                    res_ncc = numerator / (sqrt(left_std) * sqrt(right_std)) / n;
                } else {
                    double left_mean = 0, right_mean = 0;
                    double left_std = 0, right_std = 0;
                    double numerator = 0;

                    for (int i = start_y; i <= end_y; i++) {
                        for (int j = start_x; j <= end_x; j++) {
                            left_mean += tmp.at<uchar>(i, j);
                            right_mean += right.at<uchar>(i, j);
                        }
                    }

                    left_mean /= n;
                    right_mean /= n;

                    for (int i = start_y; i <= end_y; i++) {
                        for (int j = start_x; j <= end_x; j++) {
                            left_std += pow(tmp.at<uchar>(i, j) - left_mean, 2);
                            right_std += pow(right.at<uchar>(i, j) - right_mean, 2);
                            numerator += (tmp.at<uchar>(i, j) - left_mean) * (right.at<uchar>(i, j) - right_mean);
                        }
                    }

                    numerator /= n;
                    left_std /= n;
                    right_std /= n;
                    res_ncc = numerator / (sqrt(left_std) * sqrt(right_std)) / n;
                }

                // greater NCC value found
                if (res_ncc > max_ncc[y][x]) {
                    max_ncc[y][x] = res_ncc;
                    // for better visualization
                    depth.at<uchar>(y, x) = (uchar) (offset * 3);
                }


            }

        }
//        std::cout << "Operating with an offset of " << offset << " pixels." << std::endl;
    }

//    std::cout << " Finished. " << std::endl;

    return depth;
}

cv::Mat
StereoMatching(const cv::Mat &in1, const cv::Mat &in2, const std::string &method, int max_offset, int kernel_size,
               const std::string &type) {
    if (method == "SSD")
        return ssd(in1, in2, max_offset, kernel_size, type);
    else if (method == "MSD")
        return msd(in1, in2, max_offset, kernel_size, type);
    else if (method == "SAD")
        return sad(in1, in2, max_offset, kernel_size, type);
    else if (method == "MAD")
        return mad(in1, in2, max_offset, kernel_size, type);
    else if (method == "NCC")
        return ncc(in1, in2, max_offset, kernel_size, type);
    else
        exit(123);
}

