#pragma once
#include<vector>

#include "interests_tree.h"
#include "util.h"

class People {
private:
	std::string id;					// �û�ID
	std::string name;				// �û�����
	InterestsTree interests;		// �û���Ȥ��
	std::vector<std::string> frends;// �û�����id

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


	// �����û�Ȩ��
	void update(std::string data) {
		interests.update(data);
	}

};