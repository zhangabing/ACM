#include <bits/stdc++.h>

using namespace std;

struct node {
	bool status; // 1Ϊ���� 0Ϊæµ
	int memory;
	string name;
};

void out(vector<node> a) {
	for (auto i: a) {
		if (i.status) {
			printf ("�����ڴ� %d KB��״̬ ����\n", i.memory);
		} else {
			printf ("�����ڴ� %d KB��״̬ æµ����ҵ�� ", i.memory);
			cout << i.name << endl;
		}
	}
}

// �״���Ӧ�㷨
void firstFit() {
	int num;
	string name, op;
	int memory;
	puts ("���������������");
	scanf ("%d", &num);
	system("cls");

	vector<node> v;
	v.push_back(node{1, 600, name});
	while (num --) {
		puts ("��������ϸ����");
		cin >> name >> op;
		scanf ("%dKB", &memory);
		if (op == "����") {
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

// �����Ӧ�㷨
void bestFit() {

}

int main() {

	return 0;
}

/*
10
��ҵ1 ���� 130KB
��ҵ2 ���� 60KB
��ҵ3 ���� 100KB
��ҵ2 �ͷ� 60KB
��ҵ4 ���� 200KB
��ҵ3 �ͷ� 100KB
��ҵ1 �ͷ� 130KB
��ҵ5 ���� 140KB
��ҵ6 ���� 60KB
��ҵ7 ���� 50KB
*/
