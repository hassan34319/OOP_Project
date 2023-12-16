#pragma once
#include "GUI_Renderer.h"
#include <iostream>
#include <memory>
#include <cmath>
#include "types.h"

class AirHockey
{
public:
	AirHockey();
	void startGame();

private:
	void prepareForGame();
	void botMoveStrategy();
	void calcGameState();
	void calculatePosition(const TypeOfElement &type);	 // Pass TypeOfElement by reference
	void checkBoardLimitsFor(const TypeOfElement &type); // Pass TypeOfElement by reference

	std::unique_ptr<GUI_Renderer> mGameUI;
	std::vector<SElement> mGameElements;
	Difficulty gameDifficulty = Difficulty::Easy;
	bool mGamePreparation = false;
	bool mIsPlay = false;
	bool mMute = false;

	const int FPS = 120;
	const int frameDelay = 1000 / FPS;

	unsigned int frameStart;
	int frameTime;
};