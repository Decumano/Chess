#pragma once

#ifdef _WIN32
  #include <windows.h>
#endif

#include <chrono>
#include <thread>

int find(const char arr[], int len, char seek);
void ClearScreen();
void CrossSleep(int milliseconds);
int abs(int value);