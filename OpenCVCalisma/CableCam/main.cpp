#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv/cvaux.h>
#include <iostream>
#include <time.h>
#include <iomanip>

#include "StickmanDetector.h"
#include "cmake-build-debug/CableSlope.h"

using  namespace cv;
using  namespace std;



int main() {
    std::cout << "Hello, World!" << std::endl;

    StickmanDetector myDetector;
    CableSlope cblDetector;


//    myDetector.videoCapturing();
    cblDetector.videoCapturing();

    return 0;
}

