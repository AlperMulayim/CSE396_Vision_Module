#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv/cvaux.h>
#include <iostream>
#include <time.h>
#include <iomanip>

#define IMAGE_SIZE40_40 Size(40,40)
#define IMAGE_SIZE64_64 Size(64,64)
#define IMAGE_SIZE128_128 Size(128,128)
#define IMAGE_SIZE64_128 Size(64,128)

using  namespace cv;
using  namespace std;

void videoCapturing();
void printTextToVideo(Mat image,String text, Point point);
string convertDoubleToString(double x);
void displayFotoNums(Mat output, string message ,double displayNum, Point place);
void createTheData(Mat outImage, Rect boundRect, stringstream ss);


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
    Mat imageGoussOut;

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
        GaussianBlur(image, imageGoussOut, Size(7,7), 1.5, 1.5);
        //imshow("Gaus Result",image);
        Mat cannyOut;
        Canny(imageGoussOut, cannyOut, 0, 30, 3);
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
                string name = "CinaliPos40_40\\" + ss.str() + ".png";
                ++imageNumPos;


                vector<Vec3f> circles;
                /// Apply the Hough Transform to find the circles
                HoughCircles(imageGoussOut, circles, CV_HOUGH_GRADIENT, 1, imageGoussOut.rows/8, 75, 30, 0, 0 );



                Point centerM;
                int radiusM = 0;

                if(circles.size() != 0) {
                    for (size_t i = 0; i < circles.size(); i++) {
                        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));

                        centerM.x += center.x;
                        centerM.y += center.y;
                        radiusM += cvRound(circles[i][2]);

                    }

                    centerM.x = centerM.x / circles.size();
                    centerM.y = centerM.y / circles.size();

                    radiusM = radiusM / circles.size();


                    circle(output, centerM, 3, Scalar(0, 255, 255), -1, 8, 0);
                    // circle outline
                    circle(output, centerM, radiusM, Scalar(0, 255, 255), 3, 8, 0);
                }
                displayFotoNums(output,"Foto Pos : " ,imageNumPos,Point(15,60));
                // putText(image, imageNumPos , cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,255), 1);


                imshow("imageCont : ", output);
            }
            else if( area > 500 && area < 4000 ){
                rectangle(output, boundRect, Scalar(255, 0, 0), 2, 8, 0);

                stringstream ss;
                ss << imageNumNeg;
                string name = "CinaliNeg40_40\\" + ss.str() + ".png";
                ++imageNumNeg;



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

void createTheData(Mat outImage, Rect boundRect, stringstream ss)
{
    string name;
    Mat im = outImage(boundRect);
    resize(im,im,IMAGE_SIZE40_40);
    imwrite(name, im);

    name = "CinaliNeg64_64\\" + ss.str() + ".png";
    resize(im,im,IMAGE_SIZE64_64);
    imwrite(name, im);

    name = "CinaliNeg64_128\\" + ss.str() + ".png";
    resize(im,im,IMAGE_SIZE64_128);
    imwrite(name, im);

    name = "CinaliNeg128_128\\" + ss.str() + ".png";
    resize(im,im,IMAGE_SIZE128_128);
    imwrite(name, im);
}