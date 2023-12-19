#include "game.h"
#include <cmath>

const int leftSideGate = (boardWidth - gateWidth) / 2;
const int rightSideGate = leftSideGate + gateWidth;
int winner =0;
bool gameOver = false;
bool winningClick = false;
int BotIndex = 0;
int PlayerIndex = 1;
int PuckIndex =2;

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

    int currentBotScore =0;
    Bot* newBot = dynamic_cast<Bot*>(mGameElements[0]);
    if (newBot != nullptr) {
    currentBotScore = newBot->getScore(); // Get current Bot score
    newBot->setScore(currentBotScore); // Set Bot's score to its current score
    delete mGameElements[0];
}

    mGameElements[0] = new Bot(0); // Index 0 for Bot
    dynamic_cast<Bot*>(mGameElements[0])->setScore(currentBotScore); // Set Bot's score to its current score // 
    mGameElements[0]->setXCurrPos((boardWidth - malletDiameter) / 2);
    mGameElements[0]->setYCurrPos((boardHeight - malletDiameter) / 2 / 2);
    mGameElements[0]->setXPrevPos((boardWidth - malletDiameter) / 2);
    mGameElements[0]->setYPrevPos((boardHeight - malletDiameter) / 2 / 2);

   
   int currentPlayerScore =0;
    Player* newPlayer = dynamic_cast<Player*>(mGameElements[1]);
    if (newPlayer != nullptr) {
    currentPlayerScore = newPlayer->getScore(); // Get current Bot score
    newPlayer->setScore(currentPlayerScore); // Set Bot's score to its current score
    delete mGameElements[1];
}
    mGameElements[1] = new Player(1); // Index 1 for Player
    dynamic_cast<Player*>(mGameElements[1])->setScore(currentPlayerScore); // Set Player's score to its current score
    // Setting Positions and speed
    mGameElements[1]->setXCurrPos((boardWidth - malletDiameter) / 2);
    mGameElements[1]->setYCurrPos((boardHeight - malletDiameter) / 2 + (boardHeight - malletDiameter) / 2 / 2);
    mGameElements[1]->setXPrevPos((boardWidth - malletDiameter) / 2);
    mGameElements[1]->setYPrevPos((boardHeight - malletDiameter) / 2 + (boardHeight - malletDiameter) / 2 / 2);


    mGameElements[2] = new Puck(2); // Index 2 for Puck
        // Setting Positions and speed
    mGameElements[2]->setXCurrPos(yStartPosPuck);
    mGameElements[2]->setYCurrPos(yStartPosBot);
    mGameElements[2]->setXPrevPos(xStartPosPuck);
    mGameElements[2]->setYPrevPos(xStartPosBot);
   
}

void AirHockey::calculatePosition(Element& type)
{
    Element* hitElem = mGameElements[type.getIndex()];
    Element* puck = mGameElements[2]; // Puck index is 2

    int impactStrength = 1 + abs(abs(hitElem->getXSpeed()) > abs(hitElem->getYSpeed()) ? hitElem->getXSpeed() : hitElem->getYSpeed()); // Impact force calculation
double displacementX = hitElem->getXSpeed() / impactStrength;
double displacementY = hitElem->getYSpeed() / impactStrength;

// Blackbox (From references)
bool doHit = false;
while (impactStrength) {
    hitElem->setXPrevPos(hitElem->getXPrevPos() + displacementX);
    hitElem->setYPrevPos(hitElem->getYPrevPos() + displacementY);
    // Calculating collitsion
    if (pow(malletRadius + puckRadius, 2) >= pow((hitElem->getXPrevPos() + malletRadius) - (puck->getXCurrPos() + puckRadius), 2) + pow((hitElem->getYPrevPos() + malletRadius) - (puck->getYCurrPos() + puckRadius), 2)) {
        doHit = true;

        double hyp = hypot(hitElem->getXPrevPos() - puck->getXCurrPos(), hitElem->getYPrevPos() - puck->getYCurrPos());
        double sin = (hitElem->getYPrevPos() - puck->getYCurrPos()) / hyp;
        double cos = (puck->getXCurrPos() - hitElem->getXPrevPos()) / hyp;
        double nSpeed = puck->getXSpeed() * cos - puck->getYSpeed() * sin;
        double tSpeed = puck->getXSpeed() * sin + puck->getYSpeed() * cos;
        nSpeed = -nSpeed;

        puck->setXSpeed(tSpeed * sin + nSpeed * cos + hitElem->getXSpeed());
        puck->setYSpeed(tSpeed * cos - nSpeed * sin + hitElem->getYSpeed());

        puck->setXCurrPos(puck->getXCurrPos() + puck->getXSpeed());
        puck->setYCurrPos(puck->getYCurrPos() + puck->getYSpeed());
    }
    --impactStrength;
}

if (doHit)
    mGameUI->playClashSound(eClash_Hit);

}



void AirHockey::calcGameState()
{
    Element* puck = mGameElements[PuckIndex];

    int puckMaxX = boardWidth - puckDiameter;
    int puckMaxY = boardHeight - puckDiameter;

    puck->setXCurrPos(puck->getXCurrPos() + puck->getXSpeed());
puck->setYCurrPos(puck->getYCurrPos() + puck->getYSpeed());

calculatePosition(*mGameElements[PlayerIndex]);
calculatePosition(*mGameElements[BotIndex]);

// Collision with boards
if (puck->getXCurrPos() > puckMaxX || puck->getXCurrPos() <= 0)
{
    // Calculate the X coordinate after the collision with the field boundary
    double newX = (puck->getXCurrPos() > puckMaxX) ? (puckMaxX * 2 - puck->getXCurrPos()) : (borderWidth - puck->getXCurrPos());
    puck->setXCurrPos(newX);

    // Reverse the X speed to reflect the collision
    puck->setXSpeed(puck->getXSpeed() * -1);

    // Handle collision with boards
    mGameUI->playClashSound(eClash_Board);
}

// Goal
if ((puck->getXCurrPos() > leftSideGate) && puck->getXCurrPos() < (rightSideGate - puckDiameter))
{
    // Handle goal
    if (puck->getYCurrPos() > (puckMaxY + puckDiameter) || puck->getYCurrPos() <= -puckDiameter)
    {
        mGameUI->playClashSound(eClash_Goal);
        // Dynamic cast the Bot Element to Bot class From Element CLass/
        if (puck->getYCurrPos() > puckMaxY && dynamic_cast<Bot*>(mGameElements[BotIndex]) != nullptr) {
    std::cout << "Bot scored!" << std::endl;
    int botScore = dynamic_cast<Bot*>(mGameElements[BotIndex])->getScore();
    dynamic_cast<Bot*>(mGameElements[BotIndex])->setScore(botScore + 1);
} else if (dynamic_cast<Player*>(mGameElements[PlayerIndex]) != nullptr) {
    std::cout << "Player scored!" << std::endl;
    int playerScore = dynamic_cast<Player*>(mGameElements[PlayerIndex])->getScore();
    dynamic_cast<Player*>(mGameElements[PlayerIndex])->setScore(playerScore + 1);
}
        // Edit score from here
        const int maxScore = 4;
        // If max score reached
        if (dynamic_cast<Player*>(mGameElements[PlayerIndex])->getScore() == maxScore || dynamic_cast<Bot*>(mGameElements[BotIndex])->getScore() == maxScore)
        {
            mIsPlay = false;
            gameOver = true;
        }

        prepareForGame();
        return;
    }
}
else if (puck->getYCurrPos() > puckMaxY || puck->getYCurrPos() <= 0)
{
    double newY = (puck->getYCurrPos() > puckMaxY) ? (puckMaxY * 2 - puck->getYCurrPos()) : (borderWidth - puck->getYCurrPos());
    puck->setYCurrPos(newY);

// Reverse the Y speed to reflect the collision
    puck->setYSpeed(puck->getYSpeed() * -1);

// Handle collision with boards
    mGameUI->playClashSound(eClash_Board);
}

puck->setXSpeed(puck->getXSpeed() * 0.98);
puck->setYSpeed(puck->getYSpeed() * 0.98);
if (std::abs(puck->getXSpeed()) < 0.7 && std::abs(puck->getYSpeed()) < 0.7)
{
    puck->setXSpeed(0);
    puck->setYSpeed(0);
}
}

void AirHockey::checkBoardLimitsFor(Element &type)
{
    int boardHeightHalf = boardHeight / 2;
    double malletDiameterWithBorder = malletDiameter + borderWidth;
    // After score
    if (type.getIndex() == PlayerIndex && type.getYCurrPos() < boardHeightHalf)
        type.setYCurrPos(boardHeightHalf);
    // Handle collision sound and position after collisions
    if (type.getXCurrPos() > boardWidth - malletDiameterWithBorder)
    {
        mGameUI->playClashSound(eClash_Board);
        type.setXCurrPos(boardWidth - malletDiameterWithBorder);
    }

    if (type.getXCurrPos() < borderWidth)
    {
        mGameUI->playClashSound(eClash_Board);
        type.setXCurrPos(borderWidth);
    }

    if (type.getIndex() == PlayerIndex && type.getYCurrPos() > boardHeight - malletDiameterWithBorder)
    {
        mGameUI->playClashSound(eClash_Board);
        type.setYCurrPos(boardHeight - malletDiameterWithBorder);
    }

    if (type.getIndex() == BotIndex && type.getYCurrPos() < borderWidth)
    {
        mGameUI->playClashSound(eClash_Board);
        type.setYCurrPos(borderWidth);
    }

    type.setXSpeed(type.getXCurrPos() - type.getXPrevPos());
    type.setYSpeed(type.getYCurrPos() - type.getYPrevPos());
}

void AirHockey::botMoveStrategy()
// Blackbox AI
{
    Element* bot = mGameElements[BotIndex];
    Element* puck = mGameElements[PuckIndex];
    double speed = (gameDifficulty.isEasy()) ? MAX_SPEED / 5 : MAX_SPEED / 3;

    bot->setXPrevPos(bot->getXCurrPos());
    bot->setYPrevPos(bot->getYCurrPos());
    
    double preX = puck->getXCurrPos() + puck->getXSpeed();
    double preY = puck->getYCurrPos() + puck->getYSpeed();
    double distX = std::abs(preX - bot->getXCurrPos());
    double distY = preY - bot->getYCurrPos();

    bot->setXSpeed(((speed < distX) ? speed : distX) * ((preX < bot->getXCurrPos()) ? -1 : 1));
    if (preY > boardHeight / 2)
        bot->setYSpeed((bot->getYCurrPos() - speed > 50) ? -speed : 0);
    else if (preY < bot->getYCurrPos() + malletRadius)
        bot->setYSpeed(-speed);
    else if (distY > distX || speed > distX - puckRadius)
        bot->setYSpeed((speed < distY) ? speed : distY);
    else
        bot->setYSpeed(distY / (distX / speed));

    speed *= speed;
    while (speed < pow(bot->getXSpeed(), 2) + pow(bot->getYSpeed(), 2))
    {
        // Reduce speed deaccerate when moving
        bot->setXSpeed(bot->getXSpeed() * 0.9);
        bot->setYSpeed(bot->getYSpeed() * 0.9);
    }
    bot->setXCurrPos(bot->getXCurrPos() + bot->getXSpeed());
    bot->setYCurrPos(bot->getYCurrPos() + bot->getYSpeed());

    checkBoardLimitsFor(*mGameElements[BotIndex]);
}


void AirHockey::startGame()
{
    mGameUI->gameMenu(gameDifficulty);

    while (true)
    {
        frameStart = SDL_GetTicks();
        // Check for user events
        Event event = mGameUI->checkEvent(*mGameElements[PlayerIndex], mGamePreparation, mIsPlay, gameOver);

        switch (event.eventType)
        {
            default:
            case EventType::NoEvent:
                break;
        // Quit
            case EventType::Esc:
                return;
        // Prepare
            case EventType::PrepareToPlay:
                if (!mIsPlay)
                {
                    mGamePreparation = true;
                }
                break;
            // Win/Lose
            case EventType::Win:
                winningClick = true;
                break;
            // Play screen
            case EventType::Play:
                if (!mIsPlay)
                {
                    mGamePreparation = false;
                    mIsPlay = true;
                }
                break;
            // Difficult changed
            case EventType::ChangeDifficulty:
                if (!mIsPlay)
                {
                    gameDifficulty = (gameDifficulty.isEasy()) ? Difficulty(1) : Difficulty(0);
                    mGameUI->gameMenu(gameDifficulty);
                }
                break;
            // speaker
            case EventType::Sound:
                mMute = mGameUI->enableSound();
                if (!mIsPlay)
                    mGameUI->gameMenu(gameDifficulty);
                break;
            // Main menu
            case EventType::Menu:
                if (mIsPlay)
                {
                    mIsPlay = false;
                    delete mGameElements[BotIndex];
                    delete mGameElements[PlayerIndex];
                    mGameElements[BotIndex] = new Bot(BotIndex);
                    mGameElements[PlayerIndex] = new Player(PlayerIndex);
                    mGameUI->gameMenu(gameDifficulty);
                }
                break;
        }   
        // Handle win and lose screen
        if (gameOver && !winningClick)
        {
            int winnerIndex = (dynamic_cast<Player*>(mGameElements[PlayerIndex]))->getScore() >
                                (dynamic_cast<Bot*>(mGameElements[BotIndex]))->getScore() ? PlayerIndex : BotIndex;

            mGameUI->gameEnd(winnerIndex);
        }
        // Back to main screen. Dynamic memory released
        if (gameOver && winningClick)
        {
           mGameUI->gameMenu(gameDifficulty);
            delete mGameElements[BotIndex];
            delete mGameElements[PlayerIndex];
            mGameElements[BotIndex] = new Bot(BotIndex);
            mGameElements[PlayerIndex] = new Player(PlayerIndex);
            gameOver = false;
            winningClick = false;
        }
    // Start game
        if (mGamePreparation && !mIsPlay)
        {
            prepareForGame();
            mGameUI->drawGame(mGameElements, mGamePreparation);
        }
        // In game
        if (!mGamePreparation && mIsPlay)
        {
            botMoveStrategy();
            checkBoardLimitsFor(*mGameElements[PlayerIndex]);
            calcGameState();
            mGameUI->drawGame(mGameElements, mGamePreparation);
        }

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
