
#include "Color.hpp"



//std::map<std::string, std::array<uint8_t, 3>> Color::colors =
//{
//    {"white", {0, 0, 0}},
//    { "red", {255, 0, 0}},
//    { "green", {0, 255, 0}},
//    { "blue", {0, 0, 255}}
//};
//
//
//uint8_t Color::percentToUInt8(double percentage)
//{
//    int rgbInt = percentage / 100 * 255;
//    uint8_t rgbUInt = rgbInt;
//    return rgbUInt;
//}
//
//RGBA Color::makeRGBA(std::string colorName, double percentAlpha)
//{
//    return RGBA(Color::colors[colorName][0],
//                Color::colors[colorName][1],
//                Color::colors[colorName][2],
//                percentToUInt8(percentAlpha));
//}
//
//RGBA Color::operator()(std::string colorName, double percentAlpha)
//{
//    return makeRGBA(colorName, percentAlpha);
//}
//
