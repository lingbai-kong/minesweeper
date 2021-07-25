/****************************************
GameEngine0.h
Author: Root
Date: 2019/12/09
Description:
定义了程序游戏模块的头文件，用GameEngine0命名空间防止同名污染
各函数说明：
void InitGame()	   初始化游戏
void Play()		   开始游戏
void DestroyGame() 结束游戏
*****************************************/
#pragma once
#ifndef GAMEENGINE0_H
#define GAMEENGINE0_H
#include "Graphic.h"
#include "Controller.h"
#include <time.h>
#include <cstdlib>

namespace GameEngine0 {
	void InitGame();
	void Play();
	void DestroyGame();
}
#endif // GAMEENGINE0_H