//
// Created by Alper on 13.05.2017.
//

#include "StickmanDetector.h"

using namespace std;
StickmanDetector::StickmanDetector(int camNum) {
    VideoCapture captureMe(camNum);
    videoCapturer = captureMe;

    videoCapturer.set(CV_CAP_PROP_FRAME_WIDTH,280);
    videoCapturer.set(CV_CAP_PROP_FRAME_HEIGHT,396);

    if(!videoCapturer.isOpened()){
        cout<<"Failed to open camera"<<endl;
        exit(0);
    }

    dataNum = 0;
}
void StickmanDetector::videoCapturing() {

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

    capturer.set(CV_CAP_PROP_FRAME_WIDTH,284);
    capturer.set(CV_CAP_PROP_FRAME_HEIGHT,190);

    if(!capturer.isOpened()){
        cout<<"Failed to open camera"<<endl;
        exit(0);
    }


    while(key != 'q') {

        key = waitKey(25);

        if (counter == 0) {
            time(&start);
        }

        capturer >> image;

        imshow("IMAGE", image);


        time(&end);
        counter++;

        sec = difftime(end, start);
        fps = counter / sec;

        if (counter == (INT_MAX - 1000))
            counter = 0;

        ostringstream convert;
        if (counter > 30) {
            convert << fixed << setprecision(3) << fps;
        }

        detectTheStickMan(image);
    }

}


void StickmanDetector::displayFotoNums(Mat output, string message, double displayNum, Point place) {
    string numstr = convertDoubleToString(displayNum);
    string textRight = message + numstr;
    printTextToVideo(output,textRight, place);
}

string StickmanDetector::convertDoubleToString(double x) {
    ostringstream strs;
    strs << x;
    string str = strs.str();
    return str;
}

bool StickmanDetector::detectTheStickMan(Mat stickManFoto) {

    Mat outImage;
    Mat imageGoussOut;
    Mat output;



    stickManFoto.copyTo(output);


    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    stickManFoto.copyTo(outImage);
    cvtColor(stickManFoto, stickManFoto, COLOR_BGR2GRAY);
    GaussianBlur(stickManFoto, imageGoussOut, Size(7,7), 1.5, 1.5);
    //imshow("Gaus Result",imageGoussOut);
    Mat cannyOut;
    Canny(imageGoussOut, cannyOut, 0, 30, 3);

    //imshow("Canny Result",cannyOut);
    GaussianBlur(cannyOut, cannyOut, Size(7,7), 1.5, 1.5);

    //TODO : Change this to Morphology
    threshold(cannyOut,cannyOut,0,255,THRESH_BINARY);



    imshow("GausCanny Result",cannyOut);
    findContours(cannyOut, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    double maxArea = 0;
    for(int j = 0 ; j< contours.size() ; ++j){
        if(maxArea < contourArea(contours[j])){
            maxArea = contourArea(contours[j]);
        }
    }

    for (int i = 0; i < contours.size(); i++) {
        Scalar color = Scalar(0, 0, 255);
        if (maxArea == contourArea(contours[i])) {
            // drawContours(output, contours, i, color, 2, 8, hierarchy, 0, Point());
            double area = contourArea(contours[i]);
            RotatedRect boundRect;
            boundRect = minAreaRect(contours[i]);


            //displayFotoNums(output,"Area : " ,area,Point(20,120));
            if (area > 3000) {
                Point2f vertices[4];
                boundRect.points(vertices);
                for (int i = 0; i < 4; i++) {
                    line(output, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2, 8, 0);
                }




                //gövdeyi çiz


                //rectangle(output, boundRect, Scalar(0, 255, 0), 2, 8, 0);

                // imshow("Contours : ", output);



                vector<Vec3f> circles;
                /// Apply the Hough Transform to find the circles
                HoughCircles(imageGoussOut, circles, CV_HOUGH_GRADIENT, 1, imageGoussOut.rows / 8, 75, 30, 0, 0);

                Point centerM;
                int radiusM = 0;

                if (circles.size() != 0) {
                    for (size_t i = 0; i < circles.size(); i++) {
                        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));


                        centerM.x += center.x;
                        centerM.y += center.y;
                        radiusM += cvRound(circles[i][2]);


                    }

                    centerM.x = centerM.x / circles.size();
                    centerM.y = centerM.y / circles.size();

                    radiusM = radiusM / circles.size();

                    //center of circle
                    circle(output, centerM, 3, Scalar(0, 255, 255), -1, 8, 0);
                    // circle drawing for head
                    circle(output, centerM, radiusM, Scalar(0, 255, 255), 3, 8, 0);

                    // imshow("Head : ", output);

                }
                displayFotoNums(output, "Center X: ", centerM.y, Point(15, 80));
                displayFotoNums(output, "Center Y: ", centerM.x, Point(15, 100));
                displayFotoNums(output, "Radius: ", radiusM, Point(15, 120));
                displayFotoNums(output, "CenterRectX: ", boundRect.center.y, Point(15, 160));
                displayFotoNums(output, "CenterRectY: ", boundRect.center.x, Point(15, 180));

                circle(output, boundRect.center, 3, Scalar(255, 0, 255), -1, 8, 0);

                //draw the line to head and body
                // line(output, boundRect.center, centerM, Scalar(255,0,0));



                Point temp(0, 0);



                temp.x = (int) (boundRect.center.x -
                                (centerM.x - boundRect.center.x));
                temp.y = (int) (boundRect.center.y - (centerM.y - boundRect.center.y));

                if(circles.size() != 0){
                    line(output, temp, boundRect.center, Scalar(255, 0, 0), 2, 8, 0);
                }

                // displayFotoNums(output,"Foto Pos : " ,imageNumPos,Point(15,60));
                // putText(image, imageNumPos , cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,255), 1);
                //generateHistogram(output);

                displayFotoNums(output, "New Point X: ", temp.y, Point(15, 200));
                displayFotoNums(output, "New Point Y: ", temp.x, Point(15, 220));

                circle(output, temp, 3, Scalar(255, 0, 255), -1, 8, 0);
                // imshow("Body Line ", output);





                Point2f topLeft(centerM.x-radiusM, centerM.y-radiusM);
                circle(output,topLeft, 2, Scalar(0, 255, 255), 3, 8, 0);



               // circle(output, vertices[2], 2, Scalar(0, 255, 255), 3, 8, 0);

                theStickMan.setHeadRadius(radiusM);
                theStickMan.setHeadCenterX(centerM.y);
                theStickMan.setHeadCenterY(centerM.x);
                theStickMan.setBodyPointX(temp.y);
                theStickMan.setBodyPointY(temp.x);
                theStickMan.setRectPointX((int) topLeft.y);
                theStickMan.setRectPointY((int) topLeft.x);


                string name = "FOTO\\";
                if(circles.size() != 0 ) {
                    name += convertDoubleToString(dataNum);
                    name += ".png";
                    imwrite(name, output);
                    ++dataNum;
                    imshow("THE RESULT  : ", output);
                }
                //theStickMan.printTheStickMan();
            } else{


                theStickMan.setHeadRadius(-1);
                theStickMan.setHeadCenterX(-1);
                theStickMan.setHeadCenterY(-1);
                theStickMan.setBodyPointX(-1);
                theStickMan.setBodyPointY(-1);
                theStickMan.setRectPointX(-1);
                theStickMan.setRectPointY(-1);
            }

        }

    }
    imshow("Detect StickMan Video : ", output);
}

void StickmanDetector::captureSingleFrame() {
    Mat image;

    videoCapturer >> image;

    imshow("MyRotImage",image);
    Point2f src_center(image.cols/2.0F, image.rows/2.0F);
    Mat rot_mat = getRotationMatrix2D(src_center, 270, 1.0);
    Mat dst;
    warpAffine(image, dst, rot_mat,  image.size());

    imshow("MyRotImage",dst);


    //sadece 1. ve 3. parametreleri kurcala
    Mat cropImage = Mat (dst,Rect(35, 0, 285, 250)).clone();


    detectTheStickMan(cropImage);

}

void StickmanDetector::printTextToVideo(Mat image, String text, Point point) {
    putText(image,text, point, FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0));
}

StickManData StickmanDetector::getTheCapturedStickMan() {
    return  this->theStickMan;
}




