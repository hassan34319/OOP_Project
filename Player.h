#pragma once
#include "Element.h"

class Player : public Element {
private:
    int score;

public:
    Player(int index);

    int getScore() const;
    void setScore(int newScore);

    void someFunction() override;
};
