#pragma once

#include<graphics.h>

// 父类界面
class Screen {
public:
	Screen() = default;
	~Screen() = default;

	// 进入界面
	virtual void on_enter() {}
	// 绘制界面
	virtual void on_drow() {}
	// 鼠标键盘输入
	virtual void on_input(const ExMessage& msg) {}

	bool get_is_back() {
		return is_back;
	}

private:
	bool is_back = false;				// 返回上一个界面

};
