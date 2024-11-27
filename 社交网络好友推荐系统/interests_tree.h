#pragma once
#include "Tree.h"

class InterestsTree : public Tree {
private:
	double interest_weight;

public:
	InterestsTree() {
		interest_weight = 1.0;
	}

	~InterestsTree() {}

	// 权重更新
	void update(std::string);
};
