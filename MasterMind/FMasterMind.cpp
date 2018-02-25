#include "FMasterMind.h"
#include <map>
#define TMap std::map


using int32 = int;

FMasterMind::FMasterMind() { Reset(); }

//Getter Methods (Functions)
int32 FMasterMind::GetMaxTries() const { return MyMaxTries; }
int32 FMasterMind::GetCurrentTry() const { return MyCurrentTry; }
int32 FMasterMind::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FMasterMind::GetHiddenWord() const { return MyHiddenWord; }
bool FMasterMind::IsGameWon() const { return bGameIsWon; }

void FMasterMind::Reset()
{
	constexpr int32 MAX_TRIES = 12;		//MAX TRIES CONSTEXPR
	const FString HIDDEN_WORD[] = { "rgbp", "rgbs", "rgbw", "bgsl", "wrol", "bpsr", "ogbw", "srgb", "rogs", "bwlg", "lors", "wblo", "rsgw", "glor", "pswr", "opwr", "wobl", "gorl", "wosp", "porb", "sgwo" };


	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD[rand() % 21];
	bGameIsWon = false;

	return;
}



EGuessStatus FMasterMind::CheckGuessValidity(FString Guess) const
{
	if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::wrong_length;
	}
	else if (!IsDouble(Guess)) 
	{
		return EGuessStatus::doubles;
	} 
	else if (!IsLowerCase(Guess)) 
	{
		return EGuessStatus::need_lowercase;
	}

	else 
	{
		return EGuessStatus::ok;
	}
}


//receives a VALID guess, increments turn, and returns counts
FMMGameCount FMasterMind::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	//setup a return variable
	FMMGameCount MMGameCount;

	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess

	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) 
				{ //if same place 
					MMGameCount.White++; //add White pin
				}
				else 
				{
					MMGameCount.Black++; //add black pin
				}
			}
		
		}
	}

	if (MMGameCount.White == WordLength) 
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return MMGameCount;
}

bool FMasterMind::IsDouble(FString Word) const
{
	//treat 0 and 1 letter words as doubles
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;	//setup map 
	for (auto Letter : Word)		//for all letters of the word
	{
		Letter = tolower(Letter);	//handle mixed case
		if (LetterSeen[Letter]) { return false; } //if letter is in the map = double
		else { LetterSeen[Letter] = true; }

	}
	return true; //zb cases \0 is entered
}

bool FMasterMind::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
	}
	return true;
}
