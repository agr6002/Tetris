#pragma once

struct Config
{
  static int const fallDelayFast = 100;    // milliseconds b/w falls
  static int const fallDelayRegular = 500; // milliseconds b/w falls
  static int const numBoardCols = 12;      // including walls
  static int const numBoardRows = 22;      // including walls
  static int const numDisplayCols = 8;
  static int const numDisplayRows = 8;
  inline static char const *title = "Tetris";
  static int const windowMaxHeight = 700;
  static int const windowMaxWidth = 1024;
};
