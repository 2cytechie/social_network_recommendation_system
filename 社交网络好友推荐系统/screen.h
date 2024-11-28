#pragma once

#include<graphics.h>

// �������
class Screen {
public:
	Screen() = default;
	~Screen() = default;

	// �������
	virtual void on_enter() {}
	// ���ƽ���
	virtual void on_drow() {}
	// ����������
	virtual void on_input(const ExMessage& msg) {}

	bool get_is_back() {
		return is_back;
	}

private:
	bool is_back = false;				// ������һ������

};
