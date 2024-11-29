#pragma once

#include "screen.h"
#include "button.h"

extern Screen* friends_screen;
extern Screen* search_friend_screen;
extern Screen* add_interests_screen;
extern Screen* recommendations_screen;

class StartScreen : public Screen{
public:
	StartScreen() = default;
	~StartScreen() = default;

	enum class ScreenType {
		start,
		friends,
		search_friend,
		add_interests,
		recommendations
	};

	// 进入界面
	void on_enter();
	// 绘制界面
	void on_drow();
	// 鼠标键盘输入
	void on_input(const ExMessage& msg);

	void set_current_screen(Screen* screen) {
		current_screen = screen;
		current_screen->on_enter();
	}

	void switch_to(ScreenType type);

private:
	Screen* current_screen = nullptr;

	Button search_friend;						// 查找好友按钮
	Button friends;								// 好友列表
	Button add_interests;						// 添加爱好
	Button recommendations;						// 查看推荐

};