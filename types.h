#pragma once
#include <iostream>
// enum ETypeOfElement {
// 	eTypeOfElement_Bot,
// 	eTypeOfElement_Player,
// 	eTypeOfElement_Puck
// };

// enum EDifficulty {
// 	eDifficulty_Easy,
// 	eDifficulty_Normal
// };

enum EClash {
	eClash_Board,
	eClash_Hit,
	eClash_Goal
};

// enum EEvent {
// 	eEvent_NoEvent,
// 	eEvent_esc,
// 	eEvent_PrepareToPlay,
// 	eEvent_Play,
// 	eEvent_ChangeDifficulty,
// 	eEvent_Sound,
// 	eEvent_Menu
class Element {
protected:
    int mIndex;
    double xCurrPos;
    double yCurrPos;
    double xPrevPos;
    double yPrevPos;
    double xSpeed;
    double ySpeed;

public:
    Element(int index) : mIndex(index), xCurrPos(0), yCurrPos(0), xPrevPos(0), yPrevPos(0), xSpeed(0), ySpeed(0) {}
    int getIndex() const { return mIndex; }

    double getXCurrPos() const { return xCurrPos; }
    void setXCurrPos(double newXPos) { xCurrPos = newXPos; }

    double getYCurrPos() const { return yCurrPos; }
    void setYCurrPos(double newYPos) { yCurrPos = newYPos; }

    double getXPrevPos() const { return xPrevPos; }
    void setXPrevPos(double newXPrevPos) { xPrevPos = newXPrevPos; }

    double getYPrevPos() const { return yPrevPos; }
    void setYPrevPos(double newYPrevPos) { yPrevPos = newYPrevPos; }

    double getXSpeed() const { return xSpeed; }
    void setXSpeed(double newSpeed) { xSpeed = newSpeed; }

    double getYSpeed() const { return ySpeed; }
    void setYSpeed(double newSpeed) { ySpeed = newSpeed; }

    virtual ~Element() {}
    virtual void someFunction() = 0;
};

class Bot : public Element {
private:
    int score;

public:
    Bot(int index) : Element(index), score(0) {}

    int getScore() const { return score; }
    void setScore(int newScore) { 
        score = newScore;
        std::cout << "Bot score set to: " << score << std::endl;
     }

    void someFunction() override {
        // Implement Bot's function
    }
};

class Player : public Element {
private:
    int score;

public:
    Player(int index) : Element(index), score(0) {}

    int getScore() const { return score; }
    void setScore(int newScore) { 
        score = newScore;
        std::cout << "Player score set to: " << score << std::endl;
     }

    void someFunction() override {
        // Implement Player's function
    }
};

class Puck : public Element {
public:
    Puck(int index) : Element(index) {}

    void someFunction() override {
        // Implement Puck's function
    }
};

class Difficulty
{
public:
    bool operator==(const Difficulty& other) const
    {
        return difficulty == other.difficulty;
    }

    bool isEasy() const { 
        if(difficulty == 0) {
            return true;
        }
        return false;
     }

     Difficulty(int difficultyLevel) : difficulty(difficultyLevel) {}

private:

    int difficulty;

};
// class Clash
// {
// public:
//     static const Clash Board;
//     static const Clash Hit;
//     static const Clash Goal;

//     bool operator==(const Clash& other) const
//     {
//         return this == &other; // Compare the addresses of the objects
//     }
// };

enum class EventType {
    NoEvent,
    Esc,
    PrepareToPlay,
    Play,
    ChangeDifficulty,
    Sound,
    Menu,
    Win
};

class Event {
public:
    Event(EventType type) : eventType(type) {}

    bool operator==(const Event& other) const {
        return eventType == other.eventType;
    }

    EventType eventType;

private:
};

// struct SElement {
// 	int score;
// 	double xCurrPos;
// 	double yCurrPos;
// 	double xPrevPos;
// 	double yPrevPos;
// 	double xSpeed;	
// 	double ySpeed; 
// };