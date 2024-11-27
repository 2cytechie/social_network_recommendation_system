#pragma once

#include<graphics.h>

// �������
class Screen {
public:
	Screen() = default;
	~Screen() = default;

	// �������
	virtual void on_enter() {}
	// ���½���
	virtual void on_update(double delta) {}
	// ���ƽ���
	virtual void on_drow() {}
	// ����������
	virtual void on_input() {}
	// �˳�����
	virtual void on_exit() {}

};
