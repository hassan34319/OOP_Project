#include "types.h"

const Event Event::NoEvent(0);
const Event Event::Esc(1);
const Event Event::PrepareToPlay(2);
const Event Event::Play(3);
const Event Event::ChangeDifficulty(4);
const Event Event::Sound(5);
const Event Event::Menu(6);

const Difficulty Difficulty::Easy;
const Difficulty Difficulty::Normal;


const TypeOfElement TypeOfElement::Bot(0);
const TypeOfElement TypeOfElement::Player(1);
const TypeOfElement TypeOfElement::Puck(2);


const Clash Clash::Board;
const Clash Clash::Hit;
const Clash Clash::Goal;
