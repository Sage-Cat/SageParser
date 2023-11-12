#pragma once

#include <QMetaType>

enum class TaskType
{
    NONE = 0,
    ODOO_UPDATE_PRODUCTS,
    ODOO_NEW_PRODUCTS
};

Q_DECLARE_METATYPE(TaskType)