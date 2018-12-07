/************************************************************************
    > File Name: 进程调度.cpp
    > Author: zhangab
    > Mail: 2411035458@qq.com 
    > Created Time: 2018年12月07日 星期五 17时15分29秒
************************************************************************/
#include <bits/stdc++.h>

using namespace std;

struct pcb { // 进程
    string name; // 进程名
    int toltime; // 进程总需要CPU时间片
    int nowtime; // 进程已占有CPU时间片
    bool finish() { // 进程是否完成
        return nowtime >= toltime;
    }
};
vector<pcb> v; // 读入所有进程
int num; // 进程号

// 已占用时间片不大于总需要时间片
void check(pcb & a) {
    a.nowtime = min (a.nowtime, a.toltime);
}

// 输出所有进程
void display(vector<pcb> a) {
    for (auto i: a) {
        cout << "进程名 : " << i.name;
        printf ("\t进程已占CPU时间片 : %d\t进程所需CPU时间片 : %d\n", i.nowtime, i.toltime);
    }
}

// 读入进程
void input() {
    v.clear();
    printf ("请输入进程号: ");
    cin >> num;
    system("clear");
    pcb test;
    for (int i = 0; i < num; i++) {
        printf ("请输入进程名:");
        cin >> test.name;
        printf ("请输入进程已占CPU时间片:");
        cin >> test.nowtime;
        printf ("请输入进程所需CPU时间片:");
        cin >> test.toltime;
        v.push_back(test);
        system("clear");
    }
//    display(v);
}

// 进程获取CPU时间片
pcb solve(pcb a, int t) {
    a.nowtime += (t - a.nowtime % t);
    check(a);
    printf ("当前运行的进程是 : ");
    cout << a.name << endl;
    return a;
}

// 多级反馈队列, 第一级时间片为1,后面的时间片为前面一个的时间片的2倍
void mulFeedQue() {
    const int N = 3; // 队列个数
    vector<pcb> que[N], finish;

    // 把所有进程放入第一队列
    for (auto i: v) {
        que[0].push_back(i);
    }
    puts ("准备就绪进程:");
    for (int i = 0; i < N; i++) {
        printf ("第%d队列:\n", i + 1);
        display(que[i]);
    }
    puts ("");
    getchar();

    while (1) {
        puts ("按回车键继续\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        getchar();
        system("clear");

        // 从第一级队列往后找非空的准备队列
        int ind = 0;
        while (ind < N && que[ind].size() == 0) ind++;

        // 所有队列为空即进程已完成
        if (ind >= N) break;

        // 取出进程
        pcb test = que[ind][0];
        que[ind].erase(que[ind].begin());

        // 获取时间片,第i级队列对应2^(i-1)个时间片
        test = solve(test, 1 << ind);

        // 已完成则放入已完成队列
        if (test.finish()) {
            finish.push_back(test);
        } else {
            // 否则放入下级队列,若已经是最后队列则简单轮转
            ind = min(N - 1, ind + 1);
            que[ind].push_back(test);
        }
        puts ("已完成进程:");
        display(finish);
        puts("");
        puts ("准备就绪进程:");
        for (int i = 0; i < N; i++) {
            printf ("第%d队列:\n", i + 1);
            display(que[i]);
        }
        puts ("");
    }
    printf ("进程已完成!\n");
}

// 可变时间片轮转法, 每一轮的时间片大小为准备就绪进程实际所需时间片均值
void variableTimeRR() {
    int timeSlice; // 时间片
    vector<pcb> que = v, finish, temp;

    puts ("准备就绪进程:");
    display(que);
    puts ("");
    getchar();
    puts ("按回车键继续\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    getchar();
    system("clear");

    while (que.size()) {

        // 设定时间片大小
        timeSlice = 0;
        for (auto i: que) {
            timeSlice += i.toltime - i.nowtime;
        }
        timeSlice = timeSlice / que.size() + (timeSlice % que.size() != 0); // 向上取整

        while (que.size()) {
            printf ("当前的时间片大小为 %d\n", timeSlice);
            puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            
            // 当前进程获取时间片
            que[0].nowtime += timeSlice;
            check(que[0]);
            
            // 若是已完成则放入已完成队列
            if (que[0].finish()) {
                finish.push_back(que[0]);
            } else {
                // 否则放入准备队列
                temp.push_back(que[0]);
            }
            printf ("当前运行的进程是 : ");
            cout << que[0].name << endl;
            que.erase(que.begin());
            puts ("已完成进程:");
            display(finish);
            puts("");
            puts ("准备就绪进程:");
            display(que);
            display(temp);
            puts("");
            puts ("按回车键继续...\n");
            getchar();
            system("clear");
        }
        que = temp;
        temp.clear();
    }

    printf ("进程已完成!\n");
}

int main() {
//    freopen ("test.txt", "r", stdin);
    input();
//    mulFeedQue();
    variableTimeRR();
    return 0;
}
/*
5
A 0 3
B 0 3
C 0 3
D 0 20
E 0 4
*/

