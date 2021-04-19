#pragma once
#include <vector>
#include "Block.hpp"
#include "Vec2.hpp"
#include "SDL.h"

class Piece
{
public:
  Piece(Vec2 pos, int size, int pieceNum);

  void CreateBlocks();
  void ChangeType(Vec2 changeTo[2][4], int rotation);
  void Draw(SDL_Renderer *renderer) const;
  bool Drop();
  void GetTypes(int pieceNum, int rotation);
  void Rotate(int direction);
  void Move(int direction);

  std::vector<Block *> blocks;
  int betweenCols = 0;
  int betweenRotate = 0;
  static const int numberOfBlocks = 4;
  static const int numberOfRotation = 4;
  int pieceNum;
  Vec2 pos;
  int rotate = 0;
  const int swapNumC = 5;
  const int swapNumR = 10;
  const int size;
  Vec2 type[numberOfBlocks] = {Vec2{0,0}, Vec2{0,0}, Vec2{0,0}, Vec2{0,0}};

private:
  Color colors[7] = {Color::blue, Color::cyan, Color::green, Color::magenta, 
    Color::orange, Color::red, Color::yellow};

  Vec2 bluePiece[numberOfRotation][numberOfBlocks] = {
    {Vec2{-1, -1}, Vec2{0, -1}, Vec2{0, 0}, Vec2{0, 1}},
    {Vec2{-1, 0}, Vec2{-1, 1}, Vec2{0, 0}, Vec2{1, 0}},
    {Vec2{0, -1}, Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 1}},
    {Vec2{1, -1}, Vec2{1, 0}, Vec2{0, 0}, Vec2{-1, 0}}
  };
  Vec2 cyanPiece[numberOfRotation][numberOfBlocks] = {
    {Vec2{0, -2}, Vec2{0, -1}, Vec2{0, 0}, Vec2{0, 1}},
    {Vec2{-1, 0}, Vec2{0, 0}, Vec2{1, 0}, Vec2{2, 0}},
    {Vec2{1, -2}, Vec2{1, -1}, Vec2{1, 0}, Vec2{1, 1}},
    {Vec2{-1, -1}, Vec2{0, -1}, Vec2{1, -1}, Vec2{2, -1}}
  };
  Vec2 greenPiece[numberOfBlocks][numberOfBlocks] = {
    {Vec2{-1, 0}, Vec2{-1, 1}, Vec2{0, 0}, Vec2{0, -1}},
    {Vec2{-1, 0}, Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 1}},
    {Vec2{-1, 1}, Vec2{-1, 2}, Vec2{0, 1}, Vec2{0, 0}},
    {Vec2{-1, 0}, Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 1}}
  };
  Vec2 magentaPiece[numberOfRotation][numberOfBlocks] = {
    {Vec2{-1, 0}, Vec2{0, -1}, Vec2{0, 0}, Vec2{0, 1}},
    {Vec2{-1, 0}, Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 0}},
    {Vec2{0, -1}, Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 0}},
    {Vec2{-1, 0}, Vec2{0, -1}, Vec2{0, 0}, Vec2{1, 0}}
  };
  Vec2 orangePiece[numberOfRotation][numberOfBlocks] = {
    {Vec2{0, -1}, Vec2{0, 0}, Vec2{0, 1}, Vec2{-1, 1}},
    {Vec2{-1, 0}, Vec2{0, 0}, Vec2{1, 0}, Vec2{1, 1}},
    {Vec2{1, -1}, Vec2{0, -1}, Vec2{0, 0}, Vec2{0, 1}},
    {Vec2{-1, -1}, Vec2{-1, 0}, Vec2{0, 0}, Vec2{1, 0}}
  };
  Vec2 redPiece[numberOfRotation][numberOfBlocks] = {
    {Vec2{-1, -1}, Vec2{-1, 0}, Vec2{0, 0}, Vec2{0, 1}},
    {Vec2{-1, 1}, Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 0}},
    {Vec2{-1, 0}, Vec2{-1, 1}, Vec2{0, 1}, Vec2{0, 2}},
    {Vec2{-1, 1}, Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 0}}
  };
  Vec2 yellowPiece[numberOfRotation][numberOfBlocks] = {
    {Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 0}, Vec2{1, 1}},
    {Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 0}, Vec2{1, 1}},
    {Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 0}, Vec2{1, 1}},
    {Vec2{0, 0}, Vec2{0, 1}, Vec2{1, 0}, Vec2{1, 1}}
  };
};
