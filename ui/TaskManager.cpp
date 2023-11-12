#include "TaskManager.hpp"

TaskManager::TaskManager(QObject *parent) : QObject(parent), worker(new TaskWorker())
{
    worker->moveToThread(&taskThread);

    connect(this, &TaskManager::startTask, worker, &TaskWorker::runTask);
    connect(worker, &TaskWorker::progressUpdated, this, &TaskManager::progressUpdated);
    connect(worker, &TaskWorker::taskCompleted, this, &TaskManager::taskCompleted);

    taskThread.start();
}

TaskManager::~TaskManager()
{
    taskThread.quit();
    taskThread.wait();
    delete worker;
}

void TaskManager::processTask(TaskType taskType, const QVariantMap &inputData)
{
    emit startTask(taskType, inputData); // Start the task in the worker
}
