#include "MainWindow.hpp"

#include <QVBoxLayout>
#include <QMessageBox>

#include "TaskSelectionWidget.hpp"
#include "DynamicInputForm.hpp"
#include "ProgressDialog.hpp"
#include "TaskManager.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_currentTaskType(TaskType::NONE)
{
    m_taskSelectionWidget = new TaskSelectionWidget(this);
    m_dynamicInputForm = new DynamicInputForm(this);
    m_progressDialog = new ProgressDialog(this);
    m_processButton = new QPushButton(tr("Обробити"), this);
    m_taskManager = new TaskManager(this);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_taskSelectionWidget);
    layout->addWidget(m_dynamicInputForm);
    layout->addWidget(m_processButton); // Add the process button to the layout

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    makeConnections();
}

MainWindow::~MainWindow()
{
}

void MainWindow::onTaskSelected(TaskType task)
{
    m_dynamicInputForm->setTaskForm(task);
    m_currentTaskType = task;
}

void MainWindow::onProcessButtonClicked()
{
    if (m_currentTaskType != TaskType::NONE)
    {
        m_taskManager->processTask(m_currentTaskType, std::move(m_dynamicInputForm->getInputData()));
        m_progressDialog->show();
    }
    else
    {
        QMessageBox::warning(this, tr("Тип задачі не обрано"),
                             tr("Спершу оберіть тип задачі"));
    }
}

void MainWindow::onTaskProgressUpdated(int value)
{
    m_progressDialog->setValue(value);
}

void MainWindow::onTaskCompleted()
{
    m_progressDialog->hide();
}

void MainWindow::makeConnections()
{
    // Connect task selection
    connect(m_taskSelectionWidget, &TaskSelectionWidget::taskSelected, this, &MainWindow::onTaskSelected);

    // Connect Process button
    connect(m_processButton, &QPushButton::clicked, this, &MainWindow::onProcessButtonClicked);

    // Connect TaskManager signals to MainWindow slots
    connect(m_taskManager, &TaskManager::progressUpdated, this, &MainWindow::onTaskProgressUpdated);
    connect(m_taskManager, &TaskManager::taskCompleted, this, &MainWindow::onTaskCompleted);
}
