#include "GUI_Renderer.h"
#include <string>

//------------------------------------------------------------------------------
static const int sizeOfSRC_Rect = 550;

static const SDL_Color cColorRed = { 255, 0, 0 };
static const SDL_Color cColorBlue = { 0, 0, 255 };
static const SDL_Color cColorGreen = { 0, 128, 0 };
static const int fontScoreH = 40;
static const int fontScoreW = 20;
static const int fontMsgH = 50;
static const int fontMsgW = 200;

//==============================================================================
GUI_Renderer::GUI_Renderer()
{
    mWindow = SDL_CreateWindow("Air Hockey", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, boardWidth, boardHeight, SDL_WINDOW_SHOWN);
    if (!mWindow)
    {
        std::cerr << "SDL error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        std::cerr << "SDL error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    loadFont();
    loadImages();
    loadSounds();

    Src = { 0, 0, sizeOfSRC_Rect, sizeOfSRC_Rect };
}
// Destructor destoys all sdl structures
GUI_Renderer::~GUI_Renderer()
{
    SDL_DestroyTexture(mGameField);
    SDL_DestroyTexture(mDifficultyEasy);
    SDL_DestroyTexture(mDifficultyNormal);
    SDL_DestroyTexture(mMalletPlayer);
    SDL_DestroyTexture(mMalletBot);
    SDL_DestroyTexture(mPuck);
    SDL_DestroyTexture(mGameScore);
    SDL_DestroyTexture(mSpeakerOn);
    SDL_DestroyTexture(mSpeakerOff);
    TTF_CloseFont(mFont);
    Mix_FreeMusic(mSound);
    Mix_FreeChunk(mBoard);
    Mix_FreeChunk(mHit);
    Mix_FreeChunk(mGoal);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

//------------------------------------------------------------------------------
void GUI_Renderer::loadFont()
{
    if (TTF_Init() < 0)
    {
        std::cerr << "TTF error: " << TTF_GetError() << std::endl;
        exit(3);
    }

    mFont = TTF_OpenFont("assets/ArialBlack.ttf", 45);

    if (!mFont)
    {
        std::cerr << "TTF error: " << TTF_GetError() << std::endl;
        exit(3);
    }
}

void GUI_Renderer::loadImages()
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) || !(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
    {
        std::cerr << "IMG error: " << IMG_GetError() << std::endl;
        exit(2);
    }

    mPuck = IMG_LoadTexture(mRenderer, "assets/puckMain.png");
    if (!mPuck)
    {
        std::cerr << "IMG error: " << IMG_GetError() << std::endl;
        exit(2);
    }
    mMalletPlayer = IMG_LoadTexture(mRenderer, "assets/Mallet.png");
    if (!mMalletPlayer)
    {
        std::cerr << "IMG error: " << IMG_GetError() << std::endl;
        exit(2);
    }
    mMalletBot = IMG_LoadTexture(mRenderer, "assets/MalletBot.png");
    if (!mMalletBot)
    {
        std::cerr << "IMG error: " << IMG_GetError() << std::endl;
        exit(2);
    }

    mSpeakerOn = IMG_LoadTexture(mRenderer, "assets/on.png");
    if (!mSpeakerOn)
    {
        std::cerr << "IMG error: " << IMG_GetError() << std::endl;
        exit(2);
    }

    mSpeakerOff = IMG_LoadTexture(mRenderer, "assets/mute.png");
    if (!mSpeakerOff)
    {
        std::cerr << "IMG error: " << IMG_GetError() << std::endl;
        exit(2);
    }

    mGameField = IMG_LoadTexture(mRenderer, "assets/bg.png");
    if (!mGameField)
    {
        std::cerr << "IMG error: " << IMG_GetError() << std::endl;
        exit(2);
    }

    mDifficultyEasy  = IMG_LoadTexture(mRenderer,"assets/start1.png");
    if (!mDifficultyEasy)
    {
        std::cerr << "IMG error: " << IMG_GetError() << std::endl;
        exit(2);
    }

    mDifficultyNormal = IMG_LoadTexture(mRenderer, "assets/start2.png");
    if (!mDifficultyNormal)
    {
        std::cerr << "IMG error: " << IMG_GetError() << std::endl;
        exit(2);
    }
    mWin = IMG_LoadTexture(mRenderer, "assets/lose_latest.jpg");
	if (!mWin)
	{
		std::cerr << "IMG error: " << IMG_GetError() << std::endl;
		exit(2);
	}
	mLost = IMG_LoadTexture(mRenderer, "assets/win_latest.jpg");
	if (!mLost)
	{
		std::cerr << "IMG error: " << IMG_GetError() << std::endl;
		exit(2);
	}
}

void GUI_Renderer::loadSounds()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096))
    {
        std::cerr << "MIX error: " << Mix_GetError() << std::endl;
        exit(4);
    }

    mSound = Mix_LoadMUS("assets/music.mp3");
    if (!mSound)
    {
        std::cerr << "MIX error: " << Mix_GetError() << std::endl;
        exit(4);
    }
    mBoard = Mix_LoadWAV("assets/hitBoard.wav");
    if (!mBoard)
    {
        std::cerr << "MIX error: " << Mix_GetError() << std::endl;
        exit(4);
    }
    mHit = Mix_LoadWAV("assets/hitPuck.wav");
    if (!mHit)
    {
        std::cerr << "MIX error: " << Mix_GetError() << std::endl;
        exit(4);
    }
    mGoal = Mix_LoadWAV("assets/goal.wav");
    if (!mGoal)
    {
        std::cerr << "MIX error: " << Mix_GetError() << std::endl;
        exit(4);
    }
    Mix_PlayMusic(mSound, -1);
}

Event GUI_Renderer::checkEvent(Element& inMallet, bool gamePreparation, bool isPlay, bool gameOver) const
{
    SDL_Event event;

    if (!SDL_PollEvent(&event))
        return Event(EventType::NoEvent);

    switch (event.type)
    {
    case SDL_QUIT:
        return Event(EventType::Esc);


    case SDL_KEYDOWN:
    // Handling M and Escape
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            return Event(EventType::Menu);
        case SDLK_m:
            return Event(EventType::Sound);
        }
        break;

    case SDL_MOUSEMOTION:
    // Handling player movement
    if (isPlay) {
            inMallet.setXPrevPos(inMallet.getXCurrPos());
            inMallet.setYPrevPos(inMallet.getYCurrPos());
            inMallet.setXCurrPos(event.motion.x - malletRadius);
            inMallet.setYCurrPos(event.motion.y - malletRadius);
            break;
    }

// Handling Mouse Clicks
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (gameOver)
                return Event(EventType::Win);

            if ((event.button.x > 55) && (event.button.x < 395) &&
                (event.button.y > 300) && (event.button.y < 400))
                return Event(EventType::PrepareToPlay);

            if ((event.button.x > 131) && (event.button.x < 304) &&
                (event.button.y > 457) && (event.button.y < 616) && !gamePreparation)
                return Event(EventType::ChangeDifficulty);

            if ((event.button.y > (boardHeight * 0.75 - puckRadius)) && (event.button.y < (boardHeight * 0.75 + puckRadius)) &&
                (event.button.x > (boardWidth / 2 - puckRadius)) && (event.button.x < (boardWidth / 2 + puckRadius)) && gamePreparation)
            {
                return Event(EventType::Play);
            }

            if (event.button.y > boardHeight - speakerDiameter - borderWidth &&
                event.button.x < speakerDiameter + borderWidth)
                return Event(EventType::Sound);
        }
        if (event.button.button == SDL_BUTTON_RIGHT)
            return Event(EventType::Menu);
        break;

    default:
        break;
    }

    return Event(EventType::NoEvent);
}


void GUI_Renderer::drawGame(const std::vector<Element *>& inElements, bool gamePreparation)
{
    SDL_RenderClear(mRenderer);
    SDL_RenderCopy(mRenderer, mGameField, nullptr, nullptr);
    SDL_Rect gameElement;

    // Draw Score
    drawScore(gameElement, inElements);

    if (gamePreparation)
    {
        
        printMsg("Please, take your mallet");
    }
    // Draw Puck
    drawGameElement(gameElement, mPuck, *(inElements[2]), puckDiameter); //  Puck is at index 0
    // Draw Bot
    drawGameElement(gameElement, mMalletBot, *(inElements[0]), malletDiameter); // Bot is at index 1
    // Draw Player
    drawGameElement(gameElement, mMalletPlayer, *(inElements[1]), malletDiameter); //  Player is at index 2
    // Draw SoundOn/SoundOff button
    drawSpeaker();

    SDL_RenderPresent(mRenderer);
}

void GUI_Renderer::drawGameElement(SDL_Rect& inGameElement, SDL_Texture* texture, const Element& inElement, const int& diameter)
{
    inGameElement.h = inGameElement.w = diameter;
    inGameElement.x = inElement.getXCurrPos();
    inGameElement.y = inElement.getYCurrPos();
    SDL_RenderCopy(mRenderer, texture, nullptr, &inGameElement);
}

void GUI_Renderer::drawScore(SDL_Rect& inGameElement, const std::vector<Element*>& inElements)
{
    inGameElement.x = boardWidth - fontScoreW * 2;
    inGameElement.h = fontScoreH;
    inGameElement.w = fontScoreW;

    // Draw current score for Bot
    inGameElement.y = boardHeight / 2 - fontScoreH;
    SDL_Color mColScoreBot = (dynamic_cast<Bot*>(inElements[0])->getScore() >= dynamic_cast<Player*>(inElements[1])->getScore()) ? cColorRed : cColorBlue;


    mTTF = TTF_RenderText_Solid(mFont, std::to_string(dynamic_cast<Bot*>(inElements[0])->getScore()).c_str(), mColScoreBot);
    mGameScore = SDL_CreateTextureFromSurface(mRenderer, mTTF);
    SDL_RenderCopy(mRenderer, mGameScore, nullptr, &inGameElement);
    SDL_FreeSurface(mTTF);
    SDL_DestroyTexture(mGameScore);

    // Draw current score for Player &Bot using dynamic casting to get Player
    inGameElement.y = boardHeight / 2;
    SDL_Color mColScorePlayer = (dynamic_cast<Player*>(inElements[1])->getScore() > dynamic_cast<Bot*>(inElements[0])->getScore() ? cColorRed : cColorBlue); // Assuming Bot and Player are at indices 1 and 2
    mTTF = TTF_RenderText_Solid(mFont, std::to_string(dynamic_cast<Player*>(inElements[1])->getScore()).c_str(), mColScorePlayer);
    mGameScore = SDL_CreateTextureFromSurface(mRenderer, mTTF);
    SDL_RenderCopy(mRenderer, mGameScore, nullptr, &inGameElement);
    SDL_FreeSurface(mTTF);
    SDL_DestroyTexture(mGameScore);
}


void GUI_Renderer::gameMenu(Difficulty difficulty)
{
    SDL_RenderClear(mRenderer);

    if (difficulty.isEasy()) {
        SDL_RenderCopy(mRenderer, mDifficultyEasy, NULL, NULL);
    }
    else { // Assuming there are only two difficulties: Easy and Normal
        SDL_RenderCopy(mRenderer, mDifficultyNormal, NULL, NULL);
    }
    
    drawSpeaker();
    SDL_RenderPresent(mRenderer);
}


void GUI_Renderer::gameEnd(int result)
{
	SDL_RenderClear(mRenderer);
	// Player won
	if (result == 0) {
		SDL_RenderCopy(mRenderer, mWin, NULL, NULL);
	}
	else {
		SDL_RenderCopy(mRenderer, mLost, NULL, NULL);
	}
	SDL_RenderPresent(mRenderer);
}

bool GUI_Renderer::enableSound()
{
    soundOn = !soundOn;
    if (soundOn)
        Mix_ResumeMusic();
    else
        Mix_PauseMusic();
    return soundOn;
}

void GUI_Renderer::drawSpeaker()
{
    if (soundOn) {
        SDL_Rect mDst{ borderWidth, boardHeight - speakerDiameter - borderWidth, speakerDiameter, speakerDiameter };
        SDL_RenderCopy(mRenderer, mSpeakerOn, &Src, &mDst);
    }
    else {
        SDL_Rect mDst{ borderWidth, boardHeight - speakerDiameter - borderWidth, speakerDiameter, speakerDiameter };
        SDL_RenderCopy(mRenderer, mSpeakerOff, &Src, &mDst);
    }
}

void GUI_Renderer::printMsg(std::string msg)
{
    SDL_Rect Msg;
    Msg.x = 140;
    Msg.y = 500;
    Msg.h = fontMsgH;
    Msg.w = fontMsgW;

    const char* cMsg = msg.c_str();
    SDL_Color mColMsg = cColorGreen;
    mTtf = TTF_RenderText_Solid(mFont, cMsg, mColMsg);
    mMsg = SDL_CreateTextureFromSurface(mRenderer, mTtf);
    SDL_RenderCopy(mRenderer, mMsg, 0, &Msg);
    SDL_FreeSurface(mTtf);
    SDL_DestroyTexture(mMsg);
}

void GUI_Renderer::playClashSound(EClash sound)
{
    if (!soundOn)
        return;

    if (sound == eClash_Board)
        Mix_PlayChannel(-1, mBoard, 0);
    else if (sound == eClash_Hit)
        Mix_PlayChannel(-1, mHit, 0);
    else {
        Mix_PlayChannel(-1, mGoal, 0);
        SDL_Delay(300); // pause 0.3s before a new round
    }
}
