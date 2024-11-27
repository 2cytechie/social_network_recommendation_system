#pragma once

#include "screen.h"
#include "button.h"

class StartScreen : public Screen{
public:
	StartScreen() = default;
	~StartScreen() = default;

	// 进入界面
	virtual void on_enter() {
		search_friend.set_data(_T("搜索好友"));
		search_friend.set_pos()
	}
	// 更新界面
	virtual void on_update(double delta) {}
	// 绘制界面
	virtual void on_drow() {}
	// 鼠标键盘输入
	virtual void on_input() {}
	// 退出界面
	virtual void on_exit() {}


private:
	Button search_friend;						// 查找好友按钮
	Button friends;								// 好友列表
	Button add_interests;						// 添加爱好

};