#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QString>
#include <QVariantMap>

#include "Types.hpp"
#include "Forms/TaskForm.hpp"

enum class OdooTaskType
{
    NONE = 0,
    UPDATE,
    CREATE
};

class OdooProductsForm : public TaskForm
{
    Q_OBJECT

public:
    explicit OdooProductsForm(QWidget *parent = nullptr, OdooTaskType type = OdooTaskType::UPDATE);
    QVariantMap getInputData() const override;

private slots:
    void openOmegaFileDialog();
    void openOdooOldFileDialog();
    void openOdooNewFileDialog();

private:
    void initDescriptions(OdooTaskType type);
    QWidget *createFileInputRow(const QString &labelText, QLineEdit *&edit, QPushButton *&button, QComboBox *&combo);
    void fillInputCombo(QComboBox *combo);
    void fillOutputCombo(QComboBox *combo);

private:
    QString m_omegaLabelDescription,
        m_omegaOpenDescription,
        m_omegaFileExtension,
        m_odooInputLabelDescription,
        m_odooInputOpenDescription,
        m_odooInputFileExtension,
        m_odooOutputLabelDescription,
        m_odooOutputOpenDescription,
        m_odooOutputFileExtension;

private: // UI
    QLineEdit *m_omegaFilePathEdit;
    QPushButton *m_omegaFileButton;
    QComboBox *m_omegaFileTypeCombo;

    QLineEdit *m_odooInputFilePathEdit;
    QPushButton *m_odooInputFileButton;
    QComboBox *m_odooInputFileTypeCombo;

    QLineEdit *m_odooOutputFilePathEdit;
    QPushButton *m_odooOutputFileButton;
    QComboBox *m_odooOutputFileTypeCombo;
};
