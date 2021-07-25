/****************************************
DifficultyMenu.cpp
Author: Student
Date: 2019/12/15
Description:
定义了六边形地图难度菜单的渲染/管理模块，用DiffucultyMenu命名空间防止同名污染
*****************************************/
#include "DifficultyMenu.h"
int MapHeight = 0;				   // 地图高度
int MapWidth = 0;				   // 地图宽度
int BoomNum = 0;				   // 地雷数量

namespace DifficultyMenu {
	// 引入两个命名空间
	using namespace Graphic;
	using namespace Controller;

	size_t frame = 0;                  // 定义已渲染的帧数 
	COORD pos = { 0 }, hitPos = { 0 }; // 定义鼠标当前的坐标和左键点击的坐标
	int choice = 0, oldChoice = 0;     // 定义选中的菜单项
	bool isChosen = false;             // 定义是否做出选择
	char key = '\0';                   // 定义当前键盘的按键
	clock_t tic = clock();             // 定义程序上一帧渲染的时刻
	// 如果你有新加的变量，建议加在下方和预置变量做区别

	/****************************************
	Function:  renderMenu()
	Parameter: None(void)
	Return:    None(void)
	Description:
	清屏并且打印标题和相关菜单选项
	*****************************************/
	void renderMenu() {
		ClearScreen();  // 清屏
		MovePos(17, 2); // 移动坐标到 17,2
		PutString("难度"); // 在这个坐标放置一个string
		MovePos(17, 4);
		PutString("简单");
		MovePos(17, 6);
		PutString("普通");
		MovePos(17, 8);
		PutString("困难");
		MovePos(16, 10);
		PutString("自定义");
		Update();
	}

	/****************************************
	Function:  InitMenu()
	Parameter: None(void)
	Return:    None(void)
	Description:
	初始化菜单，同时初始化图形框架和控制器框架
	*****************************************/
	void InitMenu() {
		renderMenu();        // 绘制菜单
	}

	/****************************************
	Function:  randerChoiceBackground(int choice)
	Parameter: int choice
	Return:    None(void)
	Description:
	将当前选中的菜单项(int choice)背景渲染一个渐变消失的白色
	*****************************************/
	void randerChoiceBackground(int choice) {
		size_t y = 0;  // 定义当前选中的菜单项的实际y坐标
		const BYTE alpha = 255 - (BYTE)((frame % 50) * 5);  // 定义背景白色当前的颜色值，通过已渲染的帧数进行运算（此处也可以改成使用时间）
		switch (choice) {
		case 0:
			y = 4;
			break;
		case 1:
			y = 6;
			break;
		case 2:
			y = 8;
			break;
		case 3:
			y = 10;
			break;
		}
		for (size_t x = 10; x < 30; x++) {
			MovePos((SHORT)x, (SHORT)y); // 将坐标移到目标点
			ModColor(2, 255, 255, 255, alpha, alpha, alpha); // 修改背景色
		}
		Update();  // 更新界面
	}

	/****************************************
	Function:  clearChoiceBackground(int choice)
	Parameter: int choice
	Return:    None(void)
	Description:
	将上次选中的菜单项(int choice)背景恢复为黑色，内容大致和上一个函数一致，不多做阐述
	*****************************************/
	void clearChoiceBackground(int choice) {
		size_t y = 0;
		switch (choice) {
		case 0:
			y = 4;
			break;
		case 1:
			y = 6;
			break;
		case 2:
			y = 8;
			break;
		case 3:
			y = 10;
			break;
		}
		for (size_t x = 10; x < 30; x++) {
			MovePos((SHORT)x, (SHORT)y);
			ModColor(2, 255, 255, 255, 0, 0, 0);
		}
	}

	/****************************************
	Function:  checkChoice()
	Parameter: None(void)
	Return:    None(void)
	Description:
	检查键盘/鼠标输入，并更新选中的菜单项
	*****************************************/
	void checkChoice() {
		FlushInput();           // 刷新输入缓冲区
		pos = GetCursorPos();   // 获取鼠标输入
		key = GetKeyHit();		// 获取键盘输入
		hitPos = GetCursorHitPos();  // 获取鼠标单击输入
		isChosen = false;		// 重置选中状态

		// 检查鼠标位置，更新选中项
		if (!(pos.Y != 4 || pos.X < 10 || pos.X > 30)) {
			choice = 0;
		}
		else if (!(pos.Y != 6 || pos.X < 10 || pos.X > 30)) {
			choice = 1;
		}
		else if (!(pos.Y != 8 || pos.X < 10 || pos.X > 30)) {
			choice = 2;
		}
		else if (!(pos.Y != 10 || pos.X < 10 || pos.X > 30)) {
			choice = 3;
		}

		// 检查键盘按键，更新选中项
		switch (key) {
		case VK_UP:
			// 上方向键
			if (choice > 0)choice--;
			break;
		case VK_DOWN:
			// 下方向键
			if (choice < 3)choice++;
			break;
		case VK_RETURN:
			// 回车，更新选中
			isChosen = true;
			break;
		}

		// 检查鼠标点击的位置是否在菜单项中，如果是，更新选中
		if (!(hitPos.Y != 4 || hitPos.X < 10 || hitPos.X > 30)) {
			isChosen = true;
		}
		else if (!(hitPos.Y != 6 || hitPos.X < 10 || hitPos.X > 30)) {
			isChosen = true;
		}
		else if (!(hitPos.Y != 8 || hitPos.X < 10 || hitPos.X > 30)) {
			isChosen = true;
		}
		else if (!(hitPos.Y != 10 || hitPos.X < 10 || hitPos.X > 30)) {
			isChosen = true;
		}
	}

	/****************************************
	Function:  WaitChoice()
	Parameter: None(void)
	Return:    None(void)
	Description:
	主循环，若不退出将一直渲染下去
	*****************************************/
	void WaitChoice() {
		bool runFlag = true;
		while (runFlag) {
			checkChoice();  // 检查输入

			if (choice != oldChoice) {
				// 若新的选择与旧选择不一致，将旧选择的背景清空
				clearChoiceBackground(oldChoice);
				oldChoice = choice;
			}
			randerChoiceBackground(choice); // 绘制选中项的背景

			// 如果选中菜单，执行操作
			if (isChosen) {
				switch (choice) {
				case 0:
					// 简单
					MapHeight = 12;
					MapWidth = 12;
					BoomNum = 10;
					InitGraphic(40, 22); // 初始化新的窗口大小为44,25
					InitController();    // 初始化控制器

					GameEngine::InitGame();
					GameEngine::Play();
					GameEngine::DestroyGame();
					runFlag = false;
					break;
				case 1:
					// 普通
					MapHeight = 20;
					MapWidth = 20;
					BoomNum = 30;
					InitGraphic(65, 30); // 初始化新的窗口大小为65,37
					InitController();    // 初始化控制器

					GameEngine::InitGame();
					GameEngine::Play();
					GameEngine::DestroyGame();
					runFlag = false;
					break;
				case 2:
					// 困难
					MapHeight = 30;
					MapWidth = 50;
					BoomNum = 99;
					InitGraphic(160, 40); // 初始化新的窗口大小为121,37
					InitController();    // 初始化控制器

					GameEngine::InitGame();
					GameEngine::Play();
					GameEngine::DestroyGame();
					runFlag = false;
					break;
				case 3:
					// 自定义
					//设置系统颜色
					system("color 07");

					// 显示光标
					HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);  // 获取标准输出句柄
					CONSOLE_CURSOR_INFO cci;
					cci.bVisible = 1;
					cci.dwSize = 1;
					SetConsoleCursorInfo(hStdOut, &cci);

					//清屏
					system("cls");

					//自定义输入
					printf("请输入地图高度：");
					scanf_s("%d", &MapHeight);
					printf("请输入地图宽度：");
					scanf_s("%d", &MapWidth);
					printf("请输入地雷数量：");
					scanf_s("%d", &BoomNum);

					MapWidth = 2 * MapWidth;
					//合法化处理
					if (MapHeight > 40)
						MapHeight = 40;
					if (MapWidth > 50)
						MapWidth = 50;

					if (MapHeight < 12)
						MapHeight = 12;
					if (MapWidth < 12)
						MapWidth = 12;

					if (BoomNum > MapWidth* (MapHeight - 1) / 2 - 6)
						BoomNum = MapWidth * (MapHeight - 1) / 2 - 6;

					int w, h;
					if (MapWidth < 10)
						w = 41;
					else
						w = 3 * MapWidth + 10;

					if (MapHeight < 10)
						h = 25;
					else
						h = MapHeight + 10;

					InitGraphic(w, h); // 初始化新的窗口大小
					InitController();    // 初始化控制器

					GameEngine::InitGame();
					GameEngine::Play();
					GameEngine::DestroyGame();
					runFlag = false;
					break;
				}
			}

			// 处理每帧的事务
			frame++;  // 渲染帧数自增
			clock_t elapsed = 25 - (clock() - tic); // 检查上一帧渲染时间，并计算与25的差值
			Sleep(elapsed > 0 ? elapsed : 0);       // 若差值大于零，则休眠该差值的毫秒数，以确保每帧渲染不超过50帧
			tic = clock();							// 更新上一次记录的时间
		}
	}
}