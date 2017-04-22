#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv/cvaux.h>
#include <iostream>
#include <time.h>
#include <iomanip>

#define IMAGE_SIZE Size(64,128)
using  namespace cv;
using  namespace std;

void videoCapturing();
void printTextToVideo(Mat image,String text, Point point);
string convertDoubleToString(double x);
void displayFotoNums(Mat output, string message ,double displayNum, Point place);
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
    int imageNumPos = 0;
    int imageNumNeg = 0;

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
       // imshow("image : ",image);
        Mat output;
        image.copyTo(output);
        image.copyTo(outImage);
        cvtColor(image, image, COLOR_BGR2GRAY);
        GaussianBlur(image, image, Size(7,7), 1.5, 1.5);
        //imshow("Gaus Result",image);
        Mat cannyOut;
        Canny(image, cannyOut, 0, 30, 3);
        //imshow("Canny Result",cannyOut);
        GaussianBlur(cannyOut, cannyOut, Size(19,19), 1.5, 1.5);
        imshow("GausCanny Result",cannyOut);
        findContours(cannyOut, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        for (int i = 0; i < contours.size(); i++) {
            Scalar color = Scalar(0, 0, 255);

            drawContours(output, contours, i, color, 2, 8, hierarchy, 0, Point());
            double area = contourArea(contours[i]);
            Rect boundRect;
            boundRect = boundingRect(contours[i]);
            //displayFotoNums(output,"Area : " ,area,Point(20,120));
            if (area > 4000 ) {
                rectangle(output, boundRect, Scalar(0, 255, 0), 2, 8, 0);

                stringstream ss;
                ss << imageNumPos;
                string name = "CinaliPos\\" + ss.str() + ".png";
                ++imageNumPos;


                Mat im = outImage(boundRect);
                resize(im,im,IMAGE_SIZE);
                imwrite(name, im);

                imwrite(name, im);
                displayFotoNums(output,"Foto Pos : " ,imageNumPos,Point(15,60));
                // putText(image, imageNumPos , cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,255), 1);
                imshow("imageCont : ", output);
            }
            else if( area > 500 && area < 4000 ){
                rectangle(output, boundRect, Scalar(0, 255, 0), 2, 8, 0);

                stringstream ss;
                ss << imageNumNeg;
                string name = "CinaliNeg\\" + ss.str() + ".png";
                ++imageNumNeg;
                Mat im = outImage(boundRect);
                resize(im,im,IMAGE_SIZE);
                imwrite(name, im);
                displayFotoNums(output,"Foto Neg : " ,imageNumNeg,Point(15,80));
                imshow("imageCont : ", output);
            }
        }

    }
}

void displayFotoNums(Mat output, string message ,double displayNum, Point place)
{

    string numstr = convertDoubleToString(displayNum);
    string textRight = message + numstr;
    printTextToVideo(output,textRight, place);
}

void printTextToVideo(Mat image,String text, Point point)
{
    putText(image,text, point, FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0));
}

string convertDoubleToString(double x)
{
    ostringstream strs;
    strs << x;
    string str = strs.str();
    return str;
}
