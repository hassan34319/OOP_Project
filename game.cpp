#include "game.h"
#include <cmath>

const int leftSideGate = (boardWidth - gateWidth) / 2;
const int rightSideGate = leftSideGate + gateWidth;
bool gameOver = false;

AirHockey::AirHockey() : mGameUI(new GUI_Renderer)
{
    mGameElements.resize(3);
}

void AirHockey::prepareForGame()
{
    // Setting the starting coordinates of the game elements
    const double xStartPosBot = (boardWidth - malletDiameter) / 2;
    const double yStartPosBot = (boardHeight - malletDiameter) / 2;
    const double xStartPosPlayer = xStartPosBot;
    const double yStartPosPlayer = yStartPosBot + yStartPosBot / 2;
    const double xStartPosPuck = xStartPosBot;
    const double yStartPosPuck = (boardWidth - puckDiameter) / 2;

    mGameElements[TypeOfElement::Bot.getIndex()] = { mGameElements[TypeOfElement::Bot.getIndex()].score, xStartPosBot, yStartPosBot / 2, xStartPosBot, yStartPosBot / 2, 0, 0 };
    mGameElements[TypeOfElement::Player.getIndex()] = { mGameElements[TypeOfElement::Player.getIndex()].score, xStartPosBot, yStartPosPlayer, xStartPosBot, yStartPosPlayer, 0, 0 };
    mGameElements[TypeOfElement::Puck.getIndex()] = { 0, yStartPosPuck, yStartPosBot, yStartPosPuck, yStartPosBot, 0, 0 };
}

void AirHockey::calculatePosition(const TypeOfElement& type)
{
    SElement& hitElem = mGameElements[type.getIndex()];
    SElement& puck = mGameElements[TypeOfElement::Puck.getIndex()];

    int impactStrength = 1 + abs(abs(hitElem.xSpeed) > abs(hitElem.ySpeed) ? hitElem.xSpeed : hitElem.ySpeed); // Impact force calculation
    double displacementX = hitElem.xSpeed / impactStrength;
    double displacementY = hitElem.ySpeed / impactStrength;

    bool doHit = false;
    while (impactStrength)
    {
        hitElem.xPrevPos += displacementX;
        hitElem.yPrevPos += displacementY;

        if (pow(malletRadius + puckRadius, 2) >= pow((hitElem.xPrevPos + malletRadius) - (puck.xCurrPos + puckRadius), 2) + pow((hitElem.yPrevPos + malletRadius) - (puck.yCurrPos + puckRadius), 2))
        {
            doHit = true;

            double hyp = hypot(hitElem.xPrevPos - puck.xCurrPos, hitElem.yPrevPos - puck.yCurrPos);
            double sin = (hitElem.yPrevPos - puck.yCurrPos) / hyp;
            double cos = (puck.xCurrPos - hitElem.xPrevPos) / hyp;
            double nSpeed = puck.xSpeed * cos - puck.ySpeed * sin;
            double tSpeed = puck.xSpeed * sin + puck.ySpeed * cos;
            nSpeed = -nSpeed;

            puck.xSpeed = tSpeed * sin + nSpeed * cos + hitElem.xSpeed;
            puck.ySpeed = tSpeed * cos - nSpeed * sin + hitElem.ySpeed;

            puck.xCurrPos += puck.xSpeed;
            puck.yCurrPos += puck.ySpeed;
        }
        --impactStrength;
    }

    if (doHit)
        mGameUI->playClashSound(Clash::Hit);
}

void AirHockey::calcGameState()
{
    SElement& puck = mGameElements[TypeOfElement::Puck.getIndex()];

    int puckMaxX = boardWidth - puckDiameter;
    int puckMaxY = boardHeight - puckDiameter;

    puck.xCurrPos += puck.xSpeed;
    puck.yCurrPos += puck.ySpeed;

    calculatePosition(TypeOfElement::Player);
    calculatePosition(TypeOfElement::Bot);

    // Collision with boards
    if (puck.xCurrPos > puckMaxX || puck.xCurrPos <= 0)
    {
        puck.xCurrPos = (puck.xCurrPos > puckMaxX ? puckMaxX * 2 - puck.xCurrPos : borderWidth - puck.xCurrPos);
        puck.xSpeed *= -1;
        mGameUI->playClashSound(Clash::Board);
    }

    // Goal
    if ((puck.xCurrPos > leftSideGate) && puck.xCurrPos < (rightSideGate - puckDiameter))
    {
        if (puck.yCurrPos > (puckMaxY + puckDiameter) || puck.yCurrPos <= -puckDiameter)
        {
            mGameUI->playClashSound(Clash::Goal);
            mGameElements[(puck.yCurrPos > puckMaxY ? TypeOfElement::Bot : TypeOfElement::Player).getIndex()].score++;

            const int maxScore = 4;

            if (mGameElements[TypeOfElement::Player.getIndex()].score == maxScore)
            {
                mIsPlay = false;
                gameOver = true;
            }

            if (mGameElements[TypeOfElement::Bot.getIndex()].score == maxScore)
            {
                mIsPlay = false;
                gameOver = true;
            }

            prepareForGame();
            return;
        }
    }
    else if (puck.yCurrPos > puckMaxY || puck.yCurrPos <= 0)
    {
        puck.yCurrPos = (puck.yCurrPos > puckMaxY ? puckMaxY * 2 - puck.yCurrPos : borderWidth - puck.yCurrPos);
        puck.ySpeed *= -1;
        mGameUI->playClashSound(Clash::Board);
    }

    puck.xSpeed *= 0.98;
    puck.ySpeed *= 0.98;
    if (abs(puck.xSpeed) < 0.7 && abs(puck.ySpeed) < 0.7)
    {
        puck.xSpeed = 0;
        puck.ySpeed = 0;
    }
}

void AirHockey::checkBoardLimitsFor(const TypeOfElement& type)
{
    SElement& bat = mGameElements[type.getIndex()];

    if (type == TypeOfElement::Player && bat.yCurrPos < boardHeight / 2)
        bat.yCurrPos = boardHeight / 2;

    if (bat.xCurrPos > boardWidth - malletDiameter - borderWidth)
    {
        mGameUI->playClashSound(Clash::Board);
        bat.xCurrPos = boardWidth - malletDiameter - borderWidth;
    }

    if (bat.xCurrPos < borderWidth)
    {
        mGameUI->playClashSound(Clash::Board);
        bat.xCurrPos = borderWidth;
    }

    if (type == TypeOfElement::Player && bat.yCurrPos > boardHeight - malletDiameter - borderWidth)
    {
        mGameUI->playClashSound(Clash::Board);
        bat.yCurrPos = boardHeight - malletDiameter - borderWidth;
    }

    if (type == TypeOfElement::Bot && bat.yCurrPos < borderWidth)
    {
        mGameUI->playClashSound(Clash::Board);
        bat.yCurrPos = borderWidth;
    }

    bat.xSpeed = bat.xCurrPos - bat.xPrevPos;
    bat.ySpeed = bat.yCurrPos - bat.yPrevPos;
}

void AirHockey::botMoveStrategy()
{
    SElement& bot = mGameElements[TypeOfElement::Bot.getIndex()];
    SElement& puck = mGameElements[TypeOfElement::Puck.getIndex()];
    double speed = (gameDifficulty == Difficulty::Normal ? MAX_SPEED / 3 : MAX_SPEED / 5);

    bot.xPrevPos = bot.xCurrPos;
    bot.yPrevPos = bot.yCurrPos;

    double preX = puck.xCurrPos + puck.xSpeed;
    double preY = puck.yCurrPos + puck.ySpeed;
    double distX = abs(preX - bot.xCurrPos);
    double distY = preY - bot.yCurrPos;

    bot.xSpeed = (speed < distX ? speed : distX) * (preX < bot.xCurrPos ? -1 : 1);
    if (preY > boardHeight / 2)
        bot.ySpeed -= (bot.yCurrPos - speed > 50 ? speed : 0);
    else if (preY < bot.yCurrPos + malletRadius)
        bot.ySpeed = -speed;
    else if (distY > distX || speed > distX - puckRadius)
        bot.ySpeed = (speed < distY ? speed : distY);
    else
        bot.ySpeed = distY / (distX / speed);

    speed *= speed;
    while (speed < pow(bot.xSpeed, 2) + pow(bot.ySpeed, 2))
    {
        bot.xSpeed *= 0.9;
        bot.ySpeed *= 0.9;
    }
    bot.xCurrPos += bot.xSpeed;
    bot.yCurrPos += bot.ySpeed;

    checkBoardLimitsFor(TypeOfElement::Bot);
}

void AirHockey::startGame()
{
    mGameUI->gameMenu(gameDifficulty);

    while (true)
    {
        frameStart = SDL_GetTicks();

        Event event = mGameUI->checkEvent(mGameElements[TypeOfElement::Player.getIndex()], mGamePreparation);
        
        if (event == Event::NoEvent)
        {
            // Handle NoEvent
        }
        else if (event == Event::Esc)
        {
            return;
        }
        else if (event == Event::PrepareToPlay)
        {
            if (!mIsPlay)
            {
                mGamePreparation = true;
            }
        }
        else if (event == Event::Play)
        {
            if (!mIsPlay)
            {
                mGamePreparation = false;
                mIsPlay = true;
            }
        }
        else if (event == Event::ChangeDifficulty)
        {
            if (!mIsPlay)
            {
                gameDifficulty = (gameDifficulty == Difficulty::Easy) ? Difficulty::Normal : Difficulty::Easy;
                mGameUI->gameMenu(gameDifficulty);
            }
        }
        else if (event == Event::Sound)
        {
            mMute = mGameUI->enableSound();
            if (!mIsPlay)
                mGameUI->gameMenu(gameDifficulty);
        }
        else if (event == Event::Menu)
        {
            if (mIsPlay) {
                mIsPlay = false;
                mGameElements[TypeOfElement::Bot.getIndex()] = { 0, 0, 0, 0, 0, 0, 0 };
                mGameElements[TypeOfElement::Player.getIndex()] = { 0, 0, 0, 0, 0, 0, 0 };
                mGameUI->gameMenu(gameDifficulty);
            }
        }
        
        if (gameOver == true)
        {
            mGameUI->gameMenu(gameDifficulty);
            mGameElements[TypeOfElement::Bot.getIndex()] = { 0, 0, 0, 0, 0, 0, 0 };
            mGameElements[TypeOfElement::Player.getIndex()] = { 0, 0, 0, 0, 0, 0, 0 };
            gameOver = false;
        }

        if (mGamePreparation && !mIsPlay) {
            prepareForGame();
            mGameUI->drawGame(mGameElements, mGamePreparation);
        }

        if (!mGamePreparation && mIsPlay) {
            botMoveStrategy();
            checkBoardLimitsFor(TypeOfElement::Player);
            calcGameState();
            mGameUI->drawGame(mGameElements, mGamePreparation);
        }

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }

        frameTime = SDL_GetTicks() - frameStart;
    }
}
