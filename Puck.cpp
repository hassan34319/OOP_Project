#include <iostream>

#include "Puck.hpp"

Puck::Puck(float startX, float startY)
    : positionX(startX), positionY(startY), velocityX(0.0f), velocityY(0.0f) {}

void Puck::updatePosition(float deltaTime) {
    // Update position based on velocity and deltaTime
    positionX += velocityX * deltaTime;
    positionY += velocityY * deltaTime;
}

float Puck::getPositionX() const {
    return positionX;
}

float Puck::getPositionY() const {
    return positionY;
}