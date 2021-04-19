#pragma once

struct Color
{
  Color(int r, int g, int b);

  static Color black;
  static Color blue;
  static Color cyan;
  static Color gray;
  static Color green;
  static Color magenta;
  static Color orange;
  static Color red;
  static Color yellow;
  static Color white;

  int r;
  int g;
  int b;
};
