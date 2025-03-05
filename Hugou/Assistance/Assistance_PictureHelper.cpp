#include "Assistance/Include/Assistance_PictureHelper.h"

QPixmap Assistance_PictureHelper::cropPixmapIntoCircle(QPixmap& pixmap, int diameter)
{
    int width = pixmap.width();
    int height = pixmap.height();
    diameter = qMin(diameter, qMin(width, height));

    QBitmap bitmap(width, height);
    bitmap.fill(Qt::color0);
    QPainter painter(&bitmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::color1);
    painter.translate(0, 0);
    painter.drawEllipse(0, 0, width + 2, height + 2);
    QPixmap result = pixmap.copy();
    //result.setDevicePixelRatio(factor);
    result.setMask(bitmap);
    qDebug() << result.size();
    return result;
}