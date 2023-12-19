#pragma once
#include "Element.h"

class Bot : public Element {
private:
    int score;

public:
    Bot(int index);

    int getScore() const;
    void setScore(int newScore);

    void someFunction() override;
};
