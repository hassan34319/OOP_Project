#pragma once
#include "GUI_Renderer.h"
#include <iostream>
#include <memory>
#include <cmath>
using namespace std;

class AirHockey
{
public:
	AirHockey();
	void startGame();

private:
	void prepareForGame();
	void botMoveStrategy();
	void calcGameState();
	void calculatePosition(ETypeOfElement type);
	void checkBoardLimitsFor(ETypeOfElement type);
	std::unique_ptr<GUI_Renderer> mGameUI;
	std::vector<SElement> mGameElements;
	EDifficulty gameDifficulty = eDifficulty_Easy;
	bool mGamePreparation = false;
	bool mIsPlay = false;
	bool mMute = false;

	const int FPS = 120;
	const int frameDelay = 1000 / FPS;

	unsigned int frameStart;
	int frameTime;


};

-----------------------------------------------------
	refracted classes

// Puck.h
#pragma once

class Puck {
public:
    Puck(double startX, double startY, double startSpeedX, double startSpeedY);
    void updatePosition();
    // Other methods and properties related to the puck...

private:
    double xCurrPos;
    double yCurrPos;
    double xSpeed;
    double ySpeed;
};


// Mallet.h
#pragma once

class Mallet {
public:
    Mallet(double startX, double startY, double startSpeedX, double startSpeedY);
    void checkBoardLimits();
    // Other methods and properties related to the mallet...

private:
    double xCurrPos;
    double yCurrPos;
    double xSpeed;
    double ySpeed;
    int score;
};

// GUIManager.h
#pragma once

enum class EEvent { /* Define your events here */ };
enum class EDifficulty { /* Define your difficulty levels here */ };

class GUIManager {
public:
    void gameMenu(EDifficulty difficulty);
    EEvent checkEvent();
    void drawGame();
    bool enableSound();
    void playClashSound(/* Pass necessary parameters here */);
    // Other GUI-related functionalities...
};


// GameManager.h
#pragma once
#include "Puck.h"
#include "Mallet.h"
#include "GUIManager.h"

class GameManager {
public:
    GameManager();
    void startGame();

private:
    void prepareForGame();
    void botMoveStrategy();
    void calcGameState();
    void calculatePosition();
    void checkBoardLimitsFor();

    GUIManager mGUIManager;
    Puck mPuck;
    Mallet mPlayerMallet;
    Mallet mBotMallet;
    EDifficulty gameDifficulty;
    bool mGamePreparation;
    bool mIsPlay;
    bool mMute;

    const int FPS;
    const int frameDelay;
    unsigned int frameStart;
    int frameTime;
};




