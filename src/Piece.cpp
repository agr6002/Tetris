#include "Piece.hpp"
#include "Game.hpp"
#include <iostream>

Piece::Piece(Vec2 pos, int size, int pieceNum)
  : pos(pos), size(size), pieceNum(pieceNum)
{
  CreateBlocks();
  GetTypes(pieceNum, 0);
}

void Piece::CreateBlocks() 
{
  for (int i = 0; i < numberOfBlocks; i++)
  {
  blocks.emplace_back(new Block{colors[pieceNum], size, Vec2{10, 10}});
  }
}

void Piece::ChangeType(Vec2 changeTo[numberOfRotation][numberOfBlocks], int rotation)
{
  for (int i = 0; i < numberOfBlocks; i++)
  {
    type[i] = changeTo[rotation][i];
    blocks[i]->pos.row = pos.row + type[i].row;
    blocks[i]->pos.col = pos.col + type[i].col;
  }
}


void Piece::Draw(SDL_Renderer *renderer) const
{
  for (auto block : blocks)
  {
    block->Draw(renderer);
  }
}

bool Piece::Drop()
{
  for (auto block : blocks)
  {
    block->pos.row += 1;
  }
  pos.row += 1;
  return true;
}

void Piece::GetTypes(int pieceNum, int rotation)
{
  if (pieceNum == 0) 
  {
    ChangeType(bluePiece, rotation); 
  } else if (pieceNum == 1)
  {
    ChangeType(cyanPiece, rotation); 
  } else if (pieceNum == 2)
  {
   ChangeType(greenPiece, rotation); 
  } else if (pieceNum == 3)
  {
    ChangeType(magentaPiece, rotation); 
  } else if (pieceNum == 4)
  {
    ChangeType(orangePiece, rotation); 
  } else if (pieceNum == 5)
  {
    ChangeType(redPiece, rotation); 
  } else if (pieceNum == 6)
  {
    ChangeType(yellowPiece, rotation);
  }
}

void Piece::Rotate(int direction)
{
  if (direction > 0)
  {
    betweenRotate += 1;
  } else {
    betweenRotate -= 1;
  }
  if (std::abs(betweenRotate) == swapNumR) {
    betweenRotate = 0;
    rotate += direction;
    if (rotate == numberOfRotation) {
      rotate = 0;
    }
    GetTypes(pieceNum, rotate);
  }
}

void Piece::Move(int direction)
{
  if (direction > 0)
  {
    betweenCols += 1;
  } else {
    betweenCols -= 1;
  }
  if (std::abs(betweenCols) == swapNumC) {
    betweenCols = 0;
    pos.col += direction;
    for (auto block : blocks)
    {
      block->pos.col += direction;
    }
  }
}
