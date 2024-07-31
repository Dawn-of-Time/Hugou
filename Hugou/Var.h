#pragma once
#include "FloatingNoteManager.h"
#include "FileManager.h"
#include <Windows.h>

extern FloatingNoteManager floatingNoteManager;
extern FileManager fileManager;
extern bool isMaximum;
extern double getScale();

double calculateScale();
