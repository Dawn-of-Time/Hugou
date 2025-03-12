#pragma once
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

class ToolTip :
    public QWidget
{
public:
    ToolTip(const QString& content, QWidget * parent);
    void setContent(const QString& content) {};
    void show();

private:
    QString m_content;
    QVBoxLayout* m_layout;
    QLabel* m_contentLabel;
    void setupUi();
    void paintEvent(QPaintEvent* event) override;
};

