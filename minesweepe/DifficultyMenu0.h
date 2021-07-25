/****************************************
DifficultyMenu.h
Author: Student
Date: 2019/12/15
Description:
定义了程序菜单的渲染/管理模块的头文件，用DifficultyMenu0命名空间防止同名污染
各函数说明：
void InitMenu() 	 初始化菜单，并渲染菜单选项
void WaitChoice()	 等待用户输入（选择菜单等）
*****************************************/
#pragma once
#ifndef DIFFICULTYMENU0_H
#define DIFFICULTYMENU0_H
#include "Graphic.h"
#include "Controller.h"
#include "GameEngine0.h"
#include <time.h>

namespace DifficultyMenu0 {
	void InitMenu();
	void WaitChoice();
}
#endif // DIFFICULTYMENU0_H
