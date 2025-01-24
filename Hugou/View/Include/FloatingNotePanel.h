#pragma once
#include <QLabel>
#include "ui_FloatingNotePanel.h"
#include "Const_Geometry.h"

class FloatingNotePanel :
    public QWidget
{
	Q_OBJECT
 
public:
    bool isPanelShown = false;
    FloatingNotePanel(QWidget* parent);
    void updateUi();
    void switchPanel();

signals:
    void SignalDarkenBackground();
    void SignalBrightenBackground();

public slots:
    void darkenOrBrightenRequest();
    void moveSlider(int buttonIndex);

private:
    Ui_FloatingNotePanel ui;
};

