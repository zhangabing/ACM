#include <bits/stdc++.h>

using namespace std;

struct jcb {
	char name[20]; // 作业名
	int submitTime; // 提交时间
	int needTime; // 运行时间
	int beginTime; // 开始时间
	int finishTime; // 完成时间
	int turnTime; // 周转时间
	int memory; // 占用内存
	int tape; // 占用磁带机
	char status; // W R F
};

// 按提交时间排序
bool cmp (jcb a, jcb b) {
	return a.submitTime < b.submitTime;
}

// 以作业的运行时间作为比对规则
struct cmp1 {
	bool operator () (jcb a, jcb b) {
		return a.needTime > b.needTime;
	}
};

// 以作业的结束时间作为比较规则
struct cmp2 {
	bool operator () (jcb a, jcb b) {
		return a.finishTime > b.finishTime;
	}
};

vector<jcb> v;
int num;

void input () {
	printf ("请输入作业数量：");
	scanf ("%d", &num);
	system("cls");

	jcb test;
	for (int i = 0; i < num; i++) {
		printf ("请输入作业名：");
		scanf ("%s", test.name);
		printf ("请输入提交时间：");
		scanf ("%d", &test.submitTime);
		printf ("请输入所需运行时间：");
		scanf ("%d", &test.needTime);
		v.push_back(test);
		system("cls");
	}
}

// 先来先服务, 单道批处理
void FCFS() {
	input();
	vector<jcb> q = v;

	// 把所有作业根据提交时间排序
	sort (q.begin(), q.end(), cmp);

	int nowTime = 0; // CPU时间

	// 开始作业
	for (auto &i: q) {
		i.beginTime = max(nowTime, i.submitTime);
		i.finishTime = i.beginTime + i.needTime;
		i.turnTime = i.finishTime - i.submitTime;
		nowTime = i.finishTime;
	}
	puts("已完成作业！");
	puts("作业名 开始运行时刻 完成时刻 周转时间 带权周转时间");
	double avgturn = 0, avgvalue = 0;
	for (auto i: q) {
		avgturn += i.turnTime;
		avgvalue += 1.0 * i.turnTime / i.needTime;
		printf ("%s\t%d\t\t%d\t%d\t%f\n", i.name, i.beginTime, i.finishTime, i.turnTime, 1.0 * i.turnTime / i.needTime);
	}
	printf ("本组作业的平均周转时间为：%f\n", avgturn / num);
	printf ("本组作业的平均带权周转时间为：%f\n", avgvalue / num);
}

// 短作业优先，多道批处理，内存100K， 磁带机5台
void SJF() {
	set<int> moment;
	// input
	printf ("请输入作业数量：");
	scanf ("%d", &num);
	system("cls");
	jcb test;
	for (int i = 0; i < num; i++) {
		printf ("请输入作业名：");
		scanf ("%s", test.name);
		printf ("请输入提交时间：");
		scanf ("%d", &test.submitTime);
		moment.insert(test.submitTime);
		printf ("请输入所需运行时间：");
		scanf ("%d", &test.needTime);
		printf ("请输入所需内存：");
		scanf ("%d", &test.memory);
		printf ("请输入所占用磁带机: ");
		scanf ("%d", &test.tape);
		v.push_back(test);
		system("cls");
	}
    getchar();

	puts ("本组作业信息如下\n");
	puts ("作业名 提交时间 所需运行时间 所需内存 所需磁带机");
	for (auto i: v) {
		printf ("%s\t%d\t%d\t\t%d\t%d\n", i.name, i.submitTime, i.needTime, i.memory, i.tape);
	}
	puts ("\n请按回车键继续... ...");
	getchar();
	system("cls");

	// 内存100K，磁带机5台
	int memory = 100;
	int tape = 5;
	int time = 0;
	int ind = 0;
	priority_queue<jcb, vector<jcb>, cmp1> wait; // 等待队列，短作业优先
	priority_queue<jcb, vector<jcb>, cmp2> running; // 运行队列
	vector<jcb> finish; // 已完成队列

	sort(v.begin(), v.end(), cmp); //
	while (finish.size() != num) {
		time = *moment.begin();
		moment.erase(moment.begin());

		// 作业完成，回收作业占用的资源
		while (!running.empty()) {
			if (running.top().finishTime <= time) {
				memory += running.top().memory;
				tape += running.top().tape;
				finish.push_back(running.top());
				running.pop();
			} else break;
		}

		// 作业进入等待队列
		while (ind < v.size() && v[ind].submitTime <= time)
			wait.push(v[ind++]);

		// 从等待队列里面取出作业运行, 占用资源，进入running队列
		vector<jcb> temp; // 临时存储
		while (!wait.empty()) {
			test = wait.top();	wait.pop();
			if (test.memory <= memory && test.tape <= tape) {
				test.beginTime = time;
				test.finishTime = test.beginTime + test.needTime;
				test.turnTime = test.finishTime - test.submitTime;
				memory -= test.memory;
				tape -= test.tape;
				running.push(test);
				moment.insert(test.finishTime); // 新增时间点
			} else {
				temp.push_back(test);
			}
		}

		puts ("");
		printf ("当前时刻：%d\n", time);
		printf ("当前空闲内存：%d\n", memory);
		printf ("当前空闲磁带机：%d\n", tape);
		puts ("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

		puts ("");
		puts ("已完成作业:");
		puts("作业名 开始运行时刻 完成时刻 周转时间 带权周转时间");
		for (auto i: finish) {
			printf ("%s\t%d\t\t%d\t%d\t%f\n", i.name, i.beginTime, i.finishTime, i.turnTime, 1.0 * i.turnTime / i.needTime);
		}

		puts("");
		puts("未提交作业：");
		puts ("作业名 提交时间 所需运行时间 所需内存 所需磁带机");
		for (int i = ind; i < v.size(); i++) {
			printf ("%s\t%d\t%d\t\t%d\t%d\n", v[i].name, v[i].submitTime, v[i].needTime, v[i].memory, v[i].tape);
		}

		puts ("");
		puts ("等待中作业：");
		puts ("作业名 提交时间 所需运行时间 所需内存 所需磁带机");
		for (auto i: temp) {
			wait.push(i);
			printf ("%s\t%d\t%d\t\t%d\t%d\n", i.name, i.submitTime, i.needTime, i.memory, i.tape);
		}
		temp.clear();

		puts ("");
		puts ("运行中作业：");
		puts ("作业名 开始运行时间 运行结束时间 占用内存 占用磁带机");
		while (!running.empty()) {
			auto i = running.top();	running.pop();
			temp.push_back(i);
			printf ("%s\t%d\t\t%d\t  %d\t   %d\n", i.name, i.beginTime, i.finishTime, i.memory, i.tape);
		}
		for (auto i: temp) running.push(i);
		temp.clear();

		puts ("");
		puts ("请按回车键继续... ...");
		getchar();
		system("cls");
	}

	puts("已完成作业！");
	puts("作业名 开始运行时刻 完成时刻 周转时间 带权周转时间");
	double avgturn = 0, avgvalue = 0;
	for (auto i: finish) {
		avgturn += i.turnTime;
		avgvalue += 1.0 * i.turnTime / i.needTime;
		printf ("%s\t%d\t\t%d\t%d\t%f\n", i.name, i.beginTime, i.finishTime, i.turnTime, 1.0 * i.turnTime / i.needTime);
	}
	printf ("本组作业的平均周转时间为：%f\n", avgturn / num);
	printf ("本组作业的平均带权周转时间为：%f\n", avgvalue / num);
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
