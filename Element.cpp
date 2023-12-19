#include "Element.h"

Element::Element(int index)
    : mIndex(index), xCurrPos(0), yCurrPos(0), xPrevPos(0), yPrevPos(0), xSpeed(0), ySpeed(0) {}

int Element::getIndex() const {
    return mIndex;
}

double Element::getXCurrPos() const {
    return xCurrPos;
}

void Element::setXCurrPos(double newXPos) {
    xCurrPos = newXPos;
}

double Element::getYCurrPos() const {
    return yCurrPos;
}

void Element::setYCurrPos(double newYPos) {
    yCurrPos = newYPos;
}

double Element::getXPrevPos() const {
    return xPrevPos;
}

void Element::setXPrevPos(double newXPrevPos) {
    xPrevPos = newXPrevPos;
}

double Element::getYPrevPos() const {
    return yPrevPos;
}

void Element::setYPrevPos(double newYPrevPos) {
    yPrevPos = newYPrevPos;
}

double Element::getXSpeed() const {
    return xSpeed;
}

void Element::setXSpeed(double newSpeed) {
    xSpeed = newSpeed;
}

double Element::getYSpeed() const {
    return ySpeed;
}

void Element::setYSpeed(double newSpeed) {
    ySpeed = newSpeed;
}
