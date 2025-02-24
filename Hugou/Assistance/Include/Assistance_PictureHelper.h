#pragma once
#include <QObject>
#include <QPixmap>
#include <QBitmap>
#include <QPainter> 
#include <QDebug>

class Assistance_PictureHelper :
    public QObject
{
public:
    static QPixmap cropPixmapIntoCircle(QPixmap& pixmap, int diameter);
};

