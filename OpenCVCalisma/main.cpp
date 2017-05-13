#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv/cvaux.h>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <pthread.h>

using  namespace cv;
using  namespace std;

void videoCapturing(VideoCapture capturer, Mat image, int counter, time_t start,time_t end, double sec, double fps);
void printTextToVideo(Mat image,String text, Point point);
string convertDoubleToString(double x);


int main() {
    Mat image;
    Mat imageCable;
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

    std::cout << "Cameras started" << std::endl;


    while(key != 'q') {
        key = waitKey(25);
        videoCapturing(capturer, image, counter, start, end, sec, fps);

    }
//    videoCapturing();
//
    return 0;
}


void videoCapturing(VideoCapture capturer, Mat image, int counter, time_t start,time_t end, double sec, double fps)
{

//    VideoCapture captureCable(2);
//    if (!captureCable.isOpened()) {
//        cout << "Cable Cam doesn't work" << endl;
//    }

    if (counter == 0){
        time(&start);
    }

//    while(key != 'q') {
//        key = waitKey(25);
        capturer >> image;
        imshow("IMAGE", image);
//    }
//
//    captureCable>>imageCable;
//    imshow("IMAGECAble",imageCable);


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
//
//    Mat output;
//    image.copyTo(output);
//
//    String fpsRes = "FPS : " + convert.str();
//    putText(output, fpsRes , cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,255), 1);
//    // imshow("image : ",image);
//
//    image.copyTo(outImage);
//    cvtColor(image, image, COLOR_BGR2GRAY);
//    GaussianBlur(image, imageGoussOut, Size(7,7), 1.5, 1.5);
//    //imshow("Gaus Result",imageGoussOut);
//    Mat cannyOut;
//    Canny(imageGoussOut, cannyOut, 0, 30, 3);
//
//    //imshow("Canny Result",cannyOut);
//    GaussianBlur(cannyOut, cannyOut, Size(7,7), 1.5, 1.5);
//
//    //TODO : Change this to Morphology
//    threshold(cannyOut,cannyOut,0,255,THRESH_BINARY);
//
//
//
//    imshow("GausCanny Result",cannyOut);
//    findContours(cannyOut, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//    double maxArea = 0;
//    for(int j = 0 ; j< contours.size() ; ++j){
//        if(maxArea < contourArea(contours[j])){
//            maxArea = contourArea(contours[j]);
//        }
//    }
//
//    for (int i = 0; i < contours.size(); i++) {
//        Scalar color = Scalar(0, 0, 255);
//        if (maxArea == contourArea(contours[i])) {
//            // drawContours(output, contours, i, color, 2, 8, hierarchy, 0, Point());
//            double area = contourArea(contours[i]);
//            RotatedRect boundRect;
//            boundRect = minAreaRect(contours[i]);
//
//
//            //displayFotoNums(output,"Area : " ,area,Point(20,120));
//            if (area > 4000) {
//                Point2f vertices[4];
//                boundRect.points(vertices);
//                for (int i = 0; i < 4; i++)
//                    line(output, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2, 8, 0);
//
//                //gövdeyi çiz
//
//
//                //rectangle(output, boundRect, Scalar(0, 255, 0), 2, 8, 0);
//
//                // imshow("Contours : ", output);
//                stringstream ss;
//                ss << imageNumPos;
//                string name = "CinaliPos40_40\\" + ss.str() + ".png";
//                ++imageNumPos;
//
//
//                vector<Vec3f> circles;
//                /// Apply the Hough Transform to find the circles
//                HoughCircles(imageGoussOut, circles, CV_HOUGH_GRADIENT, 1, imageGoussOut.rows / 8, 75, 30, 0, 0);
//
//                Point centerM;
//                int radiusM = 0;
//
//                if (circles.size() != 0) {
//                    for (size_t i = 0; i < circles.size(); i++) {
//                        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
//
//
//                        centerM.x += center.x;
//                        centerM.y += center.y;
//                        radiusM += cvRound(circles[i][2]);
//
//
//                    }
//
//                    centerM.x = centerM.x / circles.size();
//                    centerM.y = centerM.y / circles.size();
//
//                    radiusM = radiusM / circles.size();
//
//                    //center of circle
//                    circle(output, centerM, 3, Scalar(0, 255, 255), -1, 8, 0);
//                    // circle drawing for head
//                    circle(output, centerM, radiusM, Scalar(0, 255, 255), 3, 8, 0);
//
//                    // imshow("Head : ", output);
//
//                }
//                displayFotoNums(output, "Center X: ", centerM.y, Point(15, 80));
//                displayFotoNums(output, "Center Y: ", centerM.x, Point(15, 100));
//                displayFotoNums(output, "Radius: ", radiusM, Point(15, 120));
//                displayFotoNums(output, "CenterRectX: ", boundRect.center.y, Point(15, 160));
//                displayFotoNums(output, "CenterRectY: ", boundRect.center.x, Point(15, 180));
//
//                circle(output, boundRect.center, 3, Scalar(255, 0, 255), -1, 8, 0);
//
//                //draw the line to head and body
//                // line(output, boundRect.center, centerM, Scalar(255,0,0));
//
//
//
//                Point temp(0, 0);
//
//
//
//                temp.x = (int) (boundRect.center.x -
//                                (centerM.x - boundRect.center.x));
//                temp.y = (int) (boundRect.center.y - (centerM.y - boundRect.center.y));
//
//                if(circles.size() != 0){
//                    line(output, temp, boundRect.center, Scalar(255, 0, 0), 2, 8, 0);
//                }
//
//                // displayFotoNums(output,"Foto Pos : " ,imageNumPos,Point(15,60));
//                // putText(image, imageNumPos , cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,255), 1);
//                //generateHistogram(output);
//
//                displayFotoNums(output, "New Point X: ", temp.y, Point(15, 200));
//                displayFotoNums(output, "New Point Y: ", temp.x, Point(15, 220));
//
//                circle(output, temp, 3, Scalar(255, 0, 255), -1, 8, 0);
//                // imshow("Body Line ", output);
//
//            }
//
//        }
//
//    }
//    imshow("imageCont : ", output);
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
