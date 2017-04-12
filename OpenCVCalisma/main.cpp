#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <time.h>
#include <iomanip>

using  namespace cv;
using  namespace std;
void videoCapturing();

int main() {
    std::cout << "Hello, World!" << std::endl;

    videoCapturing();

    return 0;
}

void videoCapturing()
{
    Mat image;
    char key = 'e';
    time_t start, end;
    int counter = 0;
    double sec;
    double fps;



    VideoCapture capturer(0);

    capturer.set(CV_CAP_PROP_FRAME_WIDTH,480);
    capturer.set(CV_CAP_PROP_FRAME_HEIGHT,480);

    if(!capturer.isOpened()){
        cout<<"Failed to open camera"<<endl;
        exit(0);
    }


    while(key != 'q'){
        key = waitKey(25);

        if (counter == 0){
            time(&start);
        }

        capturer>>image;



        time(&end);
        counter++;

        sec = difftime(end, start);
        fps = counter / sec;

        if (counter == (INT_MAX - 1000))
            counter = 0;

        ostringstream convert;
        if(counter>30) {
            convert << fixed << setprecision(3) << fps;
        }

        String fpsRes = "FPS : " + convert.str();
        putText(image, fpsRes , cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,255), 1);
        imshow("image : ",image);




    }
}



