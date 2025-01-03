#pragma once
#include<vector>

#include "interests.h"
#include "util.h"

class People {
private:
	std::string id;									// �û�ID
	std::string name;								// �û�����
	Interests interests;							// �û���Ȥ
	std::vector<std::string> friends_id;			// �û�����id

public:
	People(std::string id,std::string name) {
		this->id = id;
		this->name = name;
	}

	~People() = default;

	std::string get_id() {
		return id;
	}

	std::string get_name() {
		return name;
	}

	void set_name(std::string name) {
		this->name = name;
	}

	const Interests get_interests() const {
		return interests;
	}

	const std::vector<std::string> get_friends() const {
		return friends_id;
	}

	void add_interest(std::string inter) {
		interests.add_interest(inter);
	}

	void add_friend(std::string id) {
		// ����Ƿ��Ѿ���Ӻ���
		for (auto &i : friends_id) {
			if (i == id) {
				return;
			}
		}
		friends_id.push_back(id);
	}

};