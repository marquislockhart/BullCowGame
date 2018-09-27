/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the fBullCowGame class */

#pragma once

#include <iostream>
#include <string>
#include "fBullCowGame.h"

using fText = std::string;
using int32 = int;

void printIntro();
void playGame();
fText getValidGuess();
bool playAgain();
void printGameSummary();

fBullCowGame BCGame; //instantiate a new game

//entry point for the application
int main()
{
	bool wantsToPlayAgain = false;
	do
	{
		printIntro();
		playGame();
		wantsToPlayAgain = playAgain();
	} 
	while (wantsToPlayAgain);

	return 0; // exit the application
}


void printIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.getHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void playGame()
{
	BCGame.reset();
	int32 maxAttempts = BCGame.getMaxAttempts();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.isGameWon() && BCGame.getCurrentAttempt() <= maxAttempts) {
		fText Guess = getValidGuess();

		// submit valid guess to the game, and recieve counts
		fBullCowCount BullCowCount = BCGame.submitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}

	printGameSummary();
	return;
}

fText getValidGuess() 
{
	fText Guess = "";
	eGuessStatus status = eGuessStatus::Invalid_Status;
	do {
		//gets a guess from the player
		int32 currentAttempt = BCGame.getCurrentAttempt();
		std::cout << "Attempt " << currentAttempt << " of " << BCGame.getMaxAttempts();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		status = BCGame.checkGuess(Guess);
		switch (status)
		{
		case eGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word.\n\n";
			break;
		case eGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case eGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume guess is valid
			break;
		}
	} while (status != eGuessStatus::OK); //continue looping until no errors
	return Guess;
}

bool playAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n)? ";
	fText response = "";
	std::getline(std::cin, response);

	return (response[0] == 'y') || (response[0] == 'Y');

}

void printGameSummary()
{
	if (BCGame.isGameWon())
	{
		std::cout << "WELL DONE - YOU WIN! \n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
