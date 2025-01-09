#pragma once

#include "start_screen.h"
#include "util.h"

#include<vector>

extern StartScreen start_screen;					// ��ʼ����
// extern People myself;							// ���û���Ϣ

class RecommendationsScreen :public Screen {
public:
	// �������
	void on_enter();
	// ���ƽ���
	void on_drow();
	// ����������
	void on_input(const ExMessage& msg);

	// �˳�����
	void on_exit();

private:
	std::vector<Button*> recommendations_friends_list;		// �Ƽ������б�
	std::vector<Button*> button_is_friend;					// ���/����Ӱ���
	Button button_back;										// ���ؼ�

	const int MAX_SHOW_SIZE = 9;							// ��ʾ����û���Ϣ
	const int SHOW_PEOPLE_X = 140;							// ��ʾ�û���ϢX����
	const int SHOW_IS_ADD_X = 1150;							// ��ʾ���/����Ӱ�ťX����
	const Vector2 SHOW_PEOPLE_SIZE = Vector2(1000, 70);		// ��ʾ�û���Ϣ��С
	const Vector2 SHOW_IS_ADD_SIZE = Vector2(120, 70);		// ��ʾ���/����Ӱ�ť��С

};