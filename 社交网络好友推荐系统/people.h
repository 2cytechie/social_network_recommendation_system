#pragma once
#include<vector>

#include "interests_tree.h"
#include "util.h"

class People {
private:
	std::string id;					// 用户ID
	std::string name;				// 用户姓名
	InterestsTree interests;		// 用户兴趣树
	std::vector<std::string> frends;// 用户好友id

public:
	People(std::string name) {
		id = get_new_id();
		this->name = name;
	}

	~People() {}

	std::string get_id() {
		return id;
	}

	std::string get_name() {
		return name;
	}

	void set_name(std::string name) {
		this->name = name;
	}

	InterestsTree get_interests() {
		return interests;
	}


	// 更新用户权重
	void update(std::string data) {
		interests.update(data);
	}

};