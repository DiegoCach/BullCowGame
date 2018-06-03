#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FString = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FString GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
FBullCowGame BCGame;

// the entry point for the application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain() == true);

	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	std::cout << "Max tries: " << MaxTries << std::endl;
	constexpr int32 TIMES_REPEATING = 5;
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FString Guess = GetValidGuess();

		BullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

FString GetValidGuess()
{
	EWordStatus Status = EWordStatus::Invalid_Status;
	FString Guess = "";
	do
	{
		int32 CTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CTry << ". Write your answer: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter all lower case\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters\n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EWordStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FString Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
	return;
}
