#include "OdooProductsForm.hpp"

#include <QVariant>
#include <QFrame>

#include "Types.hpp"

OdooProductsForm::OdooProductsForm(QWidget *parent, OdooTaskType type) : TaskForm(parent)
{
    initDescriptions(type); // Initialize descriptions based on the task type

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Input file rows
    layout->addWidget(createFileInputRow(m_omegaLabelDescription, m_omegaFilePathEdit, m_omegaFileButton, m_omegaFileTypeCombo));
    fillInputCombo(m_omegaFileTypeCombo);
    connect(m_omegaFileButton, &QPushButton::clicked, this, &OdooProductsForm::openOmegaFileDialog);

    layout->addWidget(createFileInputRow(m_odooInputLabelDescription, m_odooInputFilePathEdit, m_odooInputFileButton, m_odooInputFileTypeCombo));
    fillInputCombo(m_odooInputFileTypeCombo);
    connect(m_odooInputFileButton, &QPushButton::clicked, this, &OdooProductsForm::openOdooOldFileDialog);

    // Separator
    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line);

    // Output file row
    layout->addWidget(createFileInputRow(m_odooOutputLabelDescription, m_odooOutputFilePathEdit, m_odooOutputFileButton, m_odooOutputFileTypeCombo));
    fillOutputCombo(m_odooOutputFileTypeCombo);
    connect(m_odooOutputFileButton, &QPushButton::clicked, this, &OdooProductsForm::openOdooNewFileDialog);

    setLayout(layout);
}

void OdooProductsForm::openOmegaFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(this, m_omegaOpenDescription, QString(), m_omegaFileExtension);
    if (!filePath.isEmpty())
        m_omegaFilePathEdit->setText(filePath);
}

void OdooProductsForm::openOdooOldFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(this, m_odooInputOpenDescription, QString(), m_odooInputFileExtension);
    if (!filePath.isEmpty())
        m_odooInputFilePathEdit->setText(filePath);
}

void OdooProductsForm::openOdooNewFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(this, m_odooOutputOpenDescription, QString(), m_odooOutputFileExtension);
    if (!filePath.isEmpty())
        m_odooOutputFilePathEdit->setText(filePath);
}

void OdooProductsForm::initDescriptions(OdooTaskType type)
{
    m_omegaLabelDescription = tr("Файл Omega:");
    m_omegaOpenDescription = tr("Виберіть файл Omega");
    m_omegaFileExtension = tr("CSV файли (*.csv)");

    m_odooInputLabelDescription = tr("Експортовані товари Odoo:");
    m_odooInputOpenDescription = tr("Виберіть файл з експортованими товарами Odoo");
    m_odooInputFileExtension = tr("CSV файли (*.csv)");

    if (type == OdooTaskType::UPDATE)
    {
        m_odooOutputLabelDescription = tr("Шлях для збереження файлу з оновленими товарами Odoo:");
        m_odooOutputOpenDescription = tr("Виберіть шлях для збереження файлу з оновленими товарами Odoo");
    }
    else if (type == OdooTaskType::CREATE)
    {
        m_odooOutputLabelDescription = tr("Шлях для збереження файлу з новими товарами Odoo:");
        m_odooOutputOpenDescription = tr("Виберіть шлях для збереження файлу з новими товарами Odoo");
    }
    m_odooOutputFileExtension = tr("CSV файли (*.csv)");
}

QWidget *OdooProductsForm::createFileInputRow(const QString &labelText, QLineEdit *&edit, QPushButton *&button, QComboBox *&combo)
{
    QWidget *widget = new QWidget(this);
    QHBoxLayout *rowLayout = new QHBoxLayout(widget);

    QLabel *label = new QLabel(labelText, widget);
    edit = new QLineEdit(widget);
    button = new QPushButton(tr("..."), widget);
    combo = new QComboBox(widget);

    // Set a fixed width for the button and combo with extensions:
    button->setFixedWidth(30);
    combo->setFixedWidth(50);

    // Optional: Set size policies for edit and combo to make them stretch relative to the button
    edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    combo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    rowLayout->addWidget(label);
    rowLayout->addWidget(edit);
    rowLayout->addWidget(button);
    rowLayout->addWidget(combo);

    return widget;
}

void OdooProductsForm::fillInputCombo(QComboBox *combo)
{
    combo->addItem(tr("CSV"), QVariant::fromValue(SageParser::ReaderFileType::CSV));
}

void OdooProductsForm::fillOutputCombo(QComboBox *combo)
{
    combo->addItem(tr("CSV"), QVariant::fromValue(SageParser::WriterFileType::CSV));
}

QVariantMap OdooProductsForm::getInputData() const
{
    QVariantMap inputData;
    inputData["omegaFilePath"] = m_omegaFilePathEdit->text();
    inputData["omegaFileType"] = m_omegaFileTypeCombo->currentData();
    inputData["odooOldFilePath"] = m_odooInputFilePathEdit->text();
    inputData["odooOldFileType"] = m_odooInputFileTypeCombo->currentData();
    inputData["odooNewFilePath"] = m_odooOutputFilePathEdit->text();
    inputData["odooNewFileType"] = m_odooOutputFileTypeCombo->currentData();
    return inputData;
}