#include "DynamicInputForm.hpp"

#include "Forms/OdooProductsForm.hpp"

DynamicInputForm::DynamicInputForm(QWidget *parent) : QWidget(parent), m_stackedWidget(new QStackedWidget(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Initialize specific task forms
    m_emptyForm = new TaskForm(this);
    m_odooUpdateProductsForm = new OdooProductsForm(this, OdooTaskType::UPDATE);
    m_odooNewProductsForm = new OdooProductsForm(this, OdooTaskType::CREATE);

    // Add task forms to the stacked widget
    m_stackedWidget->addWidget(m_emptyForm);
    m_stackedWidget->addWidget(m_odooUpdateProductsForm);
    m_stackedWidget->addWidget(m_odooNewProductsForm);

    layout->addWidget(m_stackedWidget);
    setLayout(layout);
}

void DynamicInputForm::setTaskForm(TaskType taskType)
{
    switch (taskType)
    {
    case TaskType::ODOO_UPDATE_PRODUCTS:
        m_stackedWidget->setCurrentWidget(m_odooUpdateProductsForm);
        break;
    case TaskType::ODOO_NEW_PRODUCTS:
        m_stackedWidget->setCurrentWidget(m_odooNewProductsForm);
        break;
    default:
        m_stackedWidget->setCurrentWidget(m_emptyForm);
        break;
    }
}

QVariantMap DynamicInputForm::getInputData() const
{
    return qobject_cast<TaskForm *>(m_stackedWidget->currentWidget())->getInputData();
}
