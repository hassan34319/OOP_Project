#pragma once
#include <iostream>

class Element {
protected:
    int mIndex;
    double xCurrPos;
    double yCurrPos;
    double xPrevPos;
    double yPrevPos;
    double xSpeed;
    double ySpeed;

public:
    Element(int index);
    int getIndex() const;

    double getXCurrPos() const;
    void setXCurrPos(double newXPos);

    double getYCurrPos() const;
    void setYCurrPos(double newYPos);

    double getXPrevPos() const;
    void setXPrevPos(double newXPrevPos);

    double getYPrevPos() const;
    void setYPrevPos(double newYPrevPos);

    double getXSpeed() const;
    void setXSpeed(double newSpeed);

    double getYSpeed() const;
    void setYSpeed(double newSpeed);

    virtual ~Element() {}
    virtual void someFunction() = 0;
};
