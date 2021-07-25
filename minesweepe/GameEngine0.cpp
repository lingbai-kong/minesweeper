/****************************************
GameEngine0.cpp
Author: Root
Date: 2019/12/09
Description:
定义了四边形程序游戏模块，用GameEngine0命名空间防止同名污染，是你主要需要修改的文件
*****************************************/
#include "GameEngine0.h"

//拓展的全局变量
extern int MapHeight0;
extern int MapWidth0;
extern int BoomNum0;

namespace GameEngine0 {
	// 引入两个命名空间
	using namespace Graphic;
	using namespace Controller;

	size_t mapWidth = 0, mapHeight = 0;				 // 地图宽度和高度
	UCHAR* mapCanvas = nullptr;						 // 地图数组指针，若做基础项请不要直接尝试操作这个指针
	COORD pos = { 0 }, posOld = { 0 };				 // 鼠标的位置
	COORD posChoice = { 0 }, posChoiceOld = { 0 };	 // 选中地图坐标的位置
	char key = '\0';								 // 键盘的按键
	bool gameFlag = false;							 // 游戏运行状态
	size_t frame = 0;								 // 已渲染帧数
	clock_t tic = clock();							 // 游戏开始时刻
	int operation = 0;								 // 执行的操作
	bool isFirst = true;							 // 是否为第一步
	// 如果你有新加的变量，建议加在下方和预置变量做区别
	UCHAR* hidenCanvas = nullptr;
	SHORT leftNum = BoomNum0;						 // 剩余地雷数
	SHORT stepNum = 0;								 // 所走步数
	bool gameOver = false;							 // 是否游戏失败
	bool gameWin = false;							 // 是否游戏胜利
	int min = 0;									 // 游戏时间（分钟）
	int sec = 0;									 // 游戏时间（秒）
	time_t timeOld = 0;								 // 游戏开始时的系统时间



	/****************************************
	Function:  renderMap()
	Parameter: None(void)
	Return:    None(void)
	Description:
	绘制当前地图
	*****************************************/
	void renderMap() {
		// 从行开始遍历
		for (size_t i = 0; i < mapHeight + 1; i++) {
			// 移动坐标至行首 并绘制行首的字符
			MovePos(0, (SHORT)i * 2 + 3);
			if (i == 0) {
				PutString("╔");
			}
			else if (i == mapHeight) {
				PutString("╚");
			}
			else {
				PutString("╠");
			}

			// 遍历列，绘制边界
			for (size_t j = 0; j < mapWidth; j++) {
				// 移动至确切的坐标，绘制方格的边界
				MovePos(2 + (SHORT)j * 8, (SHORT)i * 2 + 3);
				if (i == 0) {
					if (j < mapWidth - 1) {
						PutString("═══╦");
					}
					else {
						PutString("═══╗");
					}
				}
				else if (i == mapHeight) {
					if (j < mapWidth - 1) {
						PutString("═══╩");
					}
					else {
						PutString("═══╝");
					}
				}
				else {
					if (j < mapWidth - 1) {
						PutString("═══╬");
					}
					else {
						PutString("═══╣");
					}
				}
			}

			// 绘制地雷地图
			if (i > 0 && i < mapHeight + 1) {
				// 移动至行首，绘制边界字符
				MovePos(0, (SHORT)i * 2 + 2);
				PutString("║");
				// 遍历列 绘制地雷
				for (size_t j = 0; j < mapWidth; j++) {
					MovePos(2 + (SHORT)j * 5, (SHORT)i * 2 + 2);    // 移动至确切坐标
					const size_t mapIndex = (i - 1) * mapWidth + j; // 确定地图数组的下标
					char numMap[8] = "   ";							// 确定数字字符串
					numMap[1] = '0' + mapCanvas[mapIndex];			// 当mapCanvas[mapIndex]为1到8时，将其转换成字符串
					switch (mapCanvas[mapIndex]) {
					case 0:
						// 0的时候放置空白
						PutString("   ");
						break;
					case 1:
						// 从1开始绘制数字 带颜色
						PutStringWithColor(numMap, 30, 144, 255, 0, 0, 0);
						break;
					case 2:
						PutStringWithColor(numMap, 0, 255, 127, 0, 0, 0);
						break;
					case 3:
						PutStringWithColor(numMap, 255, 48, 48, 0, 0, 0);
						break;
					case 4:
						PutStringWithColor(numMap, 72, 61, 139, 0, 0, 0);
						break;
					case 5:
						PutStringWithColor(numMap, 255, 105, 180, 0, 0, 0);
						break;
					case 6:
						PutStringWithColor(numMap, 148, 0, 211, 0, 0, 0);
						break;
					case 7:
						PutStringWithColor(numMap, 139, 0, 0, 0, 0, 0);
						break;
					case 8:
						PutStringWithColor(numMap, 139, 34, 82, 0, 0, 0);
						break;
					case 9:
						// 9为地雷
						PutStringWithColor(" ⊙", 255, 0, 0, 0, 0, 0);
						break;
					case 10:
						// 10为地雷标记
						PutStringWithColor(" ☆", 178, 34, 34, 0, 0, 0);
						break;
					case 11:
						// 11为未知标记
						PutStringWithColor(" ■", 255, 255, 255, 0, 0, 0);
						break;
					}

					MovePos(5 + (SHORT)j * 5, (SHORT)i * 2 + 2);
					PutString("║");
				}
			}
		}
		Update(); // 将地图更新到屏幕
	}

	/****************************************
	Function:  getTime()
	Parameter: None(void)
	Return:    None(void)
	Description:
	在第一次挖开地块后计时使用方法二
	*****************************************/
	void getTime()
	{
		if (isFirst)
		{
			timeOld = time(0);
			min = 0;
			sec = 0;
		}
		else if (!gameOver && !gameWin)
		{
			sec = (time(0) - timeOld) % 60;
			min= (time(0) - timeOld) / 60;
		}
	}

	/****************************************
	Function:  InitGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	初始化游戏
	*****************************************/
	void InitGame() {
		ClearScreen();								 // 清屏

		//初始化各个变量
		isFirst = true;
		gameOver = false;
		gameWin = false;
		leftNum = BoomNum0;
		stepNum = 0;

		mapWidth = MapWidth0; mapHeight = MapHeight0;	  // 设置宽高
		mapCanvas = new UCHAR[mapWidth * mapHeight];  // 初始化画板数组
		hidenCanvas = new UCHAR[mapWidth * mapHeight];// 初始化隐藏数组

		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				mapCanvas[i * mapWidth + j] = 11;//(i * mapWidth + j) % 12; // 更新地图数组，依次出现各个特殊字符
				hidenCanvas[i * mapWidth + j] = 0;
			}
		}
		renderMap();	// 绘制地图
	}

	/****************************************
	Function:  renderChoiceBackground(COORD choice)
	Parameter: COORD choice
	Return:    None(void)
	Description:
	绘制选中的地块的背景
	*****************************************/
	void renderChoiceBackground(COORD choice) {
		const SHORT x = choice.X, y = choice.Y;
		const BYTE alpha = 255 - (BYTE)((frame % 50) * 5);        // 定义背景白色当前的颜色值，通过已渲染的帧数进行运算（此处也可以改成使用时间）
		const size_t mapIndex = (size_t)y * mapWidth + (size_t)x; // 确定地图下标

		MovePos(2 + x * 4, y * 2 + 3);

		// 以下内容同renderMap中绘制地雷部分相同，不详做介绍
		char numMap[8] = "  ";
		numMap[0] = '0' + mapCanvas[mapIndex];
		switch (mapCanvas[mapIndex]) {
		case 0:
			PutStringWithColor("  ", 255, 255, 255, alpha, alpha, alpha);
			break;
		case 1:
			PutStringWithColor(numMap, 30, 144, 255, alpha, alpha, alpha);
			break;
		case 2:
			PutStringWithColor(numMap, 0, 255, 127, alpha, alpha, alpha);
			break;
		case 3:
			PutStringWithColor(numMap, 255, 48, 48, alpha, alpha, alpha);
			break;
		case 4:
			PutStringWithColor(numMap, 72, 61, 139, alpha, alpha, alpha);
			break;
		case 5:
			PutStringWithColor(numMap, 255, 105, 180, alpha, alpha, alpha);
			break;
		case 6:
			PutStringWithColor(numMap, 148, 0, 211, alpha, alpha, alpha);
			break;
		case 7:
			PutStringWithColor(numMap, 139, 0, 0, alpha, alpha, alpha);
			break;
		case 8:
			PutStringWithColor(numMap, 139, 34, 82, alpha, alpha, alpha);
			break;
		case 9:
			PutStringWithColor("⊙", 255, 0, 0, alpha, alpha, alpha);
			break;
		case 10:
			PutStringWithColor("☆", 178, 34, 34, alpha, alpha, alpha);
			break;
		case 11:
			PutStringWithColor("■", 255, 255, 255, alpha, alpha, alpha);
			break;
		}
	}

	/****************************************
	Function:  clearChoiceBackground(COORD choice)
	Parameter: COORD choice
	Return:    None(void)
	Description:
	清除choice中指示位置的背景，功能同上，不详做介绍
	*****************************************/
	void clearChoiceBackground(COORD choice) {
		const SHORT x = choice.X, y = choice.Y;
		const size_t mapIndex = (size_t)y * mapWidth + (size_t)x;

		MovePos(2 + x * 4, y * 2 + 3);

		char numMap[8] = "  ";
		numMap[0] = '0' + mapCanvas[mapIndex];
		switch (mapCanvas[mapIndex]) {
		case 0:
			PutStringWithColor("  ", 255, 255, 255, 0, 0, 0);
			break;
		case 1:
			PutStringWithColor(numMap, 30, 144, 255, 0, 0, 0);
			break;
		case 2:
			PutStringWithColor(numMap, 0, 255, 127, 0, 0, 0);
			break;
		case 3:
			PutStringWithColor(numMap, 255, 48, 48, 0, 0, 0);
			break;
		case 4:
			PutStringWithColor(numMap, 72, 61, 139, 0, 0, 0);
			break;
		case 5:
			PutStringWithColor(numMap, 255, 105, 180, 0, 0, 0);
			break;
		case 6:
			PutStringWithColor(numMap, 148, 0, 211, 0, 0, 0);
			break;
		case 7:
			PutStringWithColor(numMap, 139, 0, 0, 0, 0, 0);
			break;
		case 8:
			PutStringWithColor(numMap, 139, 34, 82, 0, 0, 0);
			break;
		case 9:
			PutStringWithColor("⊙", 255, 0, 0, 0, 0, 0);
			break;
		case 10:
			PutStringWithColor("☆", 178, 34, 34, 0, 0, 0);
			break;
		case 11:
			PutStringWithColor("■", 255, 255, 255, 0, 0, 0);
			break;
		}
	}

	/****************************************
	Function:  checkChoice()
	Parameter: None(void)
	Return:    None(void)
	Description:
	检查输入和操作，并设置相关变量
	*****************************************/
	void checkChoice() {
		FlushInput();							// 刷新输入缓冲区
		pos = GetCursorPos();					// 获取鼠标坐标
		COORD hitLeftPos = GetCursorHitPos();	// 获取左键单击坐标
		COORD hitRightPos = GetCursorHitPos(2);	// 获取右键单击坐标
		key = GetKeyHit();						// 获取键盘输入
		operation = 0;							// 当前操作 (0无操作，1为挖开地块，2为标值旗帜，或者自己指定)

		// 检查键盘输入
		switch (key) {
		case VK_ESCAPE:
			// ESC键，将游戏运行状态置否以退出游戏
			gameFlag = false;
			break;

			// 上下左右键移动选中的坐标
		case VK_UP:
			if (posChoice.Y > 0)posChoice.Y--;
			break;
		case VK_RIGHT:
			if (posChoice.X < (SHORT)mapWidth - 1)posChoice.X++;
			break;
		case VK_DOWN:
			if (posChoice.Y < (SHORT)mapHeight - 1)posChoice.Y++;
			break;
		case VK_LEFT:
			if (posChoice.X > 0)posChoice.X--;
			break;

			// 回车和空格分别对应操作1和2
		case VK_RETURN:
			operation = 1;
			break;
		case VK_SPACE:
			operation = 2;
			break;
		}

		// 将鼠标控制台的坐标放缩至地图坐标
		const size_t mouseY = (size_t)(pos.Y + 1) / 2 - 2;
		const size_t mouseX = (size_t)(pos.X - 1) / 4;
		if (mouseY < mapHeight && mouseX < mapWidth) {
			// 若没有超边界，更新选择的坐标
			posChoice.X = (SHORT)mouseX;
			posChoice.Y = (SHORT)mouseY;
		}

		// 左键和右键分别对应操作1和2
		if (hitLeftPos.X == pos.X && hitLeftPos.Y == pos.Y) {
			operation = 1;
		}
		else if (hitRightPos.X == pos.X && hitRightPos.Y == pos.Y) {
			operation = 2;
		}
	}

	/****************************************
	Function:  initMap()
	Parameter: None(void)
	Return:    None(void)
	Description:
	这是你需要完成的函数
	通过posChoice变量判断操作，并操作mapArray数组和hidenMap数组，完成地图的初始化和雷区的初始化
	*****************************************/
	void initMap() {
		SHORT rad_X, rad_Y;//随机坐标
		UCHAR count;//数字标记

		srand(SHORT(time(0)));//生成随机数种子
		for (SHORT n = 0; n < BoomNum0; n++)//生成随机地雷
		{
			rad_X = rand() % mapWidth;
			rad_Y = rand() % mapHeight;
			if ((rad_X == posChoice.X && rad_Y == posChoice.Y)
				|| (hidenCanvas[rad_Y * mapWidth + rad_X] == 9)
				|| (rad_X == posChoice.X - 1 && rad_Y == posChoice.Y)
				|| (rad_X == posChoice.X + 1 && rad_Y == posChoice.Y)
				|| (rad_X == posChoice.X && rad_Y == posChoice.Y - 1)
				|| (rad_X == posChoice.X && rad_Y == posChoice.Y + 1)
				|| (rad_X == posChoice.X + 1 && rad_Y == posChoice.Y - 1)
				|| (rad_X == posChoice.X + 1 && rad_Y == posChoice.Y + 1)
				|| (rad_X == posChoice.X - 1 && rad_Y == posChoice.Y - 1)
				|| (rad_X == posChoice.X - 1 && rad_Y == posChoice.Y + 1))
				n--;
			else
				hidenCanvas[rad_Y * mapWidth + rad_X] = 9;
		}

		for (SHORT y = 0; y < mapHeight; y++)//生成每个方块的计数标记
			for (SHORT x = 0; x < mapWidth; x++)
			{
				if (hidenCanvas[y * mapWidth + x] != 9)
				{
					count = 0;
					for (SHORT dx = -1; dx <= 1; dx++)
						for (SHORT dy = -1; dy <= 1; dy++)
						{
							if (x + dx >= 0 && x + dx <= mapWidth - 1 && y + dy >= 0 && y + dy <= mapHeight - 1)
								if (hidenCanvas[(y + dy) * mapWidth + x + dx] == 9)
									count++;
						}
					hidenCanvas[y * mapWidth + x] = count;
				}
			}
	}

	/****************************************
	Function:  digBlock()
	Parameter: SHORT X, SHORT Y
	Return:    None(void)
	Description:
	这是你需要完成的函数
	通过参数X,Y判断操作，并操作mapArray数组，迭代挖开空白方块的八邻域，并判断游戏失败条件
	*****************************************/
	void digBlock(SHORT X, SHORT Y) {
		if (isFirst) {
			// 如果是第一步走，则先初始化地图，注意不要在落点设置一个地雷
			initMap();
			isFirst = false; // 将第一步设置为否
		}

		if (mapCanvas[Y * mapWidth + X] != 10)//如果该地块未被标记
		{
			if (hidenCanvas[Y * mapWidth + X] != 9)//如果挖开的不是地雷
			{
				mapCanvas[Y * mapWidth + X] = hidenCanvas[Y * mapWidth + X];//翻开当前地块
				if (hidenCanvas[Y * mapWidth + X] == 0)//递归翻开相邻地块
				{
					if ((X > 0) && mapCanvas[Y * mapWidth + X - 1] == 11)
						digBlock(X - 1, Y);
					if ((X < mapWidth - 1) && mapCanvas[Y * mapWidth + X + 1] == 11)
						digBlock(X + 1, Y);
					if ((Y > 0) && (mapCanvas[(Y - 1) * mapWidth + X] == 11))
						digBlock(X, Y - 1);
					if ((Y < mapHeight - 1) && (mapCanvas[(Y + 1) * mapWidth + X] == 11))
						digBlock(X, Y + 1);
					if ((X > 0) && (Y > 0) && mapCanvas[(Y - 1) * mapWidth + X - 1] == 11)
						digBlock(X - 1, Y - 1);
					if ((X < mapWidth - 1) && (Y > 0) && mapCanvas[(Y - 1) * mapWidth + X + 1] == 11)
						digBlock(X + 1, Y - 1);
					if ((X > 0) && (Y < mapHeight - 1) && (mapCanvas[(Y + 1) * mapWidth + X - 1] == 11))
						digBlock(X - 1, Y + 1);
					if ((X < mapWidth - 1) && (Y < mapHeight - 1) && (mapCanvas[(Y + 1) * mapWidth + X + 1] == 11))
						digBlock(X + 1, Y + 1);
				}
			}
			else//挖开的是地雷
			{
				for (SHORT i = 0; i < mapHeight; i++)
					for (SHORT j = 0; j < mapWidth; j++)
						mapCanvas[i * mapWidth + j] = hidenCanvas[i * mapWidth + j];
				gameOver = true;
			}
		}
	}


	/****************************************
	Function:  flagBlock()
	Parameter: SHORT X, SHORT Y
	Return:    None(void)
	Description:
	这是你需要完成的函数
	通过参数X,Y判断操作，并操作mapArray数组，完成对标记地雷和取消标记的操作
	*****************************************/
	void flagBlock(SHORT X, SHORT Y) {

		if (isFirst) {
			// 第一步不能标记地雷，直接执行翻开地块操作
			digBlock(X, Y);
			renderMap();	// 绘制地图
			isFirst = false; // 将第一步设置为否
		}
		else if ((mapCanvas[Y * mapWidth + X] == 11) && (leftNum > 0))//目标地块未被翻开未被标记且剩余雷数大于0
		{
			mapCanvas[Y * mapWidth + X] = 10;//标记
			leftNum--;
		}
		else if ((mapCanvas[Y * mapWidth + X] == 10) && (leftNum < BoomNum0))//目标地块已被标记且剩余雷数小于总数
		{
			mapCanvas[Y * mapWidth + X] = 11;//解除标记
			leftNum++;
		}
	}

	/****************************************
	Function:  checkWin()
	Parameter: None(void)
	Return:    None(void)
	Description:
	判断是否胜利，即地雷全部被标记，剩余地块全部被挖开
	*****************************************/
	void checkWin()
	{
		gameWin = true;
		for (SHORT i = 0; i < mapHeight; i++)
			for (SHORT j = 0; j < mapWidth; j++)
				if (mapCanvas[i * mapWidth + j] == 11)
				{
					gameWin = false;
					break;
				}
	}

	/****************************************
	Function:  Play()
	Parameter: None(void)
	Return:    None(void)
	Description:
	开始游戏
	*****************************************/
	void Play() {
		gameFlag = true;
		while (gameFlag) {
			checkChoice(); // 检查输入

			// 查看当前坐标是否需要更新背景
			if (posChoice.X != posChoiceOld.X || posChoice.Y != posChoiceOld.Y) {
				clearChoiceBackground(posChoiceOld);
				posChoiceOld = posChoice;
			}
			renderChoiceBackground(posChoice);

			// 在0,0处放置当前选择位置的字符串，注意结尾有空格留白，可以思考为什么要加这么多空格
			MovePos(0, 0);
			char str[128] = "";
			getTime();
			sprintf_s(str, "当前选择(%u, %u)   \t剩余地雷数:%hd   \n当前步数:%hd      \t用时:%hd:%02hd", posChoice.X, posChoice.Y, leftNum, stepNum, min, sec);
			PutString(str);

			if (gameOver)//游戏失败
			{
				MovePos(mapWidth, mapHeight);
				PutString("游戏失败 按下ESC返回主菜单");
			}

			if (gameWin)//游戏胜利
			{
				MovePos(mapWidth, mapHeight);
				PutString("游戏胜利 按下ESC返回主菜单");
			}

			if (!gameOver && !gameWin)
			{// 执行相应操作
				switch (operation) {
				case 1:
					// 翻开地块
					digBlock(posChoice.X, posChoice.Y);
					renderMap();	// 绘制地图
					stepNum++;		// 步数加一
					break;
				case 2:
					// 标记为地雷
					flagBlock(posChoice.X, posChoice.Y);
					renderMap();	// 绘制地图
					stepNum++;		// 步数加一
					break;
				}
			}
			// 以下内容不建议修改 处理每帧的事务
			Update();    // 更新操作到屏幕

			if (leftNum == 0 && !gameOver)//当标记出所有雷时检查游戏是否胜利
				checkWin();

			frame++;  // 渲染帧数自增
			clock_t elapsed = 25 - (clock() - tic); // 检查上一帧渲染时间，并计算与25的差值
			Sleep(elapsed > 0 ? elapsed : 0);	    // 若差值大于零，则休眠该差值的毫秒数，以确保每帧渲染不超过50帧
			tic = clock();						    // 更新上一次记录的时间
		}
	}

	/****************************************
	Function:  DestroyGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	结束游戏，回收动态申请的变量
	*****************************************/
	void DestroyGame() {
		delete[] mapCanvas;
		delete[] hidenCanvas;
	}
}