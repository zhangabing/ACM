#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"

const int wide = 200;
const int high = 40;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout *layoutwin = new QVBoxLayout;
    win.setLayout(layoutwin);

// 设置时间
    QWidget *time = new QWidget;
    time->setFixedSize(wide, high);

    QHBoxLayout *layouttime = new QHBoxLayout;

    // 定义时间标签并添加进时间窗口
    QLabel *label1 = new QLabel("当前时刻：", time);
//    label1.resize(22, 50);
    layouttime->addWidget(label1);

    label2 = new QLabel("0", time);
//    label2.resize(22, 50);
    layouttime->addWidget(label2);
    time->setLayout(layouttime);

    // 将时间窗口添加进主窗口
    layoutwin->addWidget(time);

// 设置表格
    table = new QTableWidget(5, 10);
    table->setWindowTitle("两道批处理两级调度");
    table->setFixedSize(1280, wide);

    // 行标题
    QStringList headerLabels;
    headerLabels << "作业名" <<"进入时间" <<"运行时间" <<"优先数" <<"作业状态" <<"开始时间" <<"结束时间" <<"周转时间" <<"带权周转时间" <<"进程状态";
    table->setHorizontalHeaderLabels(headerLabels);

    // 行高度
    for (int i = 0; i < 5; i++) {
        table->setRowHeight(i, 22);
    }

    //设置表格的选择方式
    table->setSelectionBehavior(QAbstractItemView::SelectItems);

    //设置编辑方式
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 把表格添加进布局
    layoutwin->addWidget(table);

// 设置表格下窗口，下窗口由左右窗口组成

    //定义下窗口，并将其加入win的布局
    QWidget *down = new QWidget;
    layoutwin->addWidget(down);

    // 定义下窗口的布局
    QHBoxLayout *layoutdown = new QHBoxLayout;
    down->setLayout(layoutdown);

    // 定义right窗口
    QWidget *right = new QWidget;
    right->setFixedWidth(220);
    layoutdown->addWidget(right);

    // 定义right窗口布局
    QVBoxLayout *layoutright = new QVBoxLayout;
    right->setLayout(layoutright);

    // right作业名窗口
    QWidget *name = new QWidget;
    name->setFixedSize(wide, high);
    layoutright->addWidget(name);

    QHBoxLayout *layoutname = new QHBoxLayout;
    name->setLayout(layoutname);

    QLabel *labelname = new QLabel("作业名：", name);
    layoutname->addWidget(labelname);
    editname = new QLineEdit;
    layoutname->addWidget(editname);
    editname->setParent(name);
    editname->setPlaceholderText("请输入作业名");

    // right 进入时间窗口
    QWidget *entertime = new QWidget;
    entertime->setFixedSize(wide, high);
    layoutright->addWidget(entertime);

    QHBoxLayout *layoutenter = new QHBoxLayout;
    entertime->setLayout(layoutenter);

    QLabel *labelenter = new QLabel("进入时间：", entertime);
    layoutenter->addWidget(labelenter);
    Boxenter = new QSpinBox(entertime);
    layoutenter->addWidget(Boxenter);

    // right 运行时间窗口
    QWidget *runtime = new QWidget;
    runtime->setFixedSize(wide, high);
    layoutright->addWidget(runtime);

    QHBoxLayout *layoutrun = new QHBoxLayout;
    runtime->setLayout(layoutrun);

    QLabel *labelrun = new QLabel("运行时间：", runtime);
    layoutrun->addWidget(labelrun);
    Boxrun = new QSpinBox(runtime);
    layoutrun->addWidget(Boxrun);

    // right 优先数
    QWidget *priority = new QWidget;
    priority->setFixedSize(wide, high);
    layoutright->addWidget(priority);

    QHBoxLayout *layoutpri = new QHBoxLayout;
    priority->setLayout(layoutpri);

    QLabel *labelpri = new QLabel("优先级数：", priority);
    layoutpri->addWidget(labelpri);
    Boxpri = new QSpinBox(priority);
    layoutpri->addWidget(Boxpri);

    // right 写入进程按钮
    QWidget *widgetbuttun = new QWidget;
    widgetbuttun->setFixedSize(wide, 50);
    layoutright->addWidget(widgetbuttun);

    QHBoxLayout *layoutbutton = new QHBoxLayout;
    widgetbuttun->setLayout(layoutbutton);

    button1 = new QPushButton("手动写入", widgetbuttun);
    layoutbutton->addWidget(button1);
    button2 = new QPushButton("一键生成", widgetbuttun);
    layoutbutton->addWidget(button2);

    // 手动写入信号槽
    QObject::connect(button1, &QPushButton::clicked, this, &MainWindow::add);

    // 一键生成信号槽
    QObject::connect(button2, &QPushButton::clicked, this, &MainWindow::generate);

    // 定义left窗口，并加入down的布局
    QWidget *left = new QWidget;
    layoutdown->addWidget(left);

    // 定义left窗口的布局
    QVBoxLayout *layoutleft = new QVBoxLayout;
    left->setFixedSize(250, 120);
    left->setLayout(layoutleft);

    // left平均周转时间的展示
    QWidget *avgtime = new QWidget; // 定义窗口
    layoutleft->addWidget(avgtime); // 加入left窗口布局
    avgtime->setFixedSize(wide, high); // 设置大小

    QHBoxLayout *layoutavg = new QHBoxLayout;
    avgtime->setLayout(layoutavg); // 设置布局

    QLabel *labelavg1 = new QLabel("平均周转时间：", avgtime);
    layoutavg->addWidget(labelavg1);
    labelavg2 = new QLabel("0", avgtime);
    layoutavg->addWidget(labelavg2);

    // left平均带权周转时间
    QWidget *avgWtime = new QWidget;
    avgWtime->setFixedSize(250, high);
    layoutleft->addWidget(avgWtime); // 加入left布局

    QHBoxLayout *layoutavgW = new QHBoxLayout;
    avgWtime->setLayout(layoutavgW); // 设置布局

    QLabel *labelavgW1 = new QLabel("平均带权周转时间：", avgWtime);
    layoutavgW->addWidget(labelavgW1);
    labelavgW2 = new QLabel("0", avgWtime);
    layoutavgW->addWidget(labelavgW2);

    // left设置按钮
    button = new QPushButton("执行", left);
    button->setFixedSize(100, high);
    layoutleft->addWidget(button);

    // 执行信号槽
    QObject::connect(button, &QPushButton::clicked, this, &MainWindow::run);
}

MainWindow::~MainWindow()
{
    delete ui;
}
