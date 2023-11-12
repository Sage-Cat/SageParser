#pragma once

#include <QDialog>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QWidget *parent = nullptr);
    void setMaximum(int value);
    void setValue(int value);

private:
    QProgressBar *progressBar;
    QPushButton *cancelButton;
};
