#pragma once

#include "start_screen.h"
#include "util.h"

extern StartScreen start_screen;					// ��ʼ����

class AddInterestsScreen :public Screen {
	// �������
	void on_enter() {
		// ��������
		InputBox(input_str, 50, L"��������ӵİ���", L"��Ӱ���");

		// �����û�����

	}
	// ���ƽ���
	void on_drow() {}
	// ����������
	void on_input(const ExMessage& msg) {
		on_exit();
	}

	// �˳�����
	void on_exit() {
		add_interest(input_str);
		MessageBox(nullptr, input_str, L"�������Ȥ", MB_OK || MB_ICONERROR);

		start_screen.switch_to(StartScreen::ScreenType::start);
	}

private:
	wchar_t input_str[11] = L"";					// �����ַ�����󳤶�Ϊ10
};