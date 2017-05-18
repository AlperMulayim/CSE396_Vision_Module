//
// Created by Alper on 13.05.2017.
//

#include <iostream>
#include "StickManData.h"



StickManData::StickManData(int headRadiusV, int headCenterXV, int headCenterYV, int bodyPointXV, int bodyPointYV, int rectPointXV,
                           int rectPointYV) {
    headRadius = headRadiusV;
    headCenterX = headCenterXV;
    headCenterY = headCenterYV;
    bodyPointX = bodyPointXV;
    bodyPointY = bodyPointYV;
}

StickManData::StickManData() {
    headRadius = -1;
    headCenterX = -1;
    headCenterY = -1;
    bodyPointX = -1;
    bodyPointY = -1;
}

int StickManData::getHeadRadius() const {
    return this->headRadius;
}

void StickManData::setHeadRadius(int headRadius) {
    this->headRadius = headRadius;
}

int StickManData::getHeadCenterX() const {
    return  this->headCenterX;
}

void StickManData::setHeadCenterX(int headCenterX) {
    this->headCenterX = headCenterX;
}

int StickManData::getHeadCenterY() const {
    return this->headCenterY;
}

void StickManData::setHeadCenterY(int headCenterY) {
    this->headCenterY = headCenterY;
}

int StickManData::getBodyPointX() const {
    return this->bodyPointX;
}

void StickManData::setBodyPointX(int bodyPointX) {
    this->bodyPointX = bodyPointX;
}

int StickManData::getBodyPointY() const {
    return bodyPointY;
}

void StickManData::setBodyPointY(int bodyPointY) {
    this->bodyPointY = bodyPointY;
}

void StickManData::printTheStickMan() {
    cout<<"\nRadius : "<<getHeadRadius()<<endl;
    cout<<"HeadCenter :  ( "<<getHeadCenterX()<<" , "<<getHeadCenterY() <<" ) "<<endl;
    cout<<"Body Point : ( "<<getBodyPointX()<<" , "<<getBodyPointY()<<" ) "<<endl;
}











