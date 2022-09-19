#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <process.h>
#include "System.h"

void Init();
void Update();
void DrawLine();
void DrawScore();
void DrawArrow();
void DrawTimer();
void CheckTimer();
void CheckInput(int direction);
void GameOver();
int Input();
unsigned _stdcall TimerThread(void* arg);

#endif
