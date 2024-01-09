#pragma once

#include <QWidget>
#include <QMap>
#include <QString>
#include <QVariant>
#include <QVariantMap>

#include "Types.hpp"

class TaskForm : public QWidget
{
    Q_OBJECT
public:
    explicit TaskForm(QWidget *parent = nullptr) : QWidget(parent) {}
    virtual ~TaskForm() = default;

    virtual QVariantMap getInputData() const { return QVariantMap(); };
};
