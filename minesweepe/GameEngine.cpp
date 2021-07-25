/****************************************
GameEngine.cpp
Author: Root
Date: 2019/12/09
Description:
�����������γ�����Ϸģ�飬��GameEngine�����ռ��ֹͬ����Ⱦ��������Ҫ��Ҫ�޸ĵ��ļ�
*****************************************/
#include "GameEngine.h"

//��չ��ȫ�ֱ���
extern int MapHeight;
extern int MapWidth;
extern int BoomNum;

namespace GameEngine {
	// �������������ռ�
	using namespace Graphic;
	using namespace Controller;

	size_t mapWidth = 0, mapHeight = 0;				 // ��ͼ��Ⱥ͸߶�
	UCHAR* mapCanvas = nullptr;						 // ��ͼ����ָ�룬�����������벻Ҫֱ�ӳ��Բ������ָ��
	COORD pos = { 0 }, posOld = { 0 };				 // ����λ��
	COORD posChoice = { 0 }, posChoiceOld = { 0 };	 // ѡ�е�ͼ�����λ��
	char key = '\0';								 // ���̵İ���
	bool gameFlag = false;							 // ��Ϸ����״̬
	size_t frame = 0;								 // ����Ⱦ֡��
	clock_t tic = clock();							 // ��Ϸ��ʼʱ��
	int operation = 0;								 // ִ�еĲ���
	bool isFirst = true;							 // �Ƿ�Ϊ��һ��
	// ��������¼ӵı�������������·���Ԥ�ñ���������
	UCHAR* hidenCanvas = nullptr;
	SHORT leftNum = BoomNum;						 // ʣ�������
	SHORT stepNum = 0;								 // ���߲���
	bool gameOver = false;							 // �Ƿ���Ϸʧ��
	bool gameWin = false;							 // �Ƿ���Ϸʤ��
	int min = 0;									 // ��Ϸʱ�䣨���ӣ�
	int minOld = 0;									 // ��һ����Ϸʱ�䣨���ӣ�
	int sec = 0;									 // ��Ϸʱ�䣨�룩
	time_t timeOld = 0;								 // ��Ϸ��ʼʱ��ϵͳʱ��

	/****************************************
	Function:  renderMap()
	Parameter: None(void)
	Return:    None(void)
	Description:
	���Ƶ�ǰ��ͼ
	*****************************************/
	void renderMap() {
		// ���п�ʼ����
		for (size_t i = 0; i <= mapHeight + 1; i++) {
			// �����У����Ʊ߽�
			for (size_t j = 0; j < mapWidth / 2; j++) {
				// �ƶ���ȷ�е����꣬���Ʒ���ı߽�
				MovePos((SHORT)j * 6, (SHORT)i + 3);
				if (i < mapHeight){
					if (i == 0) {
						PutString("/��\\  ");
					}
					else if (i % 2 == 0) {
						PutString("/��\\");
						const size_t mapIndex = (i-1) * mapWidth + 2 * j + (i - 1) % 2; // ȷ����ͼ������±�
						char numMap[8] = " ";							// ȷ�������ַ���
						numMap[1] = '0' + mapCanvas[mapIndex];			// ��mapCanvas[mapIndex]Ϊ1��8ʱ������ת�����ַ���
						switch (mapCanvas[mapIndex]) {
						case 0:
							//0��ʱ����ÿհ�
							PutString("  ");
							break;
						case 1:
							//��1��ʼ�������� ����ɫ
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
							//9Ϊ����
							PutStringWithColor("��", 255, 0, 0, 0, 0, 0);
							break;
						case 10:
							//10Ϊ���ױ��
							PutStringWithColor("��", 178, 34, 34, 0, 0, 0);
							break;
						case 11:
							//11Ϊδ֪���
							PutStringWithColor("��", 255, 255, 255, 0, 0, 0);
							break;
						}
						if(j==mapWidth/2-1)
							PutString("/");
					}
					else if (i % 2 != 0){
						PutString("\\");
						const size_t mapIndex = (i-1) * mapWidth + 2 * j + (i - 1) % 2; // ȷ����ͼ������±�
						char numMap[8] = "  ";							// ȷ�������ַ���
						numMap[1] = '0' + mapCanvas[mapIndex];			// ��mapCanvas[mapIndex]Ϊ1��8ʱ������ת�����ַ���
						switch (mapCanvas[mapIndex]) {
						case 0:
							//0��ʱ����ÿհ�
							PutString("  ");
							break;
						case 1:
							//��1��ʼ�������� ����ɫ
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
							//9Ϊ����
							PutStringWithColor("��", 255, 0, 0, 0, 0, 0);
							break;
						case 10:
							//10Ϊ���ױ��
							PutStringWithColor("��", 178, 34, 34, 0, 0, 0);
							break;
						case 11:
							//11Ϊδ֪���
							PutStringWithColor("��", 255, 255, 255, 0, 0, 0);
							break;
						}
						if (j < mapWidth / 2-1 )
							PutString("/��");
						else
							PutString("/��\\");
					}
				}
				else if(i == mapHeight){
					if (i % 2 == 0) {
						if (j == 0) {
							PutString(" ��\\");
							const size_t mapIndex = (i - 1) * mapWidth + 2 * j + (i - 1) % 2; // ȷ����ͼ������±�
							char numMap[8] = "  ";							// ȷ�������ַ���
							numMap[1] = '0' + mapCanvas[mapIndex];			// ��mapCanvas[mapIndex]Ϊ1��8ʱ������ת�����ַ���
							switch (mapCanvas[mapIndex]) {
							case 0:
								//0��ʱ����ÿհ�
								PutString("  ");
								break;
							case 1:
								//��1��ʼ�������� ����ɫ
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
								//9Ϊ����
								PutStringWithColor("��", 255, 0, 0, 0, 0, 0);
								break;
							case 10:
								//10Ϊ���ױ��
								PutStringWithColor("��", 178, 34, 34, 0, 0, 0);
								break;
							case 11:
								//11Ϊδ֪���
								PutStringWithColor("��", 255, 255, 255, 0, 0, 0);
								break;
							}
						}
						else  {
							PutString("/��\\");
							const size_t mapIndex = (i - 1) * mapWidth + 2 * j + (i - 1) % 2; // ȷ����ͼ������±�
							char numMap[8] = "  ";							// ȷ�������ַ���
							numMap[1] = '0' + mapCanvas[mapIndex];			// ��mapCanvas[mapIndex]Ϊ1��8ʱ������ת�����ַ���
							switch (mapCanvas[mapIndex]) {
							case 0:
								//0��ʱ����ÿհ�
								PutString("  ");
								break;
							case 1:
								//��1��ʼ�������� ����ɫ
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
								//9Ϊ����
								PutStringWithColor("��", 255, 0, 0, 0, 0, 0);
								break;
							case 10:
								//10Ϊ���ױ��
								PutStringWithColor("��", 178, 34, 34, 0, 0, 0);
								break;
							case 11:
								//11Ϊδ֪���
								PutStringWithColor("��", 255, 255, 255, 0, 0, 0);
								break;
							}
							if (j == mapWidth / 2 -1)
								PutString("/    ");
						}
					}
					else {
						if (j < mapWidth / 2) {
							PutString("\\");
							const size_t mapIndex = (i - 1) * mapWidth + 2 * j + (i - 1) % 2; // ȷ����ͼ������±�
							char numMap[8] = "  ";							// ȷ�������ַ���
							numMap[1] = '0' + mapCanvas[mapIndex];			// ��mapCanvas[mapIndex]Ϊ1��8ʱ������ת�����ַ���
							switch (mapCanvas[mapIndex]) {
							case 0:
								//0��ʱ����ÿհ�
								PutString("  ");
								break;
							case 1:
								//��1��ʼ�������� ����ɫ
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
								//9Ϊ����
								PutStringWithColor("��", 255, 0, 0, 0, 0, 0);
								break;
							case 10:
								//10Ϊ���ױ��
								PutStringWithColor("��", 178, 34, 34, 0, 0, 0);
								break;
							case 11:
								//11Ϊδ֪���
								PutStringWithColor("��", 255, 255, 255, 0, 0, 0);
								break;
							}
							PutString("/��");
						}
						else {
							PutString("\\");
							const size_t mapIndex = (i - 1) * mapWidth + 2 * j + (i - 1) % 2; // ȷ����ͼ������±�
							char numMap[8] = "  ";							// ȷ�������ַ���
							numMap[1] = '0' + mapCanvas[mapIndex];			// ��mapCanvas[mapIndex]Ϊ1��8ʱ������ת�����ַ���
							switch (mapCanvas[mapIndex]) {
							case 0:
								//0��ʱ����ÿհ�
								PutString("  ");
								break;
							case 1:
								//��1��ʼ�������� ����ɫ
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
								//9Ϊ����
								PutStringWithColor("��", 255, 0, 0, 0, 0, 0);
								break;
							case 10:
								//10Ϊ���ױ��
								PutStringWithColor("��", 178, 34, 34, 0, 0, 0);
								break;
							case 11:
								//11Ϊδ֪���
								PutStringWithColor("��", 255, 255, 255, 0, 0, 0);
								break;
							}
							PutString("/ ");
						}
					}
				}
				else
				{
					if (i % 2 == 0) {
						if (j == 0) {
							PutString(" ��   ");
						}
						else if (j < mapWidth / 2) {
							PutString(" ��   ");
						}
						else {
							PutString(" ��  ");
						}
					}
					else {
						if (j < mapWidth / 2) {
							PutString("    ��");
						}
						else {
							PutString("     ");
						}
					}
				}
			}
		}
		Update(); // ����ͼ���µ���Ļ
	}
	/****************************************
	Function:  getTime()
	Parameter: None(void)
	Return:    None(void)
	Description:
	�ڵ�һ���ڿ��ؿ���ʱʹ�÷���һ
	*****************************************/
	void getTime()
	{
		if (isFirst)
		{
			timeOld = time(0);
			minOld = -1;
			min = 0;
			sec = 0;
		}
		else if (!gameOver && !gameWin)
		{
			sec = (time(0) - timeOld) % 60;
			if (sec == 0)
				if (minOld == min)
					min++;
			if (sec != 0)
				minOld = min;
		}
	}

	/****************************************
	Function:  InitGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	��ʼ����Ϸ
	*****************************************/
	void InitGame() {
		ClearScreen();								 // ����

		//��ʼ����������
		isFirst = true;
		gameOver = false;
		gameWin = false;
		leftNum = BoomNum;
		stepNum = 0;

		mapWidth = MapWidth; mapHeight = MapHeight;	  // ���ÿ��
		mapCanvas = new UCHAR[mapWidth * mapHeight];  // ��ʼ����������
		hidenCanvas = new UCHAR[mapWidth * mapHeight];// ��ʼ����������

		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				if (((i % 2 == 0) && (j % 2 == 0)) || ((i % 2 != 0) && (j % 2 != 0)))
					mapCanvas[i * mapWidth + j] = 11;//(i * mapWidth + j) % 12; // ���µ�ͼ���飬���γ��ָ��������ַ�
				else
					mapCanvas[i * mapWidth + j] = 0;
				hidenCanvas[i * mapWidth + j] = 0;
			}
		}
		renderMap();	// ���Ƶ�ͼ
	}

	/****************************************
	Function:  renderChoiceBackground(COORD choice)
	Parameter: COORD choice
	Return:    None(void)
	Description:
	����ѡ�еĵؿ�ı���
	*****************************************/
	void renderChoiceBackground(COORD choice) {
		const SHORT x = choice.X, y = choice.Y;
		const BYTE alpha = 255 - (BYTE)((frame % 50) * 5);        // ���屳����ɫ��ǰ����ɫֵ��ͨ������Ⱦ��֡���������㣨�˴�Ҳ���Ըĳ�ʹ��ʱ�䣩
		const size_t mapIndex = y * mapWidth + x; // ȷ����ͼ�±�

		MovePos(1 + x * 3, y + 3);

		// ��������ͬrenderMap�л��Ƶ��ײ�����ͬ������������
		char numMap[8] = "  ";
		numMap[1] = '0' + mapCanvas[mapIndex];
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
			PutStringWithColor("��", 255, 0, 0, alpha, alpha, alpha);
			break;
		case 10:
			PutStringWithColor("��", 178, 34, 34, alpha, alpha, alpha);
			break;
		case 11:
			PutStringWithColor("��", 255, 255, 255, alpha, alpha, alpha);
			break;
		}
	}

	/****************************************
	Function:  clearChoiceBackground(COORD choice)
	Parameter: COORD choice
	Return:    None(void)
	Description:
	���choice��ָʾλ�õı���������ͬ�ϣ�����������
	*****************************************/
	void clearChoiceBackground(COORD choice) {
		const SHORT x = choice.X, y = choice.Y;
		const size_t mapIndex = y * mapWidth + x ;
		//const size_t mapIndex = y * mapWidth + 2 * x + y % 2;

		MovePos(1 + x * 3, y + 3);

		char numMap[8] = "  ";
		numMap[1] = '0' + mapCanvas[mapIndex];
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
			PutStringWithColor("��", 255, 0, 0, 0, 0, 0);
			break;
		case 10:
			PutStringWithColor("��", 178, 34, 34, 0, 0, 0);
			break;
		case 11:
			PutStringWithColor("��", 255, 255, 255, 0, 0, 0);
			break;
		}
	}

	/****************************************
	Function:  checkChoice()
	Parameter: None(void)
	Return:    None(void)
	Description:
	�������Ͳ�������������ر���
	*****************************************/
	void checkChoice() {
		FlushInput();							// ˢ�����뻺����
		pos = GetCursorPos();					// ��ȡ�������
		COORD hitLeftPos = GetCursorHitPos();	// ��ȡ�����������
		COORD hitRightPos = GetCursorHitPos(2);	// ��ȡ�Ҽ���������
		key = GetKeyHit();						// ��ȡ��������
		operation = 0;							// ��ǰ���� (0�޲�����1Ϊ�ڿ��ؿ飬2Ϊ��ֵ���ģ������Լ�ָ��)

		// ����������
		switch (key) {
		case VK_ESCAPE:
			// ESC��������Ϸ����״̬�÷����˳���Ϸ
			gameFlag = false;
			break;

			// �������Ҽ��ƶ�ѡ�е�����
		case VK_UP:
			if (posChoice.Y > 1)posChoice.Y-=2;
			break;
		case VK_RIGHT:
			if ((posChoice.X < (SHORT)mapWidth - 1)&&(posChoice.Y > 0))posChoice.X++, posChoice.Y--;
			break;
		case VK_DOWN:
			if (posChoice.Y <= (SHORT)mapHeight - 2)posChoice.Y+=2;
			break;
		case VK_LEFT:
			if ((posChoice.X > 0)&&(posChoice.Y > 0))posChoice.X--,posChoice.Y--;
			break;

			// �س��Ϳո�ֱ��Ӧ����1��2
		case VK_RETURN:
			operation = 1;
			break;
		case VK_SPACE:
			operation = 2;
			break;
		}

		// ��������̨�������������ͼ����
		const size_t mouseY = (size_t)(pos.Y - 3);
		const size_t mouseX = (size_t)(pos.X - 1) / 3;
		if (mouseY < mapHeight && mouseX < mapWidth) {
			// ��û�г��߽磬����ѡ�������
			posChoice.X = (SHORT)mouseX;
			posChoice.Y = (SHORT)mouseY;
		}

		if (posChoice.X % 2 != posChoice.Y % 2)
		{
			if ((posChoice.Y % 2 == 0)&&(posChoice.Y<mapHeight-1))
				posChoice.Y++;
			else
				posChoice.Y--;
		}
		// ������Ҽ��ֱ��Ӧ����1��2
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
	��������Ҫ��ɵĺ���
	ͨ��posChoice�����жϲ�����������mapArray�����hidenMap���飬��ɵ�ͼ�ĳ�ʼ���������ĳ�ʼ��
	*****************************************/
	void initMap() {
		SHORT rad_X, rad_Y;//�������
		UCHAR count;//���ֱ��

		srand(SHORT(time(0)));//�������������
		for (SHORT n = 0; n < BoomNum; n++)//�����������
		{
			rad_X = rand() % mapWidth;
			rad_Y = rand() % mapHeight;
			if (((rad_X == posChoice.X && rad_Y == posChoice.Y)
				|| (hidenCanvas[rad_Y * mapWidth + rad_X] == 9)
				|| (rad_X == posChoice.X && rad_Y == posChoice.Y - 2)
				|| (rad_X == posChoice.X && rad_Y == posChoice.Y + 2)
				|| (rad_X == posChoice.X + 1 && rad_Y == posChoice.Y - 1)
				|| (rad_X == posChoice.X + 1 && rad_Y == posChoice.Y + 1)
				|| (rad_X == posChoice.X - 1 && rad_Y == posChoice.Y - 1)
				|| (rad_X == posChoice.X - 1 && rad_Y == posChoice.Y + 1))
				|| !(((rad_X % 2 == 0) && (rad_Y % 2 == 0)) || ((rad_X % 2 != 0) && (rad_Y % 2 != 0))))
				n--;
			else
				hidenCanvas[rad_Y * mapWidth + rad_X] = 9;
		}

		for (SHORT y = 0; y < mapHeight; y++)//����ÿ������ļ������
			for (SHORT x = 0; x < mapWidth; x++)
			{
				if ((hidenCanvas[y * mapWidth + x] != 9)
					&&(((x % 2 == 0) && (y % 2 == 0)) || ((x % 2 != 0) && (y % 2 != 0))))
				{
					count = 0;
					for (SHORT dx = -1; dx <= 1; dx+=2)
						for (SHORT dy = -1; dy <= 1; dy+=2)
						{
							if (x + dx >= 0 && x + dx <= mapWidth - 1 && y + dy >= 0 && y + dy <= mapHeight - 1)
								if (hidenCanvas[(y + dy) * mapWidth + x + dx] == 9)
									count++;
						}
					for (SHORT dy = -2; dy <= 2; dy += 4)
					{
						if (x >= 0 && x <= mapWidth - 1 && y + dy >= 0 && y + dy <= mapHeight - 1)
							if (hidenCanvas[(y + dy) * mapWidth + x] == 9)
								count++;
					}

					hidenCanvas[y * mapWidth + x] = count;
				}
				if (!(((x % 2 == 0) && (y % 2 == 0)) || ((x % 2 != 0) && (y % 2 != 0))))
					hidenCanvas[y * mapWidth + x] = 0;
			}
	}

	/****************************************
	Function:  digBlock()
	Parameter: SHORT X, SHORT Y
	Return:    None(void)
	Description:
	��������Ҫ��ɵĺ���
	ͨ������X,Y�жϲ�����������mapArray���飬�����ڿ��հ׷���İ����򣬲��ж���Ϸʧ������
	*****************************************/
	void digBlock(SHORT X, SHORT Y) {
		if (isFirst) {
			// ����ǵ�һ���ߣ����ȳ�ʼ����ͼ��ע�ⲻҪ���������һ������
			initMap();
			isFirst = false; // ����һ������Ϊ��
		}

		if ((((X % 2 == 0) && (Y % 2 == 0)) || ((X % 2 != 0) && (Y % 2 != 0)))
			&&(mapCanvas[Y * mapWidth + X] != 10))//����õؿ�δ�����
		{
			if (hidenCanvas[Y * mapWidth + X] != 9)//����ڿ��Ĳ��ǵ���
			{
				mapCanvas[Y * mapWidth + X] = hidenCanvas[Y  * mapWidth + X];//������ǰ�ؿ�
				if (hidenCanvas[Y * mapWidth + X] == 0)//�ݹ鷭�����ڵؿ�
				{
					if ((Y > 1) && (mapCanvas[(Y - 2) * mapWidth + X] == 11))
						digBlock(X, Y - 2);
					if ((Y < mapHeight - 2) && (mapCanvas[(Y + 2) * mapWidth + X] == 11))
						digBlock(X, Y + 2);
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
			else//�ڿ����ǵ���
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
	��������Ҫ��ɵĺ���
	ͨ������X,Y�жϲ�����������mapArray���飬��ɶԱ�ǵ��׺�ȡ����ǵĲ���
	*****************************************/
	void flagBlock(SHORT X, SHORT Y) {

		if (isFirst) {
			// ��һ�����ܱ�ǵ��ף�ֱ��ִ�з����ؿ����
			digBlock(X, Y);
			renderMap();	// ���Ƶ�ͼ
			isFirst = false; // ����һ������Ϊ��
		}
		else if ((mapCanvas[Y * mapWidth + X] == 11) && (leftNum > 0))//Ŀ��ؿ�δ������δ�������ʣ����������0
		{
			mapCanvas[Y * mapWidth + X] = 10;//���
			leftNum--;
		}
		else if ((mapCanvas[Y * mapWidth + X] == 10) && (leftNum < BoomNum))//Ŀ��ؿ��ѱ������ʣ������С������
		{
			mapCanvas[Y * mapWidth + X] = 11;//������
			leftNum++;
		}
	}

	/****************************************
	Function:  checkWin()
	Parameter: None(void)
	Return:    None(void)
	Description:
	�ж��Ƿ�ʤ����������ȫ������ǣ�ʣ��ؿ�ȫ�����ڿ�
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
	��ʼ��Ϸ
	*****************************************/
	void Play() {
		gameFlag = true;
		while (gameFlag) {
			checkChoice(); // �������

			// �鿴��ǰ�����Ƿ���Ҫ���±���
			if (posChoice.X != posChoiceOld.X || posChoice.Y != posChoiceOld.Y) {
				clearChoiceBackground(posChoiceOld);
				posChoiceOld = posChoice;
			}
			renderChoiceBackground(posChoice);

			// ��0,0�����õ�ǰѡ��λ�õ��ַ�����ע���β�пո����ף�����˼��ΪʲôҪ����ô��ո�
			MovePos(0, 0);
			char str[128] = "";
			getTime();
			sprintf_s(str, "��ǰѡ��(%u, %u)   \tʣ�������:%hd   \n��ǰ����:%hd      \t��ʱ:%hd:%02hd", posChoice.X, posChoice.Y, leftNum, stepNum, min, sec);
			PutString(str);
	
			if (gameOver)//��Ϸʧ��
			{
				MovePos(mapWidth, mapHeight/2);
				PutString("��Ϸʧ�� ����ESC�������˵�");
			}

			if (gameWin)//��Ϸʤ��
			{
				MovePos(mapWidth, mapHeight/2);
				PutString("��Ϸʤ�� ����ESC�������˵�");
			}

			if (!gameOver && !gameWin)
			{// ִ����Ӧ����
				switch (operation) {
				case 1:
					// �����ؿ�
					digBlock(posChoice.X, posChoice.Y);
					renderMap();	// ���Ƶ�ͼ
					stepNum++;		// ������һ
					break;
				case 2:
					// ���Ϊ����
					flagBlock(posChoice.X, posChoice.Y);
					renderMap();	// ���Ƶ�ͼ
					stepNum++;		// ������һ
					break;
				}
			}
			// �������ݲ������޸� ����ÿ֡������
			Update();    // ���²�������Ļ

			if (leftNum == 0 && !gameOver)//����ǳ�ʮ����ʱ�����Ϸ�Ƿ�ʤ��
				checkWin();

			frame++;  // ��Ⱦ֡������
			clock_t elapsed = 25 - (clock() - tic); // �����һ֡��Ⱦʱ�䣬��������25�Ĳ�ֵ
			Sleep(elapsed > 0 ? elapsed : 0);	    // ����ֵ�����㣬�����߸ò�ֵ�ĺ���������ȷ��ÿ֡��Ⱦ������50֡
			tic = clock();						    // ������һ�μ�¼��ʱ��
		}
	}

	/****************************************
	Function:  DestroyGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	������Ϸ�����ն�̬����ı���
	*****************************************/
	void DestroyGame() {
		delete[] mapCanvas;
		delete[] hidenCanvas;
	}
}