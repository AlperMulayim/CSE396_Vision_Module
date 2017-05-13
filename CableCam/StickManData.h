//
// Created by Alper on 13.05.2017.
//



class StickManData {
private:
    int headRadius;
    int headCenterX;
    int headCenterY;
    int bodyPointX;
    int bodyPointY;

public:
    StickManData(int headRadiusV, int headCenterXV, int headCenterYV, int bodyPointXV, int bodyPointYV);

    int getHeadRadius() const;

    void setHeadRadius(int headRadius);

    int getHeadCenterX() const;

    void setHeadCenterX(int headCenterX);

    int getHeadCenterY() const;

    void setHeadCenterY(int headCenterY);

    int getBodyPointX() const;

    void setBodyPointX(int bodyPointX);

    int getBodyPointY() const;

    void setBodyPointY(int bodyPointY);


};




