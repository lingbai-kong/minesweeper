/****************************************
DifficultyMenu.cpp
Author: Student
Date: 2019/12/15
Description:
�����������ε�ͼ�ѶȲ˵�����Ⱦ/����ģ�飬��DiffucultyMenu�����ռ��ֹͬ����Ⱦ
*****************************************/
#include "DifficultyMenu.h"
int MapHeight = 0;				   // ��ͼ�߶�
int MapWidth = 0;				   // ��ͼ���
int BoomNum = 0;				   // ��������

namespace DifficultyMenu {
	// �������������ռ�
	using namespace Graphic;
	using namespace Controller;

	size_t frame = 0;                  // ��������Ⱦ��֡�� 
	COORD pos = { 0 }, hitPos = { 0 }; // ������굱ǰ�������������������
	int choice = 0, oldChoice = 0;     // ����ѡ�еĲ˵���
	bool isChosen = false;             // �����Ƿ�����ѡ��
	char key = '\0';                   // ���嵱ǰ���̵İ���
	clock_t tic = clock();             // ���������һ֡��Ⱦ��ʱ��
	// ��������¼ӵı�������������·���Ԥ�ñ���������

	/****************************************
	Function:  renderMenu()
	Parameter: None(void)
	Return:    None(void)
	Description:
	�������Ҵ�ӡ�������ز˵�ѡ��
	*****************************************/
	void renderMenu() {
		ClearScreen();  // ����
		MovePos(17, 2); // �ƶ����굽 17,2
		PutString("�Ѷ�"); // ������������һ��string
		MovePos(17, 4);
		PutString("��");
		MovePos(17, 6);
		PutString("��ͨ");
		MovePos(17, 8);
		PutString("����");
		MovePos(16, 10);
		PutString("�Զ���");
		Update();
	}

	/****************************************
	Function:  InitMenu()
	Parameter: None(void)
	Return:    None(void)
	Description:
	��ʼ���˵���ͬʱ��ʼ��ͼ�ο�ܺͿ��������
	*****************************************/
	void InitMenu() {
		renderMenu();        // ���Ʋ˵�
	}

	/****************************************
	Function:  randerChoiceBackground(int choice)
	Parameter: int choice
	Return:    None(void)
	Description:
	����ǰѡ�еĲ˵���(int choice)������Ⱦһ��������ʧ�İ�ɫ
	*****************************************/
	void randerChoiceBackground(int choice) {
		size_t y = 0;  // ���嵱ǰѡ�еĲ˵����ʵ��y����
		const BYTE alpha = 255 - (BYTE)((frame % 50) * 5);  // ���屳����ɫ��ǰ����ɫֵ��ͨ������Ⱦ��֡���������㣨�˴�Ҳ���Ըĳ�ʹ��ʱ�䣩
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
			MovePos((SHORT)x, (SHORT)y); // �������Ƶ�Ŀ���
			ModColor(2, 255, 255, 255, alpha, alpha, alpha); // �޸ı���ɫ
		}
		Update();  // ���½���
	}

	/****************************************
	Function:  clearChoiceBackground(int choice)
	Parameter: int choice
	Return:    None(void)
	Description:
	���ϴ�ѡ�еĲ˵���(int choice)�����ָ�Ϊ��ɫ�����ݴ��º���һ������һ�£�����������
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
	������/������룬������ѡ�еĲ˵���
	*****************************************/
	void checkChoice() {
		FlushInput();           // ˢ�����뻺����
		pos = GetCursorPos();   // ��ȡ�������
		key = GetKeyHit();		// ��ȡ��������
		hitPos = GetCursorHitPos();  // ��ȡ��굥������
		isChosen = false;		// ����ѡ��״̬

		// ������λ�ã�����ѡ����
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

		// �����̰���������ѡ����
		switch (key) {
		case VK_UP:
			// �Ϸ����
			if (choice > 0)choice--;
			break;
		case VK_DOWN:
			// �·����
			if (choice < 3)choice++;
			break;
		case VK_RETURN:
			// �س�������ѡ��
			isChosen = true;
			break;
		}

		// ����������λ���Ƿ��ڲ˵����У�����ǣ�����ѡ��
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
	��ѭ���������˳���һֱ��Ⱦ��ȥ
	*****************************************/
	void WaitChoice() {
		bool runFlag = true;
		while (runFlag) {
			checkChoice();  // �������

			if (choice != oldChoice) {
				// ���µ�ѡ�����ѡ��һ�£�����ѡ��ı������
				clearChoiceBackground(oldChoice);
				oldChoice = choice;
			}
			randerChoiceBackground(choice); // ����ѡ����ı���

			// ���ѡ�в˵���ִ�в���
			if (isChosen) {
				switch (choice) {
				case 0:
					// ��
					MapHeight = 12;
					MapWidth = 12;
					BoomNum = 10;
					InitGraphic(40, 22); // ��ʼ���µĴ��ڴ�СΪ44,25
					InitController();    // ��ʼ��������

					GameEngine::InitGame();
					GameEngine::Play();
					GameEngine::DestroyGame();
					runFlag = false;
					break;
				case 1:
					// ��ͨ
					MapHeight = 20;
					MapWidth = 20;
					BoomNum = 30;
					InitGraphic(65, 30); // ��ʼ���µĴ��ڴ�СΪ65,37
					InitController();    // ��ʼ��������

					GameEngine::InitGame();
					GameEngine::Play();
					GameEngine::DestroyGame();
					runFlag = false;
					break;
				case 2:
					// ����
					MapHeight = 30;
					MapWidth = 50;
					BoomNum = 99;
					InitGraphic(160, 40); // ��ʼ���µĴ��ڴ�СΪ121,37
					InitController();    // ��ʼ��������

					GameEngine::InitGame();
					GameEngine::Play();
					GameEngine::DestroyGame();
					runFlag = false;
					break;
				case 3:
					// �Զ���
					//����ϵͳ��ɫ
					system("color 07");

					// ��ʾ���
					HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);  // ��ȡ��׼������
					CONSOLE_CURSOR_INFO cci;
					cci.bVisible = 1;
					cci.dwSize = 1;
					SetConsoleCursorInfo(hStdOut, &cci);

					//����
					system("cls");

					//�Զ�������
					printf("�������ͼ�߶ȣ�");
					scanf_s("%d", &MapHeight);
					printf("�������ͼ��ȣ�");
					scanf_s("%d", &MapWidth);
					printf("���������������");
					scanf_s("%d", &BoomNum);

					MapWidth = 2 * MapWidth;
					//�Ϸ�������
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

					InitGraphic(w, h); // ��ʼ���µĴ��ڴ�С
					InitController();    // ��ʼ��������

					GameEngine::InitGame();
					GameEngine::Play();
					GameEngine::DestroyGame();
					runFlag = false;
					break;
				}
			}

			// ����ÿ֡������
			frame++;  // ��Ⱦ֡������
			clock_t elapsed = 25 - (clock() - tic); // �����һ֡��Ⱦʱ�䣬��������25�Ĳ�ֵ
			Sleep(elapsed > 0 ? elapsed : 0);       // ����ֵ�����㣬�����߸ò�ֵ�ĺ���������ȷ��ÿ֡��Ⱦ������50֡
			tic = clock();							// ������һ�μ�¼��ʱ��
		}
	}
}