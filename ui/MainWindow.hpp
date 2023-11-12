#pragma once

#include <QMainWindow>
#include <QComboBox>
#include <QStackedWidget>
#include <QProgressBar>
#include <QPushButton>

#include "TaskType.hpp"

class TaskSelectionWidget;
class DynamicInputForm;
class ProgressDialog;
class TaskManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTaskSelected(TaskType task);
    void onProcessButtonClicked();
    void onTaskProgressUpdated(int value);
    void onTaskCompleted();

private:
    void makeConnections();

private:
    TaskSelectionWidget *m_taskSelectionWidget;
    DynamicInputForm *m_dynamicInputForm;
    ProgressDialog *m_progressDialog;
    QPushButton *m_processButton;
    TaskManager *m_taskManager;

    TaskType m_currentTaskType;
};
