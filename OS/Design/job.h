#ifndef JOB_H
#define JOB_H

#include <QObject>
#include <set>
#include <vector>

class JOB : public QObject {
    Q_OBJECT

public:
    JOB(){}

    struct work {
        QString name;    // 作业名
        int submittime;  // 到达时间
        int runtime;     // 运行时间
        int priority;    // 优先数
        int JOBstatus;   // 作业状态
        int begintime;   // 开始时间
        int endtime;     // 结束时间
        int returntime;  // 周转时间
        int wighReturntime; // 带权周转时间
        int PCBstatus;   // 作业状态
        int restime;     // 所需运行剩余时间
        int id;          // 所在表格行数

        work(QString name, int submittime, int runtime, int priority, int id) :
            name(name), submittime(submittime), runtime(runtime),
            priority(priority), restime(runtime), id(id) {}

        bool operator < (const work &rhs) const {
            return runtime < rhs.runtime;
        }
    };

    std::vector<work> unsubmit;
    std::set<work>ready;
    std::vector<work> running;
    std::vector<work> finish;

    void add(QString name, int submittime, int runtime, int priority, int id) {
        unsubmit.push_back(work(name, submittime, runtime, priority, id));
    }

signals:

};

#endif // JOB_H
