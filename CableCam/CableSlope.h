//
// Created by ERDI ERKMEN on 13.05.2017.
//

#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv/cvaux.h>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <cmath>



using  namespace cv;
using  namespace std;

class CableSlope {
public:
    void videoCapturing();
    void printTextToVideo(Mat image,String text, Point point);
    string convertDoubleToString(double x);
    void displayFotoNums(Mat output, string message ,double displayNum, Point place);
    bool detectTheStickMan(Mat stickManFoto);

};

