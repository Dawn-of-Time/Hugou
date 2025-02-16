//#include "FadeEffectButtonHoverWatcher.h"
//
//FadeEffectButtonHoverWatcher::FadeEffectButtonHoverWatcher(QString default_res, QString hover_res, QSize iconSize, QObject* parent) :
//    QObject(parent)
//{
//    this->default_res = default_res;
//    this->hover_res = hover_res;
//    this->iconSize = iconSize;
//}
//
//bool FadeEffectButtonHoverWatcher::eventFilter(QObject* watched, QEvent* event)
//{
//    FadeEffectButton* button = qobject_cast<FadeEffectButton*>(watched); // 转换为按钮类型
//    if (!button) {
//        return false;
//    }
//
//    if (event->type() == QEvent::Enter) {
//        if (!hover_res.isEmpty())
//        {
//            button->setIcon(QPixmap(this->hover_res));
//            return true;
//        }
//    }
//
//    if (event->type() == QEvent::Leave) {
//        if (!default_res.isEmpty())
//        {
//            button->setIcon(QPixmap(this->default_res));
//            return true;
//        }
//    }
//    return false;
//}