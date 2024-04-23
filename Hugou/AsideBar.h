#pragma once
#include <QWidget>
#include <QStyle>
#include <QApplication>
#include "ui_AsideBar.h"

class AsideBar :
    public QWidget
{
    Q_OBJECT

public:
    AsideBar(QWidget* parent);
    void showEvent(QShowEvent* event) override;

signals:
    void SignalChangeStackedWidget(int index);

protected slots:
    void switchOverStackedWidget();

private:
    Ui_AsideBar ui;
};

