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
    Mat outImage;
    char key = 'e';
    time_t start, end;
    int counter = 0;
    double sec;
    double fps;
    int imageNum = 0;

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    VideoCapture capturer(1);

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
       // putText(image, fpsRes , cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,255), 1);
        imshow("image : ",image);
        Mat output;
        image.copyTo(output);
        image.copyTo(outImage);
        cvtColor(image, image, COLOR_BGR2GRAY);
        GaussianBlur(image, image, Size(7,7), 1.5, 1.5);
        imshow("Gaus Result",image);
        Mat cannyOut;
        Canny(image, cannyOut, 0, 30, 3);
        imshow("Canny Result",cannyOut);
        GaussianBlur(cannyOut, cannyOut, Size(19,19), 1.5, 1.5);
        imshow("GausCanny Result",cannyOut);
        findContours(cannyOut, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        for (int i = 0; i < contours.size(); i++) {
            Scalar color = Scalar(0, 0, 255);

            drawContours(output, contours, i, color, 2, 8, hierarchy, 0, Point());
            double area = contourArea(contours[i]);
            Rect boundRect;
            boundRect = boundingRect(contours[i]);

            if (area > 2000 ) {
                rectangle(output, boundRect, Scalar(0, 255, 0), 2, 8, 0);

                stringstream ss;
                ss << imageNum;
                string name = "CinaliPos\\" + ss.str() + ".png";
                ++imageNum;

                imwrite(name, outImage(boundRect));
                imshow("imageCont : ", output);

            }
        }

    }
}



