#include <algorithm>
#include <iostream>
#include "Game.hpp"
#include "Vec2.hpp"
#include <stdio.h>
#include "SDL.h"
#include "SDL_mixer.h"

//remember to destroy blocks & pieces

using std::cout;
using std::endl;
using std::max;
using std::min;

Game::Game()
{
  cout << "Game::Game()" << endl;
  if (Initialize())
  {
    Run();
  }
}

Game::~Game()
{
  cout << "Game::~Game()" << endl;
  Mix_FreeMusic(music);
  music = NULL;
  for (auto sound_effect: sound_effects)
  {
    Mix_FreeMusic(sound_effect);
    sound_effect = NULL;
  }

  UnloadData();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  Mix_Quit();
  SDL_Quit();
}

void Game::CheckLine()
{
  std::cout << "check line" << std::endl;
  for (auto block : piece->blocks)
  {
    bool isLine = true;
    for (int i = 1; i < numBoardCols - 1; i++)
    {
      if (!blocks[block->pos.row][i]) 
      {
        isLine = false;
      }
    }
    if (isLine == true)
    {
      std::cout << "clear line" << std::endl;
      ClearLine(block->pos.row);
    }
  }
  for (int row = numBoardRows - 2; row > 0; row--)
  {
    for (int col = 1; col < numBoardCols - 1; col++) 
    {
      if (blocks[row][col] && row != blocks[row][col]->pos.row)
      {
        blocks[blocks[row][col]->pos.row][col] = blocks[row][col];
        blocks[row][col] = nullptr;
      }
    }
  }
}

bool Game::CheckPieceDrop(int dx, int dy)
{
  for (auto block : piece->blocks)
  {
    if (blocks[block->pos.row + dy][block->pos.col + dx])
    {
      return false;
    }
  }
  return true;
}

void Game::ClearLine(int r)
{
  std::cout << r << std::endl;
  Mix_PlayMusic(sound_effects[1], -1);
  for (int col = 1; col < numBoardCols - 1; col++)
  {
    blocks[r][col] = nullptr;
  }
  for (int row = r; row > 0; row--)
  {
    for (int col = 1; col < numBoardCols - 1; col++) 
    {
      if (blocks[row][col])
      {
        blocks[row][col]->pos.row += 1;
      }
    }
  }
}

void Game::CreateNewPiece(Piece *piece1, int row, int col)
{
  // int num = (std::rand()% 6);
  // piece1 = new Piece(Vec2{row, col}, blockSize, num);
}

void Game::CopyPiece()
{
  for (auto block : piece->blocks)
  {
    blocks[block->pos.row][block->pos.col] = block;
  }
}

void Game::GameOver()
{
  for (auto block : piece->blocks)
  {
    if (block->pos.row < 1)
    {
      isPlaying = false;
      Mix_PlayMusic(sound_effects[2], -1);
    }
  }
}

bool Game::Initialize()
{
  cout << "Game::Initialize()" << endl;

  int blockWidth = Config::windowMaxWidth / (numBoardCols + numDisplayCols);
  int blockHeight = Config::windowMaxHeight / max(numBoardRows, numDisplayRows);
  blockSize = min(blockWidth, blockHeight);
  windowWidth = blockSize * (numBoardCols + numDisplayCols);
  windowHeight = blockSize * max(numBoardRows, numDisplayRows);

  // if (SDL_Init(SDL_INIT_VIDEO) != 0)
  // {
  //   SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
  //   return false;
  // }

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
  {
    printf("SDL could not initialize: %s\n", SDL_GetError());
    return false;
  }

  window = SDL_CreateWindow(
      Config::title,
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      windowWidth, windowHeight,
      0);
  if (!window)
  {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer)
  {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return false;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  {
    printf("SDL_mixer could not initialize: %s\n", Mix_GetError());
    return false;
  }

  music = Mix_LoadMUS(MUSIC_FILE);
  if (music == NULL)
  {
    printf("Failed to load music: %s\n", Mix_GetError());
    return false;
  }
  for (int i = 0; i < numOfSoundEffects; i++)
  {
    sound_effects[i] = Mix_LoadMUS(SOUND_EFFECTS_FILE[i]);
    if (sound_effects[i] == NULL)
    {
      printf("Failed to load music: %s\n", Mix_GetError());
      return false;
    }
  }
  Mix_PlayMusic(music, -1);
  Mix_PauseMusic();
  // TODO: Random::Init();

  LoadData();

  timePrior = SDL_GetTicks();

  return true;
}

void Game::LoadData()
{
  cout << "Game::LoadData()" << endl;
  for (int row = 0; row < numBoardRows; ++row)
  {
    for (int col = 0; col < numBoardCols; ++col)
    {
      if (row == 0 || row == numBoardRows - 1 || col == 0 || col == numBoardCols - 1)
      {
        blocks[row][col] = new Block{wallColor, blockSize, Vec2{row, col}};
      }
      else
      {
        blocks[row][col] = nullptr;
      }
    }
  }
  // for (int row = 0; row < numDisplayRows; ++row)
  // {
  //   for (int col = 0; col < numDisplayCols; ++col)
  //   {
  //     if (row == 0 || row == numDisplayRows - 1 || col == 0 || col == numDisplayCols - 1)
  //     {
  //       nextBlocks[row][col] = new Block{wallColor, blockSize, Vec2{row, col + numBoardCols}};
  //     }
  //     else
  //     {
  //       nextBlocks[row][col] = nullptr;
  //     }
  //   }
  // }
  // CreateNewPiece(piece, 1, numBoardCols / 2);
  // CreateNewPiece(nextPiece, numDisplayRows / 2, numBoardCols + numDisplayCols / 2);
}

void Game::Run()
{
  cout << "Game::Run()" << endl;
  while (isRunning)
  {
    // while (isPlaying)
    // {
      RunController();
      RunModel();
    // }
    RunView();
  }
}

void Game::RunController()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      isRunning = false;
      break;
    }
  }

  const Uint8 *keyState = SDL_GetKeyboardState(NULL);
  if (keyState[SDL_SCANCODE_ESCAPE])
  {
    isRunning = false;
  }
  isDropping = (keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN]);
  if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT])
  {
    if (CheckPieceDrop(-1, 0))
    {
      piece->Move(-1);
    }
  }
  if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT])
  {
    if (CheckPieceDrop(1, 0))
    {
      piece->Move(1);
    }
  }
  if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP])
  {
    piece->Rotate(1);
    if (!CheckPieceDrop(0, 0))
    {
    piece->Rotate(-1);
    }
  }
  // if (keyState[SDL_SCANCODE_N] && !Mix_PlayingMusic())
  // {
  //    Mix_PlayMusic(music, -1);
  // }
  // if (keyState[SDL_SCANCODE_M] && Mix_PlayingMusic())
  // {
  //   Mix_HaltMusic();
  // }
  if (keyState[SDL_SCANCODE_P] && !Mix_PausedMusic())
  {
    Mix_PauseMusic();
  }
  if (keyState[SDL_SCANCODE_U] && Mix_PausedMusic())
  {
    Mix_ResumeMusic();
  }
}

void Game::RunModel()
{
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), timePrior + 16))
    ;
  Uint32 timeChange = SDL_GetTicks() - timePrior;
  if (timeChange > 50)
  {
    timeChange = 50;
  }
  timeDelayed += timeChange;
  Uint32 fallDelay = (isDropping ? fallDelayFast : fallDelayRegular);
  if (timeDelayed >= fallDelay)
  {
    if(Mix_PlayingMusic())
      {
        Mix_HaltMusic();
      }
    if (CheckPieceDrop(0,1))
    {
      piece->Drop();
    } else
    {
      Mix_PlayMusic(sound_effects[0], -1);
      CopyPiece();
      CheckLine();
      GameOver();
      // piece = nextPiece;
      // CreateNewPiece(nextPiece, numDisplayRows / 2, numBoardCols + numDisplayCols /2);
    }
    timeDelayed -= fallDelay;
  }
  timePrior = SDL_GetTicks();
}

void Game::RunView()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  for (int row = 0; row < numBoardRows; ++row)
  {
    for (int col = 0; col < numBoardCols; ++col)
    {
      Block *block = blocks[row][col];
      if (block)
      {
        block->Draw(renderer);
      }
    }
  }
  // for (int row = 0; row < numDisplayRows; ++row)
  // {
  //   for (int col = 0; col < numDisplayCols; ++col)
  //   {
  //     Block *block = nextBlocks[row][col];
  //     if (block)
  //     {
  //       block->Draw(renderer);
  //     }
  //   }
  // }
  piece->Draw(renderer);
  // nextPiece->Draw(renderer);
  SDL_RenderPresent(renderer);
}

void Game::UnloadData()
{
  cout << "Game::UnloadData()" << endl;
  // TODO
}