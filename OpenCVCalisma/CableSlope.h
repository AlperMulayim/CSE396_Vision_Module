//
// Created by ERDI ERKMEN on 13.05.2017.
//

#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"




using  namespace cv;
using  namespace std;

class CableSlope {
public:
    CableSlope(int canNum);
    void videoCapturing();
    void printTextToVideo(Mat image,String text, Point point);
    string convertDoubleToString(double x);
    void displayFotoNums(Mat output, string message ,double displayNum, Point place);
    bool detectSlope(Mat stickManFoto);

    bool detectSingleFrame();
private:
    VideoCapture slopeCapture;
};

