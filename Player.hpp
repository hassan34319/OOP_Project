#include <iostream>

class Player {
private:
    float positionX;
    float positionY;
    int score;

public:
    Player(float startX, float startY); // Constructor
    void move(float deltaX, float deltaY);
    void increaseScore();
    float getPositionX() const;
    float getPositionY() const;
    int getScore() const;
};