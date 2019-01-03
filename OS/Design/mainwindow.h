#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTableWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QDebug>
#include <algorithm>

#include "job.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
//    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QWidget win; // 主窗口
    QTableWidget *table;// 表格窗口
    QLabel *label2; // 当前时间输出标签
    QLabel *labelavg2; // 平均周转时间
    QLabel *labelavgW2;// 平均带权周转时间
    QLineEdit *editname; // 作业名输入
    QSpinBox *Boxenter;  // 提交时间输入
    QSpinBox *Boxrun;    // 运行时间输入
    QSpinBox *Boxpri;    // 优先数输入
    QPushButton *button1;// 手动写入
    QPushButton *button2;// 随机生成
    QPushButton *button; // 执行按钮
    int id = 0;           // 输入作业id
    int time = -1;


    JOB *scheduling = new JOB;

    void show() {
        win.show();
    }

    void display(JOB::work a) {
        table->setItem(a.id, 0, new QTableWidgetItem(a.name));
        table->setItem(a.id, 1, new QTableWidgetItem(QString::number(a.submittime)));
        table->setItem(a.id, 2, new QTableWidgetItem(QString::number(a.runtime)));
        table->setItem(a.id, 3, new QTableWidgetItem(QString::number(a.priority)));

        QString str[4] = {"未提交", "准备就绪", "执行中", "已完成"};
        table->setItem(a.id, 4, new QTableWidgetItem(str[a.JOBstatus]));

        if (a.JOBstatus <= 1) {
            table->setItem(a.id, 5, new QTableWidgetItem("NULL"));
        } else {
            table->setItem(a.id, 5, new QTableWidgetItem(QString::number(a.begintime)));
        }

        if (a.JOBstatus == 3) {
            table->setItem(a.id, 6, new QTableWidgetItem(QString::number(a.endtime)));
            table->setItem(a.id, 7, new QTableWidgetItem(QString::number(a.returntime)));
            table->setItem(a.id, 8, new QTableWidgetItem(QString::number(a.wighReturntime)));
        } else {
            table->setItem(a.id, 6, new QTableWidgetItem("NULL"));
            table->setItem(a.id, 7, new QTableWidgetItem("NULL"));
            table->setItem(a.id, 8, new QTableWidgetItem("NULL"));
        }

        if (a.PCBstatus == 2) {
            table->setItem(a.id, 9, new QTableWidgetItem("已完成"));
        } else if (a.PCBstatus == 1) {
            table->setItem(a.id, 9, new QTableWidgetItem("执行中"));
        } else {
            table->setItem(a.id, 9, new QTableWidgetItem("未执行"));
        }

    }

    void add() {
        scheduling->add(editname->text(), Boxenter->value(), Boxrun->value(), Boxpri->value(), id);
        display(JOB::work(editname->text(), Boxenter->value(), Boxrun->value(), Boxpri->value(), id));
        id ++;
    }
    void generate() {
        /*
        作业 进入时间 运行时间 优先数
        JOB1   0      4      5
        JOB2   2      3      3
        JOB3   3      5      4
        JOB4   5      2      6
        */
        scheduling->add("JOB1", 0, 4, 5, id);
        display(JOB::work("JOB1", 0, 4, 5, id++));
        scheduling->add("JOB2", 2, 3, 3, id);
        display(JOB::work("JOB2", 2, 3, 3, id++));
        scheduling->add("JOB3", 3, 5, 4, id);
        display(JOB::work("JOB3", 3, 5, 4, id++));
        scheduling->add("JOB4", 5, 2, 6, id);
        display(JOB::work("JOB4", 5, 2, 6, id++));
    }

    void run () {
        time ++;
        label2->setText(QString::number(time));

        // 未提交变成准备就绪
        for (int i = 0; i < scheduling->unsubmit.size(); i++) {
            if (scheduling->unsubmit[i].submittime<=time) {
                scheduling->unsubmit[i].JOBstatus++; // 准备就绪状态
                scheduling->ready.push_back(scheduling->unsubmit[i]);
                scheduling->unsubmit.erase(scheduling->unsubmit.begin() + i);
                i --;
            }
        }

        // 执行中变成已完成
        if (scheduling->running.size() > 1) { // 把优先级高的放在前面，并修改进程状态
            if (scheduling->running[0].priority > scheduling->running[1].priority) {
                std::swap(scheduling->running[0], scheduling->running[1]);
            }
            scheduling->running[1].PCBstatus = 0;
        }

        if (scheduling->running.size() > 0) {
            scheduling->running[0].PCBstatus = 1;
            if (--scheduling->running[0].restime == 0) { // 判断是否已完成作业
                scheduling->running[0].endtime = time;
                scheduling->running[0].returntime = time - scheduling->running[0].begintime;
                scheduling->running[0].wighReturntime = 1.0 * scheduling->running[0].returntime / scheduling->running[0].runtime;
                scheduling->running[0].JOBstatus++;
                scheduling->running[0].PCBstatus++;
                scheduling->finish.push_back(scheduling->running[0]);
                scheduling->running.erase(scheduling->running.begin());
            }
        }

        // 准备就绪变成执行中
        std::sort(scheduling->ready.begin(), scheduling->ready.end());
        while (scheduling->running.size() < 2 && scheduling->ready.size() > 0) {
            scheduling->ready[0].JOBstatus++;
            scheduling->ready[0].begintime = time;
            scheduling->running.push_back(scheduling->ready[0]);
            scheduling->ready.erase(scheduling->ready.begin());
        }

        // 修改表格
        for (auto i: scheduling->unsubmit) {
            display(i);
        }
        for (auto i: scheduling->ready) {
            display(i);
        }
        for (auto i: scheduling->running) {
            display(i);
        }
        for (auto i: scheduling->finish) {
            display(i);
        }

        if (scheduling->unsubmit.size() == 0 && scheduling->ready.size() == 0 && scheduling->running.size() == 0) {
            double avg = 0;
            for (auto i: scheduling->finish) {
                avg += i.returntime;
            }
            avg /= scheduling->finish.size();
            labelavg2->setText(QString::number(avg));

            avg = 0;
            for (auto i: scheduling->finish) {
                avg += i.wighReturntime;
            }
            avg /= scheduling->finish.size();
            labelavgW2->setText(QString::number(avg));
        }
    }

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
