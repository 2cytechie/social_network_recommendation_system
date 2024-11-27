#pragma once

#include "screen.h"
#include "button.h"

class StartScreen : public Screen{
public:
	StartScreen() = default;
	~StartScreen() = default;

	// �������
	virtual void on_enter() {
		search_friend.set_data(_T("��������"));
		search_friend.set_pos()
	}
	// ���½���
	virtual void on_update(double delta) {}
	// ���ƽ���
	virtual void on_drow() {}
	// ����������
	virtual void on_input() {}
	// �˳�����
	virtual void on_exit() {}


private:
	Button search_friend;						// ���Һ��Ѱ�ť
	Button friends;								// �����б�
	Button add_interests;						// ��Ӱ���

};