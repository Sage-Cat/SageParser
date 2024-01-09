#pragma once

#include <QWidget>
#include <QComboBox>

enum class TaskType;

class TaskSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskSelectionWidget(QWidget *parent = nullptr);

signals:
    void taskSelected(TaskType task);

private slots:
    void onComboBoxIndexChanged(int index);

private:
    QComboBox *taskComboBox;
};
