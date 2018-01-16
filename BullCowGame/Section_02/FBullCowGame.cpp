#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRY = 8;
	MyMaxTries = MAX_TRY;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;

	bGameWon = false;
	
	return;
}

int32 FBullCowGame::GetMaxTries() const{ return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (IsIsogram(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	// increment the turn number
	MyCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop throuhg all letters in the guess
	for (int32 i = 0; i < WordLength; i++)
	{
		// compare letter against the hidden wordl
		for (int32 j = 0; j < WordLength; j++) 
		{
			if ((MyHiddenWord[i] | ' ') == (Guess[j] | ' ')) 
			{
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
		// incriment bulls if they're in the same place
		// increment cows if not
	}
	if (BullCowCount.Bulls == WordLength)
		bGameWon = true;
	else
		bGameWon = false;
	return BullCowCount;
}

// Private Functions 

bool FBullCowGame::IsIsogram(FString Guess) const
{
	// treat 0 and 1 letter strings as isograms
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	// range based loop
	for (auto Letter : Guess) // for all letters of  the word
	{
		Letter = tolower(Letter); // handle mixed cases
		if (LetterSeen[Letter]){
			return false;
		} else {
			LetterSeen[Letter] = true;
		}
	}
	return false;
}
