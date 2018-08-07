#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat before = imread("D:\\research\\qrcode.jpg", 0);

    Mat dist;
    distanceTransform(before, dist, CV_DIST_L2, 3);

    imshow("before", before);
    imshow("non-normalized", dist);

    normalize(dist, dist, 0.0, 1.0, NORM_MINMAX);
    imshow("normalized", dist);
    waitKey();
    return 0;
}