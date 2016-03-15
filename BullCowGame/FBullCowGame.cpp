#pragma once

#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() {
  std::ifstream file("enable2k.txt");
  if (file.is_open())
    for (int i = 0; i < sizeof(Words) / sizeof(Words[0]); i++)
      file >> Words[i];

  Difficulty = 4;
  Reset(Difficulty);
}

int32 FBullCowGame::GetDifficulty() const { return Difficulty; }

int32 FBullCowGame::GetCurrentAttempt() const { return CurrentAttempt; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bHasWon; }
FString FBullCowGame::GetHiddenWord() const { return HiddenWord; }

int32 FBullCowGame::GetMaxAttempts() const {
  return HiddenWord.length() * 2 + HiddenWord.length() / 1.5;
}

bool FBullCowGame::IsIsogram(FString Guess) const {
  if (Guess.length() < 2) return true;

  TSet<char> set;
  for (char Letter : Guess) {
    Letter = tolower(Letter);
    if (set.find(Letter) != set.end()) return false;
    else set.insert(Letter);
  }
}

bool FBullCowGame::IsAlpha(FString Guess) const {
  for (char Letter : Guess)
    if (!isalpha(Letter)) return false;

  return true;
}

EGuessStatus FBullCowGame::GetGuessStatus(FString Guess) const {
  if (!IsAlpha(Guess)) return EGuessStatus::HAS_NON_LETTERS;
  else if (!IsIsogram(Guess)) return EGuessStatus::NOT_ISOGRAM;
  else if (Guess.length() != HiddenWord.length()) return EGuessStatus::INVALID_LENGTH;
  else return EGuessStatus::OK;
}

FString FBullCowGame::ToLower(FString String) const {
  FString LowerStr = String;
  for (int i = 0; i < LowerStr.length(); i++) {
    LowerStr[i] = tolower(LowerStr[i]);
  }

  return LowerStr;
}

void FBullCowGame::IncreaseDifficulty() { Difficulty++; }

FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
  CurrentAttempt++;
  FBullCowCount BullCowCount;

  FString LowerGuess = ToLower(Guess);

  for (int32 i = 0; i < LowerGuess.length(); i++) {
    if (LowerGuess[i] == HiddenWord[i]) BullCowCount.Bulls++;
    else
      for (int32 j = 0; j < HiddenWord.length(); j++)
        if (LowerGuess[i] == HiddenWord[j]) BullCowCount.Cows++;
  }

  if (LowerGuess == HiddenWord) bHasWon = true;
  return BullCowCount;
}

void FBullCowGame::Reset(int32 Length) {
  CurrentAttempt = 1;

  HiddenWord = "";
  srand(std::time(NULL));
  while (HiddenWord.length() != Length || !IsIsogram(HiddenWord)) {
    HiddenWord = Words[rand() % 173529];
  }

  bHasWon = false;
}
