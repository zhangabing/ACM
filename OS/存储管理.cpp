#include <bits/stdc++.h>

using namespace std;

struct node {
	bool status; // 1为空闲 0为忙碌
	int memory;
	string name;
};

void out(vector<node> a) {
	for (auto i: a) {
		if (i.status) {
			printf ("该区内存 %d KB，状态 空闲\n", i.memory);
		} else {
			printf ("该区内存 %d KB，状态 忙碌，作业名 ", i.memory);
			cout << i.name << endl;
		}
	}
}

// 首次适应算法
void firstFit() {
	int num;
	string name, op;
	int memory;
	puts ("请输入请求个数：");
	scanf ("%d", &num);
	system("cls");

	vector<node> v;
	v.push_back(node{1, 600, name});
	while (num --) {
		puts ("请输入详细请求：");
		cin >> name >> op;
		scanf ("%dKB", &memory);
		if (op == "申请") {
			for (int i = 0; i < v.size(); i++) {
				if (v[i].status && v[i].memory > memory) {
					v[i].memory -= memory;
					v.insert (v.begin() + i, node{false, memory, name});
					break;
				} else if (v[i].status) {
					v[i].status = false;
					v[i].name = name;
					break;
				}
			}
		} else {
			for (int i = 0; i < v.size(); i++) {
				if (v[i].name == name) {
					v[i].status = true;
					if (i + 1 < v.size() && v[i + 1].status == true) {
						v[i].memory += v[i + 1].memory;
						v.erase(v.begin() + i + 1);
					}
					if (i - 1 >= 0 && )
					break;
				}
			}
		}
		puts ("");
		puts ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		puts ("");
	}
}

// 最佳适应算法
void bestFit() {

}

int main() {

	return 0;
}

/*
10
作业1 申请 130KB
作业2 申请 60KB
作业3 申请 100KB
作业2 释放 60KB
作业4 申请 200KB
作业3 释放 100KB
作业1 释放 130KB
作业5 申请 140KB
作业6 申请 60KB
作业7 申请 50KB
*/
