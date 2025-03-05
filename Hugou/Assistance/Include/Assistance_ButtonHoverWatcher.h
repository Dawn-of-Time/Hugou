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
    QLabel* backgroundLabel = nullptr;
    QString default_color = "";
    QString hover_color = "";
    QPoint startPos;
    QPoint endPos;
    Direction direction;
    QString gifResource;
    ButtonHoverWatcher(const QString& default_res, const QString& hover_res, QObject* parent = nullptr);
    //ButtonHoverWatcher(QLabel* backgroundLabel, const QString& default_color, const QString& hover_color, QObject* parent = nullptr);
    //ButtonHoverWatcher(const QString& default_res, const QString& hover_res, QLabel* backgroundLabel, const QString& default_color, const QString& hover_color, QObject* parent = nullptr);
    //ButtonHoverWatcher(const QPoint& startPos, const QPoint& endPos, Direction direction, QObject* parent = nullptr);
    ~ButtonHoverWatcher();
    virtual bool eventFilter(QObject* watched, QEvent* event) Q_DECL_OVERRIDE;
    void setResource(const QString& default_res, const QString& hover_res);
};
