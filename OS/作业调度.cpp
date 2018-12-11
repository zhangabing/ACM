#include <bits/stdc++.h>

using namespace std;

struct jcb {
	char name[20]; // ��ҵ��
	int submitTime; // �ύʱ��
	int needTime; // ����ʱ��
	int beginTime; // ��ʼʱ��
	int finishTime; // ���ʱ��
	int turnTime; // ��תʱ��
	int memory; // ռ���ڴ�
	int tape; // ռ�ôŴ���
	char status; // W R F
};

// ���ύʱ������
bool cmp (jcb a, jcb b) {
	return a.submitTime < b.submitTime;
}

// ����ҵ������ʱ����Ϊ�ȶԹ���
struct cmp1 {
	bool operator () (jcb a, jcb b) {
		return a.needTime > b.needTime;
	}
};

// ����ҵ�Ľ���ʱ����Ϊ�ȽϹ���
struct cmp2 {
	bool operator () (jcb a, jcb b) {
		return a.finishTime > b.finishTime;
	}
};

vector<jcb> v;
int num;

void input () {
	printf ("��������ҵ������");
	scanf ("%d", &num);
	system("cls");

	jcb test;
	for (int i = 0; i < num; i++) {
		printf ("��������ҵ����");
		scanf ("%s", test.name);
		printf ("�������ύʱ�䣺");
		scanf ("%d", &test.submitTime);
		printf ("��������������ʱ�䣺");
		scanf ("%d", &test.needTime);
		v.push_back(test);
		system("cls");
	}
}

// �����ȷ���, ����������
void FCFS() {
	input();
	vector<jcb> q = v;

	// ��������ҵ�����ύʱ������
	sort (q.begin(), q.end(), cmp);

	int nowTime = 0; // CPUʱ��

	// ��ʼ��ҵ
	for (auto &i: q) {
		i.beginTime = max(nowTime, i.submitTime);
		i.finishTime = i.beginTime + i.needTime;
		i.turnTime = i.finishTime - i.submitTime;
		nowTime = i.finishTime;
	}
	puts("�������ҵ��");
	puts("��ҵ�� ��ʼ����ʱ�� ���ʱ�� ��תʱ�� ��Ȩ��תʱ��");
	double avgturn = 0, avgvalue = 0;
	for (auto i: q) {
		avgturn += i.turnTime;
		avgvalue += 1.0 * i.turnTime / i.needTime;
		printf ("%s\t%d\t\t%d\t%d\t%f\n", i.name, i.beginTime, i.finishTime, i.turnTime, 1.0 * i.turnTime / i.needTime);
	}
	printf ("������ҵ��ƽ����תʱ��Ϊ��%f\n", avgturn / num);
	printf ("������ҵ��ƽ����Ȩ��תʱ��Ϊ��%f\n", avgvalue / num);
}

// ����ҵ���ȣ�����������ڴ�100K�� �Ŵ���5̨
void SJF() {
	set<int> moment;
	// input
	printf ("��������ҵ������");
	scanf ("%d", &num);
	system("cls");
	jcb test;
	for (int i = 0; i < num; i++) {
		printf ("��������ҵ����");
		scanf ("%s", test.name);
		printf ("�������ύʱ�䣺");
		scanf ("%d", &test.submitTime);
		moment.insert(test.submitTime);
		printf ("��������������ʱ�䣺");
		scanf ("%d", &test.needTime);
		printf ("�����������ڴ棺");
		scanf ("%d", &test.memory);
		printf ("��������ռ�ôŴ���: ");
		scanf ("%d", &test.tape);
		v.push_back(test);
		system("cls");
	}
    getchar();

	puts ("������ҵ��Ϣ����\n");
	puts ("��ҵ�� �ύʱ�� ��������ʱ�� �����ڴ� ����Ŵ���");
	for (auto i: v) {
		printf ("%s\t%d\t%d\t\t%d\t%d\n", i.name, i.submitTime, i.needTime, i.memory, i.tape);
	}
	puts ("\n�밴�س�������... ...");
	getchar();
	system("cls");

	// �ڴ�100K���Ŵ���5̨
	int memory = 100;
	int tape = 5;
	int time = 0;
	int ind = 0;
	priority_queue<jcb, vector<jcb>, cmp1> wait; // �ȴ����У�����ҵ����
	priority_queue<jcb, vector<jcb>, cmp2> running; // ���ж���
	vector<jcb> finish; // ����ɶ���

	sort(v.begin(), v.end(), cmp); //
	while (finish.size() != num) {
		time = *moment.begin();
		moment.erase(moment.begin());

		// ��ҵ��ɣ�������ҵռ�õ���Դ
		while (!running.empty()) {
			if (running.top().finishTime <= time) {
				memory += running.top().memory;
				tape += running.top().tape;
				finish.push_back(running.top());
				running.pop();
			} else break;
		}

		// ��ҵ����ȴ�����
		while (ind < v.size() && v[ind].submitTime <= time)
			wait.push(v[ind++]);

		// �ӵȴ���������ȡ����ҵ����, ռ����Դ������running����
		vector<jcb> temp; // ��ʱ�洢
		while (!wait.empty()) {
			test = wait.top();	wait.pop();
			if (test.memory <= memory && test.tape <= tape) {
				test.beginTime = time;
				test.finishTime = test.beginTime + test.needTime;
				test.turnTime = test.finishTime - test.submitTime;
				memory -= test.memory;
				tape -= test.tape;
				running.push(test);
				moment.insert(test.finishTime); // ����ʱ���
			} else {
				temp.push_back(test);
			}
		}

		puts ("");
		printf ("��ǰʱ�̣�%d\n", time);
		printf ("��ǰ�����ڴ棺%d\n", memory);
		printf ("��ǰ���дŴ�����%d\n", tape);
		puts ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

		puts ("");
		puts ("�������ҵ:");
		puts("��ҵ�� ��ʼ����ʱ�� ���ʱ�� ��תʱ�� ��Ȩ��תʱ��");
		for (auto i: finish) {
			printf ("%s\t%d\t\t%d\t%d\t%f\n", i.name, i.beginTime, i.finishTime, i.turnTime, 1.0 * i.turnTime / i.needTime);
		}

		puts("");
		puts("δ�ύ��ҵ��");
		puts ("��ҵ�� �ύʱ�� ��������ʱ�� �����ڴ� ����Ŵ���");
		for (int i = ind; i < v.size(); i++) {
			printf ("%s\t%d\t%d\t\t%d\t%d\n", v[i].name, v[i].submitTime, v[i].needTime, v[i].memory, v[i].tape);
		}

		puts ("");
		puts ("�ȴ�����ҵ��");
		puts ("��ҵ�� �ύʱ�� ��������ʱ�� �����ڴ� ����Ŵ���");
		for (auto i: temp) {
			wait.push(i);
			printf ("%s\t%d\t%d\t\t%d\t%d\n", i.name, i.submitTime, i.needTime, i.memory, i.tape);
		}
		temp.clear();

		puts ("");
		puts ("��������ҵ��");
		puts ("��ҵ�� ��ʼ����ʱ�� ���н���ʱ�� ռ���ڴ� ռ�ôŴ���");
		while (!running.empty()) {
			auto i = running.top();	running.pop();
			temp.push_back(i);
			printf ("%s\t%d\t\t%d\t  %d\t   %d\n", i.name, i.beginTime, i.finishTime, i.memory, i.tape);
		}
		for (auto i: temp) running.push(i);
		temp.clear();

		puts ("");
		puts ("�밴�س�������... ...");
		getchar();
		system("cls");
	}

	puts("�������ҵ��");
	puts("��ҵ�� ��ʼ����ʱ�� ���ʱ�� ��תʱ�� ��Ȩ��תʱ��");
	double avgturn = 0, avgvalue = 0;
	for (auto i: finish) {
		avgturn += i.turnTime;
		avgvalue += 1.0 * i.turnTime / i.needTime;
		printf ("%s\t%d\t\t%d\t%d\t%f\n", i.name, i.beginTime, i.finishTime, i.turnTime, 1.0 * i.turnTime / i.needTime);
	}
	printf ("������ҵ��ƽ����תʱ��Ϊ��%f\n", avgturn / num);
	printf ("������ҵ��ƽ����Ȩ��תʱ��Ϊ��%f\n", avgvalue / num);
}

int main() {
//	FCFS();
	SJF();
	return 0;
}

/*
5
A 0 4
B 5 3
C 3 4
D 2 7
E 4 1

5
JOB1 0 20 20 2
JOB2 20 30 60 1
JOB3 30 15 45 3
JOB4 35 20 10 2
JOB5 45 10 25 3
*/
