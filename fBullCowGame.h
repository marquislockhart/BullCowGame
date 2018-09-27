#pragma once
#include <string>

using int32 = int;
using fString = std::string;

struct fBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class eGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class fBullCowGame
{
public:
	fBullCowGame(); //constructor

	int32 getMaxAttempts() const;
	int32 getCurrentAttempt() const;
	int32 getHiddenWordLength() const;
	bool isGameWon() const;
	eGuessStatus checkGuess(fString) const;

	void reset();
	fBullCowCount submitValidGuess(fString);


// ^^ please try and ignore this and focus on the interface above ^^
private:
	//see constructor for initialization
	int32 myCurrentAttempt;
	fString myHiddenWord;
	bool bGameIsWon;

	bool isIsogram(fString) const;
	bool isLowercase(fString) const;
};