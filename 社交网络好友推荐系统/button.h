#pragma once

#include "vector2.h"
#include "util.h"
#include<graphics.h>
#include<string>

class Button {
public:
	enum class ButtonState {
		idle,
		touch,
		press
	};

public:
	Button(int x,int y) {
		pos.x = x;
		pos.y = y;
		size.x = 130;
		size.y = 45;
		data_pos = Vector2(0, 0);
	}

	Button() {
		pos.x = 0;
		pos.y = 0;
		size.x = 130;
		size.y = 45;
		data_pos = Vector2(0, 0);
	}

	Button(int x, int y, int w, int h) {
		pos.x = x;
		pos.y = y;
		size.x = w;
		size.y = h;
		data_pos = Vector2(0, 0);
	}

	~Button() = default;

	// 按下
	virtual void press() {}

	Vector2 get_pos() {
		return pos;
	}

	Vector2 get_size() {
		return size;
	}

	void set_size(Vector2 size) {
		this->size = size;
	}

	void set_size(float x, float y) {
		size.x = x;
		size.y = y;
	}

	void set_pos(Vector2 pos) {
		this->pos = pos;
	}

	void set_pos(float x, float y) {
		pos.x = x;
		pos.y = y;
	}

	bool mouse_in_button(const Vector2 mouse_pos) {
		return mouse_pos.x > pos.x && (mouse_pos.x < pos.x + size.x)
			&& mouse_pos.y > pos.y && (mouse_pos.y < pos.y + size.y);
	}

	ButtonState get_button_state() {
		return button_state;
	}

	void set_button_state(ButtonState state) {
		button_state = state;
	}

	void set_data(LPCTSTR data) {
		this->data = data;
	}

	void on_drow() {
		data_pos.x = pos.x + (size.x - textwidth(data)) / 2;
		data_pos.y = pos.y + (size.y - textheight(data)) / 2;
		switch (button_state)
		{
		case Button::ButtonState::idle:
			setfillcolor(RGB(245, 245, 245));
			solidroundrect(pos.x, pos.y, pos.x + size.x, pos.y + size.y, 8, 8);
			break;
		case Button::ButtonState::touch:
			setfillcolor(RGB(222, 222, 222));
			solidroundrect(pos.x, pos.y, pos.x + size.x, pos.y + size.y, 8, 8);
			break;
		case Button::ButtonState::press:
			setfillcolor(RGB(145, 145, 145));
			solidroundrect(pos.x, pos.y, pos.x + size.x, pos.y + size.y, 8, 8);
			break;
		default:
			break;
		}

		settextcolor(RGB(0, 0, 0));
		outtextxy(data_pos.x, data_pos.y, data);
	}


private:
	Vector2 pos;
	Vector2 size;
	ButtonState button_state = ButtonState::idle;		// 默认闲置状态
	LPCTSTR data = _T("");								// 按钮上文字
	Vector2 data_pos;									// 文字位置

};
