#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QVariantMap>

#include "TaskType.hpp"

class TaskForm;
class OdooProductsForm;

class DynamicInputForm : public QWidget
{
    Q_OBJECT

public:
    explicit DynamicInputForm(QWidget *parent = nullptr);

public slots:
    void setTaskForm(TaskType taskType);

    // get current Form InputData
    QVariantMap getInputData() const;

private:
    QStackedWidget *m_stackedWidget;
    TaskForm *m_emptyForm;
    OdooProductsForm *m_odooUpdateProductsForm, *m_odooNewProductsForm;
};
