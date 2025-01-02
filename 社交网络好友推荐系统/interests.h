#pragma once
#include<vector>
#include<string>

class Interests {
public:
	Interests() = default;

	~Interests() = default;

	void add_interest(std::string name) {
		bool is_find = false;						// 是否已经添加兴趣
		for (int i = 0; i < interests.size(); i++) {
			if (interests[i].interest == name) {
				interests[i].number++;
				is_find = true;
				return;
			}
		}
		if (!is_find) {
			_interest interest(name);
			interests.push_back(interest);
		}
	}

	double get_interests_num() {
		double sum = 0;
		for (auto& inter : interests) {
			sum += inter.number;
		}
		return sum;
	}

	size_t size() {
		return interests.size();
	}

private:
	struct _interest {
		std::string interest;							// 兴趣
		size_t number = 1;								// 次数用于计算权重
		_interest(std::string inter) {
			this->interest = inter;
		}
	};

public:
	_interest& operator[](size_t index) {
		return interests[index];
	}

private:
	std::vector<_interest> interests;					// 兴趣点
};
