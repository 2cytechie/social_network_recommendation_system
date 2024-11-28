#pragma once

#include "vector2.h"
#include<graphics.h>

class Button {
public:
	enum class ButtonState {
		idle,
		touch,
		press
	};

	enum class ButtonType {
		center,				// 居中
		left				// 左对齐
	};

public:
	Button(int x,int y) {
		pos.x = x;
		pos.y = y;
		size.x = 130;
		size.y = 45;
	}

	Button() {
		pos.x = 0;
		pos.y = 0;
		size.x = 130;
		size.y = 45;
	}

	Button(int x, int y, int w, int h) {
		pos.x = x;
		pos.y = y;
		size.x = w;
		size.y = h;
	}

	~Button() = default;

	Vector2 get_pos() const {
		return pos;
	}

	Vector2 get_size() const {
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

	ButtonState get_button_state() const {
		return button_state;
	}

	void set_button_state(ButtonState state) {
		button_state = state;
	}

	void set_button_tpye(ButtonType state) {
		button_tpye = state;
	}

	void set_data(LPCTSTR data) {
		this->data = data;
	}

	bool is_press() {
		return button_state == ButtonState::press;
	}

	// 绘制
	void on_drow() {
		// 计算文字打印位置
		switch (button_tpye)
		{
		case Button::ButtonType::center:
			data_pos.x = pos.x + (size.x - textwidth(data)) / 2;
			data_pos.y = pos.y + (size.y - textheight(data)) / 2;
			break;
		case Button::ButtonType::left:
			data_pos.x = pos.x + 50;
			data_pos.y = pos.y + (size.y - textheight(data)) / 2;
			break;
		default:
			break;
		}

		// 根据按钮不同状态显示不同颜色，实现鼠标放在按钮上变灰，按下变黑
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
		// 绘制文字
		settextcolor(RGB(0, 0, 0));
		outtextxy(data_pos.x, data_pos.y, data);
	}

	void on_update(const ExMessage msg) {
		Vector2 mouse_pos(msg.x, msg.y);
		if (mouse_in_button(mouse_pos)) {
			button_state = Button::ButtonState::touch;
			if (msg.message == WM_LBUTTONDOWN) {
				button_state = Button::ButtonState::press;
			}
		}
		else {
			button_state = Button::ButtonState::idle;
		}
	}


private:
	Vector2 pos;
	Vector2 size;
	ButtonState button_state = ButtonState::idle;		// 默认闲置状态
	ButtonType button_tpye = ButtonType::center;		// 默认居中
	LPCTSTR data = _T("");								// 按钮上文字
	Vector2 data_pos;									// 文字位置

};
