#pragma once

// enum ETypeOfElement {
// 	eTypeOfElement_Bot,
// 	eTypeOfElement_Player,
// 	eTypeOfElement_Puck
// };

// enum EDifficulty {
// 	eDifficulty_Easy,
// 	eDifficulty_Normal
// };

// // enum EClash {
// // 	eClash_Board,
// // 	eClash_Hit,
// // 	eClash_Goal
// // };

// enum EEvent {
// 	eEvent_NoEvent,
// 	eEvent_esc,
// 	eEvent_PrepareToPlay,
// 	eEvent_Play,
// 	eEvent_ChangeDifficulty,
// 	eEvent_Sound,
// 	eEvent_Menu
// };
class TypeOfElement
{
public:
	TypeOfElement(int index) : mIndex(index) {} // Constructor to initialize index
	int getIndex() const { return mIndex; }		// Accessor method to get the index

	static const TypeOfElement Bot;
	static const TypeOfElement Player;
	static const TypeOfElement Puck;

	bool operator==(const TypeOfElement &other) const
	{
		// Implement your custom comparison logic here
		return this == &other; // For simplicity, we're comparing memory addresses
	}

private:
	TypeOfElement() : mIndex(-1) {} // Private constructor to prevent instantiation without an index
	int mIndex;						// Index to access elements in the mGameElements vector
};

class Difficulty
{
public:
    static const Difficulty Easy;
    static const Difficulty Normal;

    // Overload the == operator
    bool operator==(const Difficulty& other) const
    {
        return this == &other; // For simplicity, we're comparing memory addresses
    }

private:
    Difficulty() {} // Private constructor to prevent instantiation
};
class Clash
{
public:
    static const Clash Board;
    static const Clash Hit;
    static const Clash Goal;

    bool operator==(const Clash& other) const
    {
        return this == &other; // Compare the addresses of the objects
    }
};

class Event
{
public:
    static const Event NoEvent;
    static const Event Esc;
    static const Event PrepareToPlay;
    static const Event Play;
    static const Event ChangeDifficulty;
    static const Event Sound;
    static const Event Menu;

    bool operator==(const Event& other) const
    {
        // Compare the indices of the events
        return this->getIndex() == other.getIndex();
    }

private:
    Event(int index) : mIndex(index) {}
    int getIndex() const { return mIndex; }

    int mIndex;
};

struct SElement {
	int score;
	double xCurrPos;
	double yCurrPos;
	double xPrevPos;
	double yPrevPos;
	double xSpeed;	
	double ySpeed; 
};


