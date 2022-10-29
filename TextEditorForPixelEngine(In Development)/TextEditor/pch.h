#pragma once


//Standard Library load
#pragma region SDL
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>
#include <functional>
#include <filesystem>
#include <string_view>
#include "raylib.h"

#pragma endregion SDL

//Standard Containers
#pragma region Containers
#include <vector>
#include <list>
#include <unordered_map>
#include <iterator>

#pragma endregion Container

using std::cout;
using std::string;
using std::vector;
using std::list;
using std::fstream;
using std::ifstream;
using std::ostream;
using std::stringstream;
using std::to_string;
using std::ofstream;
using std::unordered_map;
using std::pair;
using std::function;
using std::string_view;

#define fs std::filesystem
enum class GameScreen { Gameplay, TilteScreen, GameOver };