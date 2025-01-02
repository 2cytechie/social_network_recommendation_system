#pragma once

#include "start_screen.h"
#include "util.h"

extern StartScreen start_screen;					// 开始界面

class AddInterestsScreen :public Screen {
	// 进入界面
	void on_enter() {
		// 弹窗输入
		InputBox(input_str, 50, L"请输入添加的爱好", L"添加爱好");

		// 更新用户爱好

	}
	// 绘制界面
	void on_drow() {}
	// 鼠标键盘输入
	void on_input(const ExMessage& msg) {
		on_exit();
	}

	// 退出界面
	void on_exit() {
		add_interest(input_str);
		MessageBox(nullptr, input_str, L"已添加兴趣", MB_OK || MB_ICONERROR);

		start_screen.switch_to(StartScreen::ScreenType::start);
	}

private:
	wchar_t input_str[11] = L"";					// 输入字符，最大长度为10
};