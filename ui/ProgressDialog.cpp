#include "ProgressDialog.hpp"

ProgressDialog::ProgressDialog(QWidget *parent) : QDialog(parent), progressBar(new QProgressBar(this)), cancelButton(new QPushButton(tr("Cancel"), this))
{
    progressBar->setRange(0, 100);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(progressBar);
    layout->addWidget(cancelButton);

    connect(cancelButton, &QPushButton::clicked, this, &ProgressDialog::reject);
    setLayout(layout);
}

void ProgressDialog::setMaximum(int value)
{
    progressBar->setMaximum(value);
}

void ProgressDialog::setValue(int value)
{
    progressBar->setValue(value);
    if (value == progressBar->maximum())
        accept();
}
