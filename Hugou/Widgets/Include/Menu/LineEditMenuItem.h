#pragma once
#include "MenuItem.h"
#include <QLineEdit>
class LineEditMenuItem :
    public MenuItem
{
    Q_OBJECT
public:
    LineEditMenuItem(const QString& title, QWidget* menu);
    void setText(const QString& text) { m_oldName = text;  m_lineEdit->setText(text); }
    void recall() override;
    QString save() override;

private:
    QString m_oldName = "";
    QLineEdit* m_lineEdit;
    void setupUi();
};

