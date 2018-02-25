/*
This is the console exe, that makes use of the MMGame class
This acts as the view in the MVC pattern, and is responsible for all
user intereaction. For game logic see the FMMGame class.
*/

const unsigned char AE = static_cast<unsigned char>(142);
const unsigned char ae = static_cast<unsigned char>(132);
const unsigned char OE = static_cast<unsigned char>(153);
const unsigned char oe = static_cast<unsigned char>(148);
const unsigned char UE = static_cast<unsigned char>(154);
const unsigned char ue = static_cast<unsigned char>(129);
const unsigned char ss = static_cast<unsigned char>(225);


//Libaries
#include <iostream>
#include <string>
#include "FMasterMind.h"
#include "ConsoleColors.h"
#include "resource1.h"

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();


FMasterMind MMGame; //Instantiate a new game, wich will be reused across plays


//Main Function---------------------------------------------------------
int main()
{	
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	std::cout << std::endl;
	return 0;
}
//Main Function END------------------------------------------------------


void PrintIntro()
{
	std::cout << blue << std::endl;
	std::cout << " __  __    _    ____ _____ _____ ____  __  __ ___ _   _ ____  " << std::endl;
	std::cout << "|  \\/  |  / \\  / ___|_   _| ____|  _ \\|  \\/  |_ _| \\ | |  _ \\ " << std::endl;
	std::cout << "| |\\/| | / _ \\ \\___ \\ | | |  _| | |_) | |\\/| || ||  \\| | | | |" << std::endl;
	std::cout << "| |  | |/ ___ \\ ___) || | | |___|  _ <| |  | || || |\\  | |_| |" << std::endl;
	std::cout << "|_|  |_/_/   \\_|____/ |_| |_____|_| \\_|_|  |_|___|_| \\_|____/ " << std::endl;
	std::cout << white << std::endl;
	std::cout << "Kannst du die " << blue << MMGame.GetHiddenWordLength() << white << " Farben, in der richtigen Reihenfolge, erraten an die ich denke ?\n(keine Farbe doppelt) :)\n\n";
	std::cout << blue << "INFO -----------------------------------------------------------------------------\n" << white;
	std::cout << "     ERGEBNISS | verr" << ae << "t dir was du richtig hast.\n";
	std::cout << "     WEI" << ss << "      | Richtige Farbe und richtiger Platz.\n";
	std::cout << "     SCHWARZ   | Richtige Farbe und falscher Platz.\n\n";
	std::cout << "     FARBEN    | r =rot | g =gr"<<ue<<"n | b =blau | p =pink | w =wei"<<ss<<" | s =schwarz\n";
	std::cout << "               | l =lila | o = orange \n\n";
	std::cout << "     Eine g"<<ue<<"ltige Antwort w" << ae << "re z.B.: "<<green<<"rgbo \n";
	std::cout << blue << "----------------------------------------------------------------------------------";
	std::cout << white << std::endl;

	return;
}

//plays a single game to completion
void PlayGame()
{
	MMGame.Reset();

	int32 MaxTries = MMGame.GetMaxTries();
	std::cout << std::endl;

	//loop asking for guesses while game NOT won, and still tries remaining
	while(!MMGame.IsGameWon() && MMGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();


		//Submit valid guess to the game, and receive counts
		FMMGameCount MMGameCount = MMGame.SubmitValidGuess(Guess);

		//Print number of white and black pins
		std::cout << color(FOREGROUND_GREEN | FOREGROUND_BLUE) << "   ERGEBNISS | " << white;
		std::cout << "Wei" << ss << ": " << MMGameCount.White << " | ";
		std::cout << "Schwarz : " << MMGameCount.Black << "\n\n\n";
	}

	PrintGameSummary();
	return;
}

//loop until valid guess
FText GetValidGuess()
{
	FText Guess ="";
	
	EGuessStatus Status = EGuessStatus::invalid_status;
	do {
		//get a guess from player
		int32 CurrentTry = MMGame.GetCurrentTry();
		std::cout << color(FOREGROUND_GREEN | FOREGROUND_BLUE) << "Versuch " << CurrentTry << "/" << MMGame.GetMaxTries() << " | " <<white<< "Tippe deine Farben und dr" << ue << "cke ENTER: ";
		std::getline(std::cin, Guess);

		//check status and give feedback
		Status = MMGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::wrong_length:
			std::cout << red << "Die Anzahl der Farben muss " << MMGame.GetHiddenWordLength() << " sein! ;)\n\n" << white;
			break;
		case EGuessStatus::doubles:
			std::cout << red << "Bei meinen Farben gibt es keine doppelten!\n\n" << white;
			break;
		case EGuessStatus::need_lowercase:
			std::cout << red << "Alle Buchstaben m" << ue << "ssen klein geschrieben sein. zb.: rgb, und nicht RGB.\n\n" << white;
			break;
		default:
			//assume the guess is valid
			break;
		}
		
	} while (Status != EGuessStatus::ok); //keep looping until no errors

	return Guess;
}

bool AskToPlayAgain()
{	
	std::cout << blue << "M" << oe << "chtest du noch einmal spielen? Schreibe JA oder NEIN und dr" << ue << "cke ENTER: " << white;
	FText  Response = "";
	std::getline(std::cin, Response);
	
	std::cout << "_________________________________________________________________________________\n";
	return (Response[0] == 'J') || (Response[0] == 'j');
}

void PrintGameSummary()
{
	if (MMGame.IsGameWon())
	{
		std::cout << green << "_________________________________________________________________________________\n";
		std::cout << " \n";
		std::cout << "        ,___,       \n";
		std::cout << "        [O,O]      Du hast GEWONNEN.   \n";
		std::cout << "      ==(__)==     Gut gemacht.\n";
		std::cout << "       -\"--\"-        \n";
		std::cout << "_________________________________________________________________________________" << white;
	}
	else
	{
		std::cout << red << "_________________________________________________________________________________\n";
		std::cout << " \n";
		std::cout << "        ,___,       \n";
		std::cout << "        [O,o]       Du hast leider verloren." << blue << " L" << oe << "sung: " << MMGame.GetHiddenWord() << red << " \n";
		std::cout << "        /)__)       Vielleicht klappt es beim n"<<ae<<"chsten mal.\n";
		std::cout << "        -\"--\"-        \n";
		std::cout << "_________________________________________________________________________________" << white;
	}
	std::cout << std::endl;
}
