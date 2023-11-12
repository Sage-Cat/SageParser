#include "TaskWorker.hpp"
#include <QThread>

void TaskWorker::runTask(TaskType taskType, const QVariantMap &inputData)
{
    // Implementation of task logic
    for (int i = 0; i <= 100; ++i)
    {
        QThread::sleep(1);       // Simulate work
        emit progressUpdated(i); // Update progress
    }

    emit taskCompleted(); // Notify that the task is completed
}
 