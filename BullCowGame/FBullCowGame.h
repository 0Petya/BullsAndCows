#pragma once

#include <string>
#define FString std::string
#include <unordered_set>
#define TSet std::unordered_set
#include <map>
#define TMap std::map
#define int32 int
#include <fstream>
#include <ctime>

struct FBullCowCount {
  int32 Bulls = 0;
  int32 Cows = 0;
};

enum class EGuessStatus {
  HAS_NON_LETTERS, NOT_ISOGRAM, INVALID_LENGTH, OK
};

class FBullCowGame {
public:
  FBullCowGame();

  int32 GetDifficulty() const;
  int32 GetCurrentAttempt() const;
  int32 GetHiddenWordLength() const;
  bool IsGameWon() const;
  FString GetHiddenWord() const;
  int32 GetMaxAttempts() const;
  EGuessStatus GetGuessStatus(FString) const;

  void IncreaseDifficulty();
  FBullCowCount SubmitGuess(FString);
  void Reset(int32);

private:
  FString Words[173529];
  int32 Difficulty;
  int32 CurrentAttempt;
  FString HiddenWord;
  bool bHasWon;

  bool IsIsogram(FString) const;
  bool IsAlpha(FString) const;
  FString ToLower(FString) const;
};
