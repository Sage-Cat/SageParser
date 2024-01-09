#pragma once

#include <QObject>
#include <QVariantMap>

#include "TaskType.hpp"

class TaskWorker : public QObject
{
    Q_OBJECT

public:
    explicit TaskWorker(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void runTask(TaskType taskType, const QVariantMap &inputData);

signals:
    void progressUpdated(int value);
    void taskCompleted();
};
