/****************************************
ModeMenu.cpp
Author: Student
Date: 2019/12/15
Description:
������ģʽ�˵�����Ⱦ/����ģ�飬��ModeMenu�����ռ��ֹͬ����Ⱦ
*****************************************/
#include "ModeMenu.h"

namespace ModeMenu {
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
		PutString("ģʽ"); // ������������һ��string
		MovePos(17, 4);
		PutString("����");
		MovePos(17, 6);
		PutString("Ť��");
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
					// ����
					DifficultyMenu0::InitMenu();
					DifficultyMenu0::WaitChoice();
					InitGraphic(44, 25); // ��ʼ���µĴ��ڴ�СΪ44,25
					InitController();    // ��ʼ��������
					runFlag = false;
					break;
				case 1:
					// Ť��
					DifficultyMenu::InitMenu();
					DifficultyMenu::WaitChoice();
					InitGraphic(44, 25); // ��ʼ���µĴ��ڴ�СΪ44,25
					InitController();    // ��ʼ��������
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