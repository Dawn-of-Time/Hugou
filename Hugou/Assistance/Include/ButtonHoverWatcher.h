#pragma once

#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QEvent>
#include <QMovie>
#include <QPropertyAnimation>

class ButtonHoverWatcher :
    public QObject
{
    Q_OBJECT

public:
    enum class Direction
    {
        Horizontal,
        Vertical
    };

    QString default_res = "";
    QString hover_res = "";
    QLabel* backgroundLabel = Q_NULLPTR;
    QString default_color = "";
    QString hover_color = "";
    QPoint startPos;
    QPoint endPos;
    Direction direction;
    QString gifResource;
    ButtonHoverWatcher(QString default_res, QString hover_res, QObject* parent = Q_NULLPTR);
    ButtonHoverWatcher(QLabel* backgroundLabel, QString default_color, QString hover_color, QObject* parent = Q_NULLPTR);
    ButtonHoverWatcher(QString default_res, QString hover_res, QLabel* backgroundLabel, QString default_color, QString hover_color, QObject* parent = Q_NULLPTR);
    ButtonHoverWatcher(QPoint startPos, QPoint endPos, Direction direction, QObject* parent = Q_NULLPTR);
    ~ButtonHoverWatcher();
    virtual bool eventFilter(QObject* watched, QEvent* event) Q_DECL_OVERRIDE;
    void setResource(QString default_res, QString hover_res);
};
