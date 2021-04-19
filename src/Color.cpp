#include "Color.hpp"

Color::Color(int r, int g, int b)
    : r(r), g(g), b(b)
{
}

Color Color::black{0, 0, 0};
Color Color::blue{0, 0, 255};
Color Color::cyan{0, 255, 255};
Color Color::gray{128, 128, 128};
Color Color::green{0, 255, 0};
Color Color::magenta{255, 0, 255};
Color Color::orange{255, 128, 0};
Color Color::red{255, 0, 0};
Color Color::yellow{255, 255, 0};
Color Color::white{255, 255, 255};