#pragma once

#include "structure.h"

int ScreenCapture(uint iGrHandle, int x, int y);
extern int hBackImage;
int SetBackground(int hImage);

int Resize(game* g, double skinX, double skinY, bool bit16);
extern int skinSizeX, skinSizeY;
extern int screenSizeX, screenSizeY;
