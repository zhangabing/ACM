#include <bits/stdc++.h>

using namespace std;

// �ڴ�
struct node {
	bool status; // 1Ϊ���� 0Ϊæµ
	int memory;
	string name;
};

// ��ӡ�ڴ�
void out(vector<node> a) {
	for (auto i: a) {
		if (i.status) {
			printf ("�����ڴ� %4d KB��״̬ ����\n", i.memory);
		} else {
			printf ("�����ڴ� %4d KB��״̬ æµ����ҵ�� ", i.memory);
			cout << i.name << endl;
		}
	}
}

// �״���Ӧ�㷨
void firstFit() {
	int num;
	string name, op;
	int memory;
	printf ("���������������");
	scanf ("%d", &num);
	system("cls");

	vector<node> v;
	v.push_back(node{true, 600, name});
	while (num --) {
		printf ("��������ϸ����");
		cin >> name >> op;
		scanf ("%dKB", &memory);
		getchar();

		// �����ڴ�
		if (op == "����") {
			for (int i = 0; i < v.size(); i++) {
				// �����ڴ���������ڴ棬����
				if (v[i].status && v[i].memory > memory) {
					v[i].memory -= memory;
					v.insert (v.begin() + i, node{false, memory, name});
					break;
				} else if (v[i].status && v[i].memory == memory) {
					// �����ڴ���������ڴ棬�������
					v[i].status = false;
					v[i].name = name;
					break;
				}
			}
		} else { // �ͷ��ڴ�
			for (int i = 0; i < v.size(); i++) {
				if (v[i].name == name) {
					v[i].status = true;
					// ǰ��ϲ�
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
		puts ("��ǰ�ڴ����������£�");
		out (v);
		puts ("");
		puts ("�밴�س�������... ...");
		getchar();
		system("cls");
	}
	puts ("");
	puts ("������������룡");
	puts ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	puts ("�����ڴ�������£�\n");
	out (v);
	puts ("");

}

// �����Ӧ�㷨
void bestFit() {
	int num;
	string name, op;
	int memory;
	printf ("���������������");
	scanf ("%d", &num);
	system("cls");

	vector<node> v;
	v.push_back(node{1, 600, name});
	while (num --) {
		printf ("��������ϸ����");
		cin >> name >> op;
		scanf ("%dKB", &memory);
		getchar();
		int ind = -1;

		// �����ڴ�
		if (op == "����") {
			// �������ʺ��ڴ�
			for (int i = 0; i < v.size(); i++) {
				if (v[i].status && v[i].memory >= memory) {
					if (ind == -1 || v[ind].memory > v[i].memory)
						ind = i;
				}
			}
			// ���з���
			if (v[ind].memory == memory) {
				v[ind].status = false;
				v[ind].name = name;
			} else {
				v[ind].memory -= memory;
				v.insert (v.begin() + ind, node{false, memory, name});
			}
		} else {
			// �ͷ��ڴ�
			for (int i = 0; i < v.size(); i++) {
				if (v[i].name == name) {
					v[i].status = true;
					// ǰ��ϲ�
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
		puts ("��ǰ�ڴ����������£�");
		out (v);
		puts ("");
		puts ("�밴�س�������... ...");
		getchar();
		system("cls");
	}
	puts ("");
	puts ("������������룡");
	puts ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	puts ("�����ڴ�������£�\n");
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
