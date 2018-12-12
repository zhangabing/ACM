#include <bits/stdc++.h>

using namespace std;

// 内存
struct node {
	bool status; // 1为空闲 0为忙碌
	int memory;
	string name;
};

// 打印内存
void out(vector<node> a) {
	for (auto i: a) {
		if (i.status) {
			printf ("该区内存 %4d KB，状态 空闲\n", i.memory);
		} else {
			printf ("该区内存 %4d KB，状态 忙碌，作业名 ", i.memory);
			cout << i.name << endl;
		}
	}
}

// 首次适应算法
void firstFit() {
	int num;
	string name, op;
	int memory;
	printf ("请输入请求个数：");
	scanf ("%d", &num);
	system("cls");

	vector<node> v;
	v.push_back(node{true, 600, name});
	while (num --) {
		printf ("请输入详细请求：");
		cin >> name >> op;
		scanf ("%dKB", &memory);
		getchar();

		// 申请内存
		if (op == "申请") {
			for (int i = 0; i < v.size(); i++) {
				// 分配内存大于所需内存，分区
				if (v[i].status && v[i].memory > memory) {
					v[i].memory -= memory;
					v.insert (v.begin() + i, node{false, memory, name});
					break;
				} else if (v[i].status && v[i].memory == memory) {
					// 分配内存等于所需内存，无需分区
					v[i].status = false;
					v[i].name = name;
					break;
				}
			}
		} else { // 释放内存
			for (int i = 0; i < v.size(); i++) {
				if (v[i].name == name) {
					v[i].status = true;
					// 前后合并
					if (i + 1 < v.size() && v[i + 1].status) {
						v[i].memory += v[i + 1].memory;
						v.erase(v.begin() + i + 1);
					}
					if (i - 1 >= 0 && v[i - 1].status) {
						v[i - 1].memory += v[i].memory;
						v.erase(v.begin() + i);
					}
					break;
				}
			}
		}
		puts ("");
		puts ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		puts ("");
		puts ("当前内存区分配如下：");
		out (v);
		puts ("");
		puts ("请按回车键继续... ...");
		getchar();
		system("cls");
	}
	puts ("");
	puts ("已完成所有申请！");
	puts ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	puts ("最终内存分配如下：\n");
	out (v);
	puts ("");

}

// 最佳适应算法
void bestFit() {
	int num;
	string name, op;
	int memory;
	printf ("请输入请求个数：");
	scanf ("%d", &num);
	system("cls");

	vector<node> v;
	v.push_back(node{1, 600, name});
	while (num --) {
		printf ("请输入详细请求：");
		cin >> name >> op;
		scanf ("%dKB", &memory);
		getchar();
		int ind = -1;

		// 申请内存
		if (op == "申请") {
			// 查找最适合内存
			for (int i = 0; i < v.size(); i++) {
				if (v[i].status && v[i].memory >= memory) {
					if (ind == -1 || v[ind].memory > v[i].memory)
						ind = i;
				}
			}
			// 进行分配
			if (v[ind].memory == memory) {
				v[ind].status = false;
				v[ind].name = name;
			} else {
				v[ind].memory -= memory;
				v.insert (v.begin() + ind, node{false, memory, name});
			}
		} else {
			// 释放内存
			for (int i = 0; i < v.size(); i++) {
				if (v[i].name == name) {
					v[i].status = true;
					// 前后合并
					if (i + 1 < v.size() && v[i + 1].status) {
						v[i].memory += v[i + 1].memory;
						v.erase(v.begin() + i + 1);
					}
					if (i - 1 >= 0 && v[i - 1].status) {
						v[i - 1].memory += v[i].memory;
						v.erase(v.begin() + i);
					}
					break;
				}
			}
		}

		puts ("");
		puts ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		puts ("");
		puts ("当前内存区分配如下：");
		out (v);
		puts ("");
		puts ("请按回车键继续... ...");
		getchar();
		system("cls");
	}
	puts ("");
	puts ("已完成所有申请！");
	puts ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	puts ("最终内存分配如下：\n");
	out (v);
	puts ("");
}

int main() {
//	firstFit();
	bestFit();
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
