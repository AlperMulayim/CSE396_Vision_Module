#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv/cvaux.h>
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


    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

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
        Mat output;
        image.copyTo(output);
        cvtColor(image, image, COLOR_BGR2GRAY);
        GaussianBlur(image, image, Size(7,7), 1.5, 1.5);
        Mat cannyOut;
        Canny(image, cannyOut, 0, 30, 3);


        findContours(cannyOut, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        for (int i = 0; i < contours.size(); i++) {
            Scalar color = Scalar(0, 0, 255);
            drawContours(output, contours, i, color, 2, 8, hierarchy, 0, Point());
            double area = contourArea(contours[i]);
            Rect boundRect;
            boundRect = boundingRect(contours[i]);
            rectangle(output, boundRect, Scalar(0, 255, 0), 2, 8, 0);
            imshow("imageCont : ",output);
        }


    }
}



