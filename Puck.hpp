#include <iostream>

class Puck {
private:
    float positionX;
    float positionY;
    float velocityX;
    float velocityY;

public:
    Puck(float startX, float startY); // Constructor
    void updatePosition(float deltaTime);
    float getPositionX() const;
    float getPositionY() const;
};