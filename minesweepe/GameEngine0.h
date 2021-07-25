/****************************************
GameEngine0.h
Author: Root
Date: 2019/12/09
Description:
�����˳�����Ϸģ���ͷ�ļ�����GameEngine0�����ռ��ֹͬ����Ⱦ
������˵����
void InitGame()	   ��ʼ����Ϸ
void Play()		   ��ʼ��Ϸ
void DestroyGame() ������Ϸ
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