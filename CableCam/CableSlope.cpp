//
// Created by ERDI ERKMEN on 13.05.2017.
//

#include "CableSlope.h"

void CableSlope::videoCapturing() {

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


void CableSlope::printTextToVideo(Mat image, String text, Point point) {
    putText(image,text, point, FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0));
}

void CableSlope::displayFotoNums(Mat output, string message, double displayNum, Point place) {
    string numstr = convertDoubleToString(displayNum);
    string textRight = message + numstr;
    printTextToVideo(output,textRight, place);
}

string CableSlope::convertDoubleToString(double x) {
    ostringstream strs;
    strs << x;
    string str = strs.str();
    return str;
}

bool CableSlope::detectTheStickMan(Mat stickManFoto) {

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
            //displayFotoNums(output,"Area : " ,area,Point(20,120));
            if (area > 4000) {
                Point2f vertices[4];
                boundRect.points(vertices);
                for (int i = 0; i < 4; i++) {
                    line(output, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2, 8, 0);
                }

                displayFotoNums(output, "1 Point X: ", vertices[1].y, Point(15, 300));
                displayFotoNums(output, "1 Point Y: ", vertices[1].x, Point(15, 320));

                circle(output, vertices[0], 3, Scalar(0, 255, 255), -1, 8, 0);

//                circle(output, vertices[1], 3, Scalar(0, 127, 127), -1, 8, 0);
//                circle(output, vertices[3], 3, Scalar(0, 127, 127), -1, 8, 0);

                double lengthX= norm(vertices[0] - vertices[1]);
                double lengthY= norm(vertices[0] - vertices[3]);
//
                float slope=0;
                if( lengthX > lengthY ){
                    circle(output, vertices[1], 3, Scalar(0, 127, 127), -1, 8, 0);
                    if( abs(vertices[0].y - vertices[1].y) >0 )
                        slope = std::abs( (vertices[0].x - vertices[1].x ) / (vertices[0].y - vertices[1].y) );
                }
                else {
                    circle(output, vertices[3], 3, Scalar(0, 127, 127), -1, 8, 0);
                    if( abs(vertices[0].y - vertices[3].y) >0 )
                        slope = std::abs( (vertices[0].x - vertices[3].x ) / (vertices[0].y - vertices[3].y) );
                }


                displayFotoNums(output, "lengthX :", lengthX, Point(15, 340));
                displayFotoNums(output, "lengthY :", lengthY, Point(15, 360));

                if(slope > 0 && slope < 0.05)
                    displayFotoNums(output, "DIK -> slope :", slope, Point(15, 380));


//                vector<Vec3f> circles;
//                /// Apply the Hough Transform to find the circles
//                HoughCircles(imageGoussOut, circles, CV_HOUGH_GRADIENT, 1, imageGoussOut.rows / 8, 75, 30, 0, 0);

//                Point centerM;
//                int radiusM = 0;


                displayFotoNums(output, "CenterRectX: ", boundRect.center.y, Point(15, 160));
                displayFotoNums(output, "CenterRectY: ", boundRect.center.x, Point(15, 180));

//                circle(output, boundRect.center, 3, Scalar(255, 0, 255), -1, 8, 0);

                //draw the line to head and body
                // line(output, boundRect.center, centerM, Scalar(255,0,0));



                Point temp(0, 0);



//                temp.x = (int) (boundRect.center.x -
//                                (centerM.x - boundRect.center.x));
//                temp.y = (int) (boundRect.center.y - (centerM.y - boundRect.center.y));
//
//                if(circles.size() != 0){
//                    line(output, temp, boundRect.center, Scalar(255, 0, 0), 2, 8, 0);
//                }

                // displayFotoNums(output,"Foto Pos : " ,imageNumPos,Point(15,60));
                // putText(image, imageNumPos , cvPoint(30,30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,255), 1);
                //generateHistogram(output);

                displayFotoNums(output, "New Point X: ", temp.y, Point(15, 200));
                displayFotoNums(output, "New Point Y: ", temp.x, Point(15, 220));

                circle(output, temp, 3, Scalar(255, 0, 255), -1, 8, 0);
                // imshow("Body Line ", output);

            }

        }

    }
    imshow("imageCont : ", output);
}