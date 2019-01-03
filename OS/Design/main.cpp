#include <QApplication>


#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    MainWindow win;

    win.show();

    return app.exec();
}
/*
作业 进入时间 运行时间 优先数
JOB1   0      4      5
JOB2   2      3      3
JOB3   3      5      4
JOB4   5      2      6
*/

