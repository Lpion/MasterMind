#pragma once
#include <string>

using FString = std::string;
using int32 = int;


struct FMMGameCount {
	int32 White = 0;
	int32 Black = 0;
};


enum class EGuessStatus {
	invalid_status,
	ok,
	doubles,
	wrong_length,
	need_lowercase,
	wrong_chars
};

enum class EColors {
	red,
	green,
	blue,
	orange
};

//---------------------------------------------------------------------------------
class FMasterMind{

public:
	FMasterMind(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	FString GetHiddenWord() const;

	void Reset();
	
	//counting whites + blacks, and increasing try # assuming valid guess
	FMMGameCount SubmitValidGuess(FString);


private:
	//see constructor for init.
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsDouble(FString) const;
	bool IsLowerCase(FString) const;
};