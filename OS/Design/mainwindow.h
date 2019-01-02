#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTableWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

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
    int id;              // 输入作业id



    JOB *scheduling = new JOB;

    void show() {
        win.show();
    }

    void add() {
        scheduling->add(editname->text(), Boxenter->value(), Boxrun->value(), Boxpri->value(), id);
        table->setItem(id, 0, new QTableWidgetItem(editname->text()));
        id ++;
    }

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
