#include "Block.hpp"

Block::Block(Color &color, int size, Vec2 pos)
    : color(color), size(size), pos(pos)
{
}

void Block::Draw(SDL_Renderer *renderer)
{
  SDL_Rect rect{pos.col * size + 1, pos.row * size + 1, size - 2, size - 2};
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
  SDL_RenderFillRect(renderer, &rect);
}
