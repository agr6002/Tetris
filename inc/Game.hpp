#pragma once
#include <stdio.h>
#include "SDL.h"
#include "SDL_mixer.h"
#include "Block.hpp"
#include "Config.hpp"
#include "Color.hpp"
#include "Piece.hpp"

class Game
{
public:
  Game();
  ~Game();

private:
  void CheckLine();
  bool CheckPieceDrop(int dx, int dy);
  void ClearLine(int row);
  void CopyPiece();
  void CreateNewPiece(Piece *piece, int row, int col);
  void GameOver();
  bool Initialize();
  void LoadData();
  void Run();
  void RunModel();
  void RunController();
  void RunView();
  void UnloadData();

  Block *blocks[Config::numBoardRows][Config::numBoardCols];
  Block *nextBlocks[Config::numDisplayRows][Config::numDisplayCols];
  int blockSize = 0;
  Uint32 fallDelayFast = Config::fallDelayFast;
  Uint32 fallDelayRegular = Config::fallDelayRegular;
  bool isDropping = false;
  bool isRunning = true;
  bool isPlaying = true;
  static int const numOfSoundEffects = 3;
  char const *MUSIC_FILE = "media/music-1.ogg";
  char const *SOUND_EFFECTS_FILE[numOfSoundEffects] = 
      {"media/selection.wav", "media/line.wav",  "media/clear.wav"};
  Mix_Music *music = NULL;
  Mix_Music *sound_effects[numOfSoundEffects] = 
      {NULL, NULL, NULL};
  int numBoardCols = Config::numBoardCols;
  int numBoardRows = Config::numBoardRows;
  int numDisplayCols = Config::numDisplayCols;
  int numDisplayRows = Config::numDisplayRows;
  Piece *piece = nullptr;
  Piece *nextPiece = nullptr;
  SDL_Renderer *renderer = nullptr;
  Uint32 timeDelayed = 0;
  Uint32 timePrior = 0;
  Color &wallColor = Color::gray;
  SDL_Window *window = nullptr;
  int windowHeight = 0;
  int windowWidth = 0;
};
