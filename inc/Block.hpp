#pragma once
#include "Color.hpp"
#include "SDL.h"
#include "Vec2.hpp"

class Block
{
public:
  Block(Color &color, int size, Vec2 pos);

  void Draw(SDL_Renderer *renderer);

  Vec2 pos;
  Color &color;

private:
  int size;
};
