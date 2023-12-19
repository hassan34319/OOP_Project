#include "Difficulty.h"

Difficulty::Difficulty(int difficultyLevel) : difficulty(difficultyLevel) {}

bool Difficulty::operator==(const Difficulty& other) const {
    return difficulty == other.difficulty;
}

bool Difficulty::isEasy() const {
    return difficulty == 0;
}
