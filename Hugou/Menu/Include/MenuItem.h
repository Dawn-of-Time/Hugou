#pragma once
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class MenuItem :
    public QWidget
{
    Q_OBJECT
public:
    MenuItem(const QString& title, QWidget* parent = nullptr);
    void setCentralWidget(QWidget* widget);
    void disableRecallFunction() { m_recallButton->hide(); };
    QString name() { return m_title;  };
    virtual void recall() = 0;
    virtual QString save() = 0;

private:
    QString m_title = "";
    QVBoxLayout* m_layout;
    QWidget* m_titleWidget;
    QHBoxLayout* m_titleWidgetLayout;
    QLabel* m_titleLabel;
    QPushButton* m_recallButton;
    void setupUi();
};

