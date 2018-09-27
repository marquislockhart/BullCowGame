#pragma once

#include "fBullCowGame.h"
#include <map>

#define TMap std::map
using int32 = int;

fBullCowGame::fBullCowGame() { reset(); } //default constructor

int32 fBullCowGame::getCurrentAttempt() const { return myCurrentAttempt; }
int32 fBullCowGame::getHiddenWordLength() const { return myHiddenWord.length(); }
bool fBullCowGame::isGameWon() const { return bGameIsWon; }

int32 fBullCowGame::getMaxAttempts() const 
{ 
	TMap<int32, int32> wordLengthToMaxAttempts{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return wordLengthToMaxAttempts[myHiddenWord.length()];
}

void fBullCowGame::reset()
{
	const fString HIDDEN_WORD = "plane"; // MUST be an isogram
	myHiddenWord = HIDDEN_WORD;

	myCurrentAttempt = 1;
	bGameIsWon = false;
	return;
}

eGuessStatus fBullCowGame::checkGuess(fString Guess) const
{
	if (!isIsogram(Guess))
	{
		return eGuessStatus::Not_Isogram;
	}
	else if (!isLowercase(Guess))
	{
		return eGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != getHiddenWordLength())
	{
		return eGuessStatus::Wrong_Length;
	}
	else
	{
		return eGuessStatus::OK;
	}
}

fBullCowCount fBullCowGame::submitValidGuess(fString Guess)
{
	myCurrentAttempt++;
	fBullCowCount bullCowCount;
	int32 wordLength = myHiddenWord.length(); // asssuming same length as guess

	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < wordLength; MHWChar++) {
		//compare letters against the guess
		for (int32 GChar = 0; GChar < wordLength; GChar++) {
			//if they match then
			if (Guess[GChar] == myHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { //if they're in the same place
					bullCowCount.Bulls++; //increment bulls
				}
				else {
					bullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	bGameIsWon = (bullCowCount.Bulls == wordLength);
	return bullCowCount;
}

bool fBullCowGame::isIsogram(fString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> letterSeen;
	for (auto letter : Word)
	{
			letter = tolower(letter);
			if (letterSeen[letter]) {
					return false;
			}
			else {
				letterSeen[letter] = true;
			} 
		}
	return true;
}

bool fBullCowGame::isLowercase(fString Word) const
{
	for (auto letter : Word)
	{
		if (!islower(letter))
		{
			return false;
		}
	}
	return true;
}

