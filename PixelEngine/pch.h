#pragma once
#include <exception>
#include <sys/types.h>  

//Standard Library load
#pragma region SDL
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>
#include <thread>
#include <future>
#include <mutex>
#include <filesystem>
#include <future>
#include <mutex>
#include <memory>
#include <set>
#include <execution>
#include <numeric>
#include <mutex>
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
using std::thread;
using std::list;
using std::mutex;
using std::fstream;
using std::ifstream;
using std::ostream;
using std::stringstream;
using std::to_string;
using std::ofstream;
using std::unordered_map;
using std::future;
using std::pair;
using std::function;
using std::stoi;
using std::stof;
using std::stol;
using std::stoull;
using std::getline;
using std::future;
using std::mutex;
using std::async;
using std::set;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;

typedef Vector3 rVector3;
typedef Vector2 rVector2;
typedef Color rColor;

#define fs std::filesystem

enum class ApplicationState {TitleScreen, Scripting};
#include "Color.h"