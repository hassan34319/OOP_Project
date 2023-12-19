#pragma once

class Difficulty {
public:
    bool operator==(const Difficulty& other) const;

    bool isEasy() const;
    Difficulty(int difficultyLevel);

private:
    int difficulty;
};
