#include "TaskSelectionWidget.hpp"

#include <QVBoxLayout>

#include "TaskType.hpp"

TaskSelectionWidget::TaskSelectionWidget(QWidget *parent) : QWidget(parent)
{
    taskComboBox = new QComboBox(this);
    taskComboBox->addItem("Обрати завдання", QVariant::fromValue(TaskType::NONE));
    taskComboBox->addItem("Оновити існуючі Odoo товари", QVariant::fromValue(TaskType::ODOO_UPDATE_PRODUCTS));
    taskComboBox->addItem("Створити нові Odoo товари", QVariant::fromValue(TaskType::ODOO_NEW_PRODUCTS));

    connect(taskComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxIndexChanged(int)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(taskComboBox);
    setLayout(layout);
}

void TaskSelectionWidget::onComboBoxIndexChanged(int index)
{
    QVariant selectedData = taskComboBox->itemData(index);
    if (selectedData.canConvert<TaskType>())
    {
        TaskType selectedTask = qvariant_cast<TaskType>(selectedData);
        emit taskSelected(selectedTask);
    }
}
