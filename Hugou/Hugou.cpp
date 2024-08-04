#include "Hugou.h"

Hugou::Hugou(QWidget* parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::FramelessWindowHint);
    // Ui
    ui.setupUi(this);
    HWND hWnd = (HWND)winId();
    LONG_PTR style = GetWindowLongPtrW(hWnd, GWL_STYLE);
    SetWindowLongPtr(
        hWnd,
        GWL_STYLE,
        style
        | WS_MINIMIZEBOX
        | WS_MAXIMIZEBOX
        | WS_CAPTION
        | CS_DBLCLKS
        | WS_THICKFRAME
    );

    // 设置模糊
    blurEffect = new QGraphicsBlurEffect(this);
    blurEffect->setBlurRadius(0);
    blurEffect->setBlurHints(QGraphicsBlurEffect::QualityHint);
    blurTimer.setInterval(100);
    ui.blurWidget->setGraphicsEffect(blurEffect);

    // 信号与槽
    connect(ui.titleBar->ui.floatingNotePanelButton, &QPushButton::clicked, ui.floatingNotePanel, &FloatingNotePanel::blurOrClearBlurRequest);
    connect(ui.floatingNotePanel, &FloatingNotePanel::blurBackground, this, &Hugou::blur);
    connect(ui.floatingNotePanel, &FloatingNotePanel::clearBackground, this, &Hugou::clearBlur);
    connect(ui.asideBar, &AsideBar::SignalChangeStackedWidget, this, &Hugou::changeStackedWidget);
    connect(ui.settingsWidget, &Settings::SignalApplyTheme, this, &Hugou::applyTheme);

    applyTheme();
}

Hugou::~Hugou()
{}

void Hugou::applyTheme(QString theme)
{
    if (theme.isEmpty())
    {
        SettingsHelper helper(this);
        if (helper.verifySettings())
        {
            theme = helper.readSettings("theme");
            if (theme == "notExist") theme = "Default";
            if (theme == "invalid")
            {
                // 硬编码Default主题
                emit helper.triggerError(10102);
                theme = "Default";
            }
        }
    }

    ui.globalTop->setSource("res/qml/themeApplyMedia.qml");
    ui.globalTop->setHint("Upcoming theme: " + theme);
    ui.globalTop->fadeIn();
    loader = new ThemeLoadThread(theme);
    connect(loader, &ThemeLoadThread::themeResourcePrepared, this, &Hugou::applyStyleSheet);
    loader->start();
}

void Hugou::applyStyleSheet(QString generalStyleFile, QString asideBarStyleFile, QString settingsStyleFile)
{
    this->setStyleSheet(generalStyleFile);
    ui.asideBar->setStyleSheet(asideBarStyleFile);
    ui.settingsWidget->setStyleSheet(settingsStyleFile);
    ui.globalTop->fadeOut();
}

void Hugou::changeStackedWidget(int index)
{
    ui.stackedWidget->setCurrentIndex(index);
    //raiseReadingSettingError();
}

void Hugou::raiseReadingSettingError() { floatingNoteManager.raiseFloatingNote(this, FloatingNote::Error, readingSettingErrorHint);}

void Hugou::raiseSavingSettingError() { floatingNoteManager.raiseFloatingNote(this, FloatingNote::Error, savingSettingErrorHint); }

Hugou::Area Hugou::getArea(QPoint mousePos)
{
    currentMainWindowGeometry = this->geometry();
    if (mousePos.y() >= 0 && mousePos.y() < edgeWidth)
    { 
        if (mousePos.x() >= 0 && mousePos.x() < edgeWidth) { return TOPLEFT; }
        else if (mousePos.x() >= edgeWidth && mousePos.x() <= (currentMainWindowGeometry.width() - edgeWidth)) { return TOP; }
        else if (mousePos.x() > (currentMainWindowGeometry.width() - edgeWidth) && mousePos.x() <= currentMainWindowGeometry.width()) { return TOPRIGHT; }
    }
    else if (mousePos.y() >= edgeWidth && mousePos.y() <= (currentMainWindowGeometry.height() - edgeWidth))
    {
        if (mousePos.x() >= 0 && mousePos.x() < edgeWidth) { return LEFT; }
        else if (mousePos.x() > (currentMainWindowGeometry.width() - edgeWidth) && mousePos.x() <= currentMainWindowGeometry.width()) { return RIGHT; }
    }
    else if (mousePos.y() > (currentMainWindowGeometry.height() - edgeWidth) && mousePos.y() < currentMainWindowGeometry.height())
    {
        if (mousePos.x() >= 0 && mousePos.x() < edgeWidth) { return BOTTOMLEFT; }
        else if (mousePos.x() >= edgeWidth && mousePos.x() <= (currentMainWindowGeometry.width() - edgeWidth)) { return BOTTOM; }
        else if (mousePos.x() > (currentMainWindowGeometry.width() - edgeWidth) && mousePos.x() <= currentMainWindowGeometry.width()) { return BOTTOMRIGHT; }
    }
    if (ui.titleBar->isOnDragZone(mousePos))
    {
        return DRAGZONE;
    }
    return NOTAREA;
}

QRect Hugou::customScale(Area area, QRect currentMainWindowGeometry, QPoint change)
{
    QRect tempMainWindowGeometry = currentMainWindowGeometry;
    QRect newMainWindowGeometry = currentMainWindowGeometry;
    bool widthInvalid = (tempMainWindowGeometry.width() < mainWindowWidth);
    bool heightInvalid = (tempMainWindowGeometry.height() < mainWindowHeight);
    switch (area)
    {
    case TOPLEFT:
    {
        tempMainWindowGeometry.setTopLeft(currentMainWindowGeometry.topLeft() + change);
        if (heightInvalid) tempMainWindowGeometry.setTop(tempMainWindowGeometry.top() - change.y());
        if (widthInvalid) tempMainWindowGeometry.setLeft(tempMainWindowGeometry.left() - change.x());
        break;
    }
    case TOP:
    {
        tempMainWindowGeometry.setTop(currentMainWindowGeometry.top() + change.y());
        if (heightInvalid) tempMainWindowGeometry.setTop(tempMainWindowGeometry.top() - change.y());
        break;
    }
    case TOPRIGHT:
    {
        tempMainWindowGeometry.setTopRight(currentMainWindowGeometry.topRight() + change);
        if (heightInvalid) tempMainWindowGeometry.setTop(tempMainWindowGeometry.top() - change.y());
        if (widthInvalid) tempMainWindowGeometry.setRight(tempMainWindowGeometry.right() - change.x());
        break;
    }
    case LEFT:
    {
        tempMainWindowGeometry.setLeft(currentMainWindowGeometry.left() + change.x());
        if (widthInvalid) tempMainWindowGeometry.setLeft(tempMainWindowGeometry.left() - change.x());
        break;
    }
    case RIGHT:
    {
        tempMainWindowGeometry.setRight(currentMainWindowGeometry.right() + change.x());
        if (widthInvalid) tempMainWindowGeometry.setRight(tempMainWindowGeometry.right() - change.x());
        break;
    }
    case BOTTOMLEFT:
    {
        tempMainWindowGeometry.setBottomLeft(currentMainWindowGeometry.bottomLeft() + change);
        if (heightInvalid) tempMainWindowGeometry.setBottom(tempMainWindowGeometry.bottom() - change.y());
        if (widthInvalid) tempMainWindowGeometry.setLeft(tempMainWindowGeometry.left() - change.x());
        break;
    }
    case BOTTOM:
    {
        tempMainWindowGeometry.setBottom(currentMainWindowGeometry.bottom() + change.y());
        if (heightInvalid) tempMainWindowGeometry.setBottom(tempMainWindowGeometry.bottom() - change.y());
        break;
    }
    case BOTTOMRIGHT:
    {
        tempMainWindowGeometry.setBottomRight(currentMainWindowGeometry.bottomRight() + change);
        if (heightInvalid) tempMainWindowGeometry.setBottom(tempMainWindowGeometry.bottom() - change.y());
        if (widthInvalid) tempMainWindowGeometry.setRight(tempMainWindowGeometry.right() - change.x());
        break;
    }
    case NOTAREA: {break; }
    default: {break; }
    }
    newMainWindowGeometry = tempMainWindowGeometry;
    return newMainWindowGeometry;
}
// 槽函数
void Hugou::openPDFEditFunction()
{
    //FileImportDialog* fileImportDialog = new FileImportDialog(this);
    //fileImportDialog->show();
    //connect(fileImportDialog, &FileImportDialog::uploadSuccessed, [&](QString fileName) 
    //    {
    //        pdfEdit = new PDFEdit(fileName);
    //    });
}

void Hugou::blur()
{
    screenShot = QPixmap(ui.asideBarAndStackedWidget->size());
    ui.blurWidget->setHidden(false);
    ui.asideBarAndStackedWidget->render(&screenShot);
    QPalette palette;
    palette.setBrush(ui.blurWidget->backgroundRole(), QBrush(screenShot));
    ui.blurWidget->setPalette(palette);
    ui.blurWidget->setAutoFillBackground(true);
    QPropertyAnimation* blurAnimation = new QPropertyAnimation(blurEffect, "blurRadius");
    blurAnimation->setDuration(100);
    blurAnimation->setStartValue(blurEffect->blurRadius());
    blurAnimation->setEndValue(30);
    if (sender()->objectName() == "notePanel") connect(blurAnimation, &QPropertyAnimation::finished, [&]() {ui.floatingNotePanel->switchPanel(); });
    blurAnimation->start(QPropertyAnimation::DeleteWhenStopped); 
}

void Hugou::clearBlur()
{
    screenShot = QPixmap(ui.asideBarAndStackedWidget->size());
    ui.asideBarAndStackedWidget->render(&screenShot);
    QPalette palette;
    palette.setBrush(ui.blurWidget->backgroundRole(), QBrush(screenShot));
    ui.blurWidget->setPalette(palette);
    ui.blurWidget->setAutoFillBackground(true);
    QPropertyAnimation* blurAnimation = new QPropertyAnimation(blurEffect, "blurRadius");
    blurAnimation->setDuration(100); 
    blurAnimation->setStartValue(blurEffect->blurRadius());
    blurAnimation->setEndValue(0);
    if (sender()->objectName() == "notePanel") connect(blurAnimation, &QPropertyAnimation::finished, [&]() {ui.blurWidget->setHidden(true); ui.floatingNotePanel->switchPanel(); });
    if (sender()->objectName() == "globalTop") connect(blurAnimation, &QPropertyAnimation::finished, [&]() {ui.blurWidget->setHidden(true); ui.globalTop->switchTop(); ui.globalTop->removeSource(); });
    blurAnimation->start(QPropertyAnimation::DeleteWhenStopped);
}

// 父类函数重写
bool Hugou::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
    MSG* msg = static_cast<MSG*>(message);
    switch (msg->message)
    {
        // 注：拦截WM_NCCALCSIZE消息，以防后续坐标计算错位。
    case WM_NCCALCSIZE:
    {
        *result = HTNOWHERE;
        return true;
    }
    case WM_ACTIVATE:
    {
        MARGINS margins = { 0, 1, 0, 1 };
        HRESULT hr = DwmExtendFrameIntoClientArea(msg->hwnd, &margins);
        *result = hr;
        return true;
    }
    case WM_NCHITTEST:
    {
        *result = HTCLIENT;
        // 为了获取到正确的全局鼠标位置，应将GET_X_LPARAM和GET_Y_LPARAM得到的结果除以缩放倍数。
        double scale = getScale();
        QPoint globalPos = QPoint(GET_X_LPARAM(msg->lParam), GET_Y_LPARAM(msg->lParam)) / scale;
        QPoint windowPos = globalPos - this->pos();

        Area area = getArea(windowPos);
        switch (area)
        {
        case TOPLEFT: {*result = HTTOPLEFT; break; }
        case TOP: { *result = HTTOP; break; }
        case TOPRIGHT: {*result = HTTOPRIGHT; break; }
        case LEFT: {*result = HTLEFT; break; }
        case RIGHT: {*result = HTRIGHT; break; }
        case BOTTOMLEFT: {*result = HTBOTTOMLEFT; break; }
        case BOTTOM: {*result = HTBOTTOM; break; }
        case BOTTOMRIGHT: {*result = HTBOTTOMRIGHT; break; }
        case DRAGZONE: {*result = HTCAPTION; break; }
        case NOTAREA: {*result = HTCLIENT; break; }
        default: {break; }
        }

        QPushButton* button = ui.titleBar->ui.scaledButton;
        QPoint localPos = button->mapFromGlobal(globalPos);
        if (ui.titleBar->isOnMaxButton(windowPos))
        {
            // 这里的触发机制如下：
            // 当控件未接受到Enter事件时，undermouse()返回false。因此，在鼠标首次悬浮于最大化按钮之上时（undermouse()为false），
            // 发送Enter事件，此后当鼠标在最大化按钮区域内移动时，undermouse()为true。
            setCursor(QCursor(Qt::PointingHandCursor));
            QMouseEvent mouseEvent = QMouseEvent(button->underMouse() ? QEvent::MouseMove : QEvent::Enter, localPos, globalPos, Qt::NoButton, Qt::NoButton, Qt::NoModifier);
            QCoreApplication::sendEvent(button, &mouseEvent);
            button->update();
            *result = HTMAXBUTTON;
            return true;
        }
        else
        {
            if (button->underMouse())
            {
                // 同样的，只有接受到Leave事件后，undermouse()才返回false。
                setCursor(QCursor(Qt::ArrowCursor));
                QMouseEvent mouseEvent = QMouseEvent(QEvent::Leave, localPos, globalPos, Qt::NoButton, Qt::NoButton, Qt::NoModifier);
                QCoreApplication::sendEvent(button, &mouseEvent);
                button->update();
                return true;
            }
        }
        if (*result != HTCLIENT) return true;
        return false;
    }
    case WM_NCLBUTTONDOWN:
    {
        if (msg->wParam == HTMAXBUTTON) {
            QPushButton* button = ui.titleBar->ui.scaledButton;
            QMouseEvent mouseEvent = QMouseEvent(QEvent::MouseButtonPress, QPoint(), QPoint(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
            QCoreApplication::sendEvent(button, &mouseEvent);
            *result = HTNOWHERE;
            return true;
        }
        break;
    }
    case WM_NCLBUTTONUP:
    {
        if (msg->wParam == HTMAXBUTTON) {
            QPushButton* button = ui.titleBar->ui.scaledButton;
            QMouseEvent mouseEvent = QMouseEvent(QEvent::MouseButtonRelease, QPoint(), QPoint(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
            QCoreApplication::sendEvent(button, &mouseEvent);
            return true;
        }
        break;
    }
    case WM_NCMOUSEHOVER:
    case WM_NCMOUSELEAVE:
    case WM_NCMOUSEMOVE:
    {
        if (msg->wParam == HTMAXBUTTON)
        {
            *result = HTNOWHERE;
            return true;
        }
    }
    }
    return QWidget::nativeEvent(eventType, message, result);
}

void Hugou::changeEvent(QEvent* event) {
    if (event->type() == QEvent::WindowStateChange) {
        switch (windowState()) {
        case Qt::WindowMaximized: {
            ui.titleBar->ui.scaledButton->setIcon(QIcon("res/ico/restore_w.png"));
            int border = GetSystemMetrics(SM_CXSIZEFRAME);
            setContentsMargins(border, border, border, border);
            break;
        }
        case Qt::WindowNoState:
            ui.titleBar->ui.scaledButton->setIcon(QIcon("res/ico/maximum_w.png"));
            setContentsMargins(0, 0, 0, 0);
            break;
        default:
            break;
        }
    }
    QWidget::changeEvent(event);
}

void Hugou::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    // 浮动消息
    if (floatingNoteManager.isAnimating || (floatingNoteManager.getShownFloatingNote()))
    {
        //qDebug() << "***Start adjusting***";
        floatingNoteManager.adjustFloatingNote(this);
    }

    // 设置页表单
    ui.settingsWidget->adjustSizeHint();
    ui.floatingNotePanel->updateUi(this);
    ui.blurWidget->resize(this->width(), this->height() - titleFrameHeight);
    ui.globalTop->updateUi(this);

    if (!ui.blurWidget->isHidden())
    {
        screenShot = QPixmap(ui.asideBarAndStackedWidget->size());
        ui.asideBarAndStackedWidget->render(&screenShot);
        QPalette palette;
        palette.setBrush(ui.blurWidget->backgroundRole(), QBrush(screenShot));
        ui.blurWidget->setPalette(palette);
        ui.blurWidget->setAutoFillBackground(true);
    }
}