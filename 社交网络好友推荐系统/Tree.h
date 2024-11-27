#pragma once
#include<string>
#include<vector>

class Tree {
	// 树定义
private:
	std::string data;
	std::vector<Tree*> children;

	// 树的方法	1、创建树    2、索引    3、添加    4、删除    5、更新

public:
	Tree() {

	}

	~Tree(){}

	void find(std::string data);
	void insert(std::string data);
	void remove(std::string data);

};