#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_TTF.h>
#include <SDL_mixer.h>

#include <iostream>
#include <vector>
#include <string>
#include "Element.h"
#include "Bot.h"
#include "Player.h"
#include "Puck.h"
#include "Difficulty.h"
#include "Event.h"
#include "EventType.h"
#include "Clash.h"


const int boardWidth = 450;
const int boardHeight = 840;
const int malletDiameter = 50;
const int speakerDiameter = 40;
const int puckDiameter = 40;
const int malletRadius = 25;
const int puckRadius = 20;
const int gateWidth = 170;
const int borderWidth = 5;

#define MAX_SPEED puckDiameter / 2

class GUI_Renderer
{
public:
    GUI_Renderer();
    ~GUI_Renderer();

    void gameMenu(Difficulty inDifficulty);
    void gameEnd(int result);
    Event checkEvent(Element& inStriker, bool gamePreparation, bool isPlay,  bool gameOver) const;
    void drawGame(const std::vector<Element *>& inElements, bool gamePreparation);
    void drawGameElement(SDL_Rect& inGameElement, SDL_Texture* texture, const Element& inElement, const int& diameter);
    void drawScore(SDL_Rect& inGameElement, const std::vector<Element *>& inElements);
    bool enableSound();
    void playClashSound(EClash s);
    void printMsg(std::string msg);

private:
    void loadFont();
    void loadImages();
    void loadSounds();
    void drawSpeaker();

    bool soundOn = true;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SDL_Surface* mTTF;
    SDL_Surface* mTtf;
    SDL_Texture* mGameField;
    SDL_Texture* mDifficultyEasy;
    SDL_Texture* mDifficultyNormal;
    SDL_Texture* mWin;
    SDL_Texture* mLost;
    SDL_Texture* mMalletPlayer;
    SDL_Texture* mMalletBot;
    SDL_Texture* mPuck;
    SDL_Texture* mGameScore;
    SDL_Texture* mMsg;
    SDL_Texture* mSpeakerOn;
    SDL_Texture* mSpeakerOff;

    SDL_Rect Src;

    TTF_Font* mFont;

    Mix_Music* mSound;
    Mix_Chunk* mBoard, * mHit, * mGoal;
};