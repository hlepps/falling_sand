#pragma once
#include <cstdlib>
#include <ctime>
#include "raylib.h"

#include "PixelMaterial.h"

void InitRules(int width, int height);

void CheckRules(Color* pixels, int width, int height);
