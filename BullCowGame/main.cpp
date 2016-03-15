#pragma once

#include <stdlib.h>
#include <iostream>
#include <string>
#define FText std::string
#define int32 int
#include "FBullCowGame.h"

FBullCowGame BCGame;

bool AskToPlayAgain(bool bWon) {
  if (bWon) std::cout << "Move on to the next level? ";
  else std::cout << "Try this level with a new word? ";

  FText Response = "";
  getline(std::cin, Response);
  system("cls");

  return tolower(Response[0]) == 'y';
}

FText GetValidGuess() {
  while (true) {
    FText S = (BCGame.GetCurrentAttempt() == BCGame.GetMaxAttempts()) ? " " : "s ";
    std::cout << BCGame.GetMaxAttempts() - BCGame.GetCurrentAttempt() + 1 << " attempt" << S << "left. Enter your guess: ";
    FText Guess;
    getline(std::cin, Guess);

    EGuessStatus Status = BCGame.GetGuessStatus(Guess);
    switch (Status) {
    case EGuessStatus::HAS_NON_LETTERS:
      std::cout << "Only letters allowed. Try again.";
      break;
    case EGuessStatus::NOT_ISOGRAM:
      std::cout << "Not an isogram. Try again.";
      break;
    case EGuessStatus::INVALID_LENGTH:
      std::cout << "Only " << BCGame.GetHiddenWordLength() << " letter words allowed. Try again.";
      break;
    default:
      return Guess;
    }
    std::cout << std::endl << std::endl;
  }
}

void PlayGame() {
  while (!BCGame.IsGameWon() && BCGame.GetCurrentAttempt() <= BCGame.GetMaxAttempts()) {
    FText Guess = GetValidGuess();
    FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
    std::cout << "Bulls = " << BullCowCount.Bulls << " Cows = " << BullCowCount.Cows << std::endl << std::endl;
  }

  if (BCGame.IsGameWon()) {
    BCGame.IncreaseDifficulty();
    FText S = (BCGame.GetCurrentAttempt() == 2) ? "!" : "s!";
    std::cout << "Congratulations! You got it in " << BCGame.GetCurrentAttempt() - 1 << " attempt" << S << std::endl;

    if (BCGame.GetDifficulty() == 13)
      std::cout << "You beat level 12! You are ultimate Bull and Cow rancher!" << std::endl;
  }
  else
    std::cout << "Out of attempts. You lose." << std::endl << "The word was: " << BCGame.GetHiddenWord() << std::endl;
}

void PrintIntro() {
  BCGame.Reset(BCGame.GetDifficulty());

  std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
  std::cout << std::endl;
  std::cout << "          }   {         ___ " << std::endl;
  std::cout << "          (o o)        (o o) " << std::endl;
  std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
  std::cout << "  / |      |O            O|      | \\ " << std::endl;
  std::cout << " *  |-,--- |              |------|  * " << std::endl;
  std::cout << "    ^      ^              ^      ^ " << std::endl;
  std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl << std::endl;
}

int main() {
  do {
    PrintIntro();
    PlayGame();
  } while (BCGame.GetDifficulty() != 13 && AskToPlayAgain(BCGame.IsGameWon()));

  std::cout << "Have a good day!" << std::endl;
  return 0;
}
