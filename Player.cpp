#include "Player.h"

Player::Player(int index) : Element(index), score(0) {}

int Player::getScore() const {
    return score;
}

void Player::setScore(int newScore) {
    score = newScore;
    std::cout << "Player score set to: " << score << std::endl;
}

void Player::someFunction() {
    // Implement Player's function
}
