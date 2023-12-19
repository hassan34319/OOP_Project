#include "Bot.h"

Bot::Bot(int index) : Element(index), score(0) {}

int Bot::getScore() const {
    return score;
}

void Bot::setScore(int newScore) {
    score = newScore;
    std::cout << "Bot score set to: " << score << std::endl;
}

void Bot::someFunction() {
    // Implement Bot's function
}
