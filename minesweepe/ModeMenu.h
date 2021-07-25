/****************************************
ModeMenu.h
Author: Student
Date: 2019/12/15
Description:
�����˳���˵�����Ⱦ/����ģ���ͷ�ļ�����ModeMenu�����ռ��ֹͬ����Ⱦ
������˵����
void InitMenu() 	 ��ʼ���˵�������Ⱦ�˵�ѡ��
void WaitChoice()	 �ȴ��û����루ѡ��˵��ȣ�
*****************************************/
#pragma once
#ifndef MODEMENU_H
#define MODEMENU_H
#include "Graphic.h"
#include "Controller.h"
#include "DifficultyMenu.h"
#include "DifficultyMenu0.h"
#include <time.h>

namespace ModeMenu {
	void InitMenu();
	void WaitChoice();
}
#endif // MODEMENU_H