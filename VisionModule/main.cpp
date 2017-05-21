#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv/cvaux.h>
#include <iostream>
#include <time.h>
#include <iomanip>

#include "StickmanDetector.h"
#include "CableSlope.h"

using  namespace cv;
using  namespace std;



int main() {
    std::cout << "Hello, World!" << std::endl;
    char key;
    StickmanDetector myDetector(0);
    //CableSlope mySlope(1);
    int i = 0;
    key = 'a';

    while(key != 'q'){
        key = waitKey(25);

    //  if( mySlope.detectSingleFrame()) {
           myDetector.captureSingleFrame();
           StickManData data = myDetector.getTheCapturedStickMan();

          data.printTheStickMan() ;

           if(data.getHeadRadius() != -1){
               cout<< "( " << i << ")" <<"------- STOP  --------"<<endl;
               ++i;
           }
       //
      //}

    }
    //myDetector.videoCapturing();

    return 0;
}

