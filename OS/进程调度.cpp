/************************************************************************
    > File Name: ���̵���.cpp
    > Author: zhangab
    > Mail: 2411035458@qq.com
    > Created Time: 2018��12��07�� ������ 17ʱ15��29��
************************************************************************/
#include <bits/stdc++.h>

using namespace std;

struct pcb { // ����
    string name; // ������
    int toltime; // ��������ҪCPUʱ��Ƭ
    int nowtime; // ������ռ��CPUʱ��Ƭ
    bool finish() { // �����Ƿ����
        return nowtime >= toltime;
    }
};
vector<pcb> v; // �������н���
int num; // ���̺�

// ��ռ��ʱ��Ƭ����������Ҫʱ��Ƭ
void check(pcb & a) {
    a.nowtime = min (a.nowtime, a.toltime);
}

// ������н���
void display(vector<pcb> a) {
    for (auto i: a) {
        cout << "������ : " << i.name;
        printf ("\t������ռCPUʱ��Ƭ : %d\t��������CPUʱ��Ƭ : %d\n", i.nowtime, i.toltime);
    }
}

// �������
void input() {
    v.clear();
    printf ("��������̺�: ");
    cin >> num;
    system("clr");
    pcb test;
    for (int i = 0; i < num; i++) {
        printf ("�����������:");
        cin >> test.name;
        printf ("�����������ռCPUʱ��Ƭ:");
        cin >> test.nowtime;
        printf ("�������������CPUʱ��Ƭ:");
        cin >> test.toltime;
        v.push_back(test);
        system("clr");
    }
//    display(v);
}

// ���̻�ȡCPUʱ��Ƭ
pcb solve(pcb a, int t) {
    a.nowtime += (t - a.nowtime % t);
    check(a);
    printf ("��ǰ���еĽ����� : ");
    cout << a.name << endl;
    return a;
}

// �༶��������, ��һ��ʱ��ƬΪ1,�����ʱ��ƬΪǰ��һ����ʱ��Ƭ��2��
void mulFeedQue() {
    const int N = 3; // ���и���
    vector<pcb> que[N], finish;

    // �����н��̷����һ����
    for (auto i: v) {
        que[0].push_back(i);
    }
    puts ("׼����������:");
    for (int i = 0; i < N; i++) {
        printf ("��%d����:\n", i + 1);
        display(que[i]);
    }
    puts ("");
    getchar();

    while (1) {
        puts ("���س�������\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        getchar();
        system("clr");

        // �ӵ�һ�����������ҷǿյ�׼������
        int ind = 0;
        while (ind < N && que[ind].size() == 0) ind++;

        // ���ж���Ϊ�ռ����������
        if (ind >= N) break;

        // ȡ������
        pcb test = que[ind][0];
        que[ind].erase(que[ind].begin());

        // ��ȡʱ��Ƭ,��i�����ж�Ӧ2^(i-1)��ʱ��Ƭ
        test = solve(test, 1 << ind);

        // ��������������ɶ���
        if (test.finish()) {
            finish.push_back(test);
        } else {
            // ��������¼�����,���Ѿ��������������ת
            ind = min(N - 1, ind + 1);
            que[ind].push_back(test);
        }
        puts ("����ɽ���:");
        display(finish);
        puts("");
        puts ("׼����������:");
        for (int i = 0; i < N; i++) {
            printf ("��%d����:\n", i + 1);
            display(que[i]);
        }
        puts ("");
    }
    printf ("���������!\n");
}

// �ɱ�ʱ��Ƭ��ת��, ÿһ�ֵ�ʱ��Ƭ��СΪ׼����������ʵ������ʱ��Ƭ��ֵ
void variableTimeRR() {
    int timeSlice; // ʱ��Ƭ
    vector<pcb> que = v, finish, temp;

    puts ("׼����������:");
    display(que);
    puts ("");
    getchar();
    puts ("���س�������\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    getchar();
    system("clr");

    while (que.size()) {

        // �趨ʱ��Ƭ��С
        timeSlice = 0;
        for (auto i: que) {
            timeSlice += i.toltime - i.nowtime;
        }
        timeSlice = timeSlice / que.size() + (timeSlice % que.size() != 0); // ����ȡ��

        while (que.size()) {
            printf ("��ǰ��ʱ��Ƭ��СΪ %d\n", timeSlice);
            puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

            // ��ǰ���̻�ȡʱ��Ƭ
            que[0].nowtime += timeSlice;
            check(que[0]);

            // ������������������ɶ���
            if (que[0].finish()) {
                finish.push_back(que[0]);
            } else {
                // �������׼������
                temp.push_back(que[0]);
            }
            printf ("��ǰ���еĽ����� : ");
            cout << que[0].name << endl;
            que.erase(que.begin());
            puts ("����ɽ���:");
            display(finish);
            puts("");
            puts ("׼����������:");
            display(que);
            display(temp);
            puts("");
            puts ("���س�������...\n");
            getchar();
            system("clr");
        }
        que = temp;
        temp.clear();
    }

    printf ("���������!\n");
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

