//
// Created by Alper on 13.05.2017.
//

#include "StickManData.h"

StickManData::StickManData(int headRadiusV, int headCenterXV, int headCenterYV, int bodyPointXV, int bodyPointYV) {
    headRadius = headRadiusV;
    headCenterX = headCenterXV;
    headCenterY = headCenterYV;
    bodyPointX = bodyPointXV;
    bodyPointY = bodyPointYV;
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








