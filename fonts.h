#ifndef FONTS_H
#define FONTS_H

#include <unordered_map>
#include <string>

using FontStyles = std::unordered_map<std::string, std::string>;
using FontMap    = std::unordered_map<std::string, FontStyles>;

extern FontMap fonts;

#endif
