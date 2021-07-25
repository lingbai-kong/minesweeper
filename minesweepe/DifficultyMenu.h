/****************************************
DifficultyMenu.h
Author: Student
Date: 2019/12/15
Description:
�����˳���˵�����Ⱦ/����ģ���ͷ�ļ�����DifficultyMenu�����ռ��ֹͬ����Ⱦ
������˵����
void InitMenu() 	 ��ʼ���˵�������Ⱦ�˵�ѡ��
void WaitChoice()	 �ȴ��û����루ѡ��˵��ȣ�
*****************************************/
#pragma once
#ifndef DIFFICULTYMENU_H
#define DIFFICULTYMENU_H
#include "Graphic.h"
#include "Controller.h"
#include "GameEngine.h"
#include <time.h>

namespace DifficultyMenu {
	void InitMenu();
	void WaitChoice();
}
#endif // DIFFICULTYMENU_H