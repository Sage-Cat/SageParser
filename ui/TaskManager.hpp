#pragma once

#include <QObject>
#include <QThread>
#include <QVariantMap>

#include "TaskType.hpp"
#include "TaskWorker.hpp"

class TaskManager : public QObject
{
    Q_OBJECT

public:
    explicit TaskManager(QObject *parent = nullptr);
    ~TaskManager();

    void processTask(TaskType taskType, const QVariantMap &inputData);

signals:
    void startTask(TaskType taskType, const QVariantMap &inputData); // Signal to start the task
    void progressUpdated(int value);
    void taskCompleted();

private:
    TaskWorker *worker; // Pointer to TaskWorker
    QThread taskThread;
};
