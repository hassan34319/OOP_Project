#pragma once
#include "GUI_Renderer.h"
#include <iostream>
#include <memory>
#include <cmath>


class AirHockey
{
public:
    AirHockey();
    void startGame();
	void prepareForGame();

private:
    void botMoveStrategy();
    void calcGameState();
    void calculatePosition(Element &type);    // Pass Element by reference
    void checkBoardLimitsFor(Element &type);  // Pass Element by reference

    std::unique_ptr<GUI_Renderer> mGameUI;
    std::vector<Element *> mGameElements; // Use Element class instead of SElement
    Difficulty gameDifficulty = Difficulty(0);
    bool mGamePreparation = false;
    bool mIsPlay = false;
    bool mMute = false;

    const int FPS = 120;
    const int frameDelay = 1000 / FPS;

    unsigned int frameStart;
    int frameTime;
};
