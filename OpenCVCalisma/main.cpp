#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv/cvaux.h>
#include <iostream>
#include <time.h>
#include <iomanip>

#include "StickmanDetector.h"

using  namespace cv;
using  namespace std;



int main() {
    std::cout << "Hello, World!" << std::endl;
    char key;
    StickmanDetector myDetector(0);

    key = 'a';

    while(key != 'q'){
        key = waitKey(25);
        myDetector.captureSingleFrame();
        StickManData data = myDetector.getTheCapturedStickMan();
        data.printTheStickMan();

    }
    //myDetector.videoCapturing();

    return 0;
}

