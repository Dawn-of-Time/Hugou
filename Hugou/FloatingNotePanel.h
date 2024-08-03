#pragma once
#include <QLabel>
#include "ui_FloatingNotePanel.h"
#include "Const.h"

class FloatingNotePanel :
    public QLabel
{
	Q_OBJECT
 
public:
    bool isPanelShown = false;
    FloatingNotePanel(QWidget* parent);
    void updateUi(QWidget* Hugou);
    void switchPanel();

signals:
    void blurBackground();
    void clearBackground();

public slots:
    void blurOrClearBlurRequest();

private:
    Ui_FloatingNotePanel ui;
};

