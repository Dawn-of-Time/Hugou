#include "Hugou.h"

Hugou::Hugou(QWidget* parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::FramelessWindowHint);
    floatingNoteDelayTimer = new QTimer(this);
    // Ui
    ui.setupUi(this);
    applyTheme();
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
    rightBlurEffect = new QGraphicsBlurEffect(this);
    rightBlurEffect->setBlurRadius(0);
    blurTimer.setInterval(5);
    ui.stackedWidget->setGraphicsEffect(rightBlurEffect);
    leftBlurEffect = new QGraphicsBlurEffect(this);
    leftBlurEffect->setBlurRadius(0);
    ui.asideBar->setGraphicsEffect(leftBlurEffect);
    
    //receiveSetting = setting;
    //if (!receiveSetting->readSetting()) // 读取设置并保存到所有settingMap中。一旦有任何错误，立即引发错误提示，并暂时采用默认设定
    //{
    //    raiseReadingSettingError();
    //    settingCommonMap = defaultCommonMap;
    //    settingExportMap = defaultExportMap;
    //}
    // 实际应用
    //receiveSetting->themeSetting->initTheme(this);
    //receiveSetting->applySetting(this);
    // ui应用
    //if (themeList.contains(settingCommonMap["theme"]))
    //    ui.themeBox->setCurrentIndex(themeList.indexOf(settingCommonMap["theme"]));
    //if (languageList.contains(settingCommonMap["language"]))
    //    ui.languageBox->setCurrentIndex(languageList.indexOf(settingCommonMap["language"]));

    // 信号与槽
    connect(ui.titleBar, &TitleBar::SignalBlur, this, &Hugou::blur);
    connect(ui.titleBar, &TitleBar::SignalClearBlur, this, &Hugou::clearBlur);
    connect(ui.asideBar, &AsideBar::SignalChangeStackedWidget, this, &Hugou::changeStackedWidget);
    connect(ui.settingsWidget, &Settings::SignalApplyTheme, this, &Hugou::applyTheme);
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
            qDebug() << theme;
            if (theme == "notExist") theme = "Default";
            if (theme == "invalid")
            {
                // 硬编码Default主题
                emit helper.triggerError(10101);
                theme = "Default";
            }
        }
    }
    QFile generalStyleFile(QString("res/theme/%1/general.qss").arg(theme));
    QFile asideBarStyleFile(QString("res/theme/%1/asideBar.qss").arg(theme));
    QFile settingsStyleFile(QString("res/theme/%1/settings.qss").arg(theme));
    if (!generalStyleFile.exists() || !asideBarStyleFile.exists() || !settingsStyleFile.exists())
    {
        // 硬编码Default主题
        SettingsHelper helper(this);
        emit helper.triggerError(10100);
        theme = "Default";
    }
    generalStyleFile.open(QIODeviceBase::ReadOnly);
    asideBarStyleFile.open(QIODeviceBase::ReadOnly);
    settingsStyleFile.open(QIODeviceBase::ReadOnly);
    this->setStyleSheet(generalStyleFile.readAll());
    ui.asideBar->setStyleSheet(asideBarStyleFile.readAll());
    ui.settingsWidget->setStyleSheet(settingsStyleFile.readAll());
    generalStyleFile.close();
    asideBarStyleFile.close();
    settingsStyleFile.close();
}

void Hugou::changeStackedWidget(int index)
{
    ui.stackedWidget->setCurrentIndex(index);
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
    blurTimer.disconnect();
    connect(&blurTimer, &QTimer::timeout, [&]()
        {
            if (blurRadius < 60)
            {
                blurRadius += 6;
                rightBlurEffect->setBlurRadius(blurRadius);
                leftBlurEffect->setBlurRadius(blurRadius);
            }
            else blurTimer.stop();
        });
    blurTimer.start();
}

void Hugou::clearBlur()
{
    blurTimer.disconnect();
    connect(&blurTimer, &QTimer::timeout, [&]()
        {
            if (blurRadius > 0) {
                blurRadius -= 10;
                rightBlurEffect->setBlurRadius(blurRadius);
                leftBlurEffect->setBlurRadius(blurRadius);
            }
            else blurTimer.stop();
        });
    blurTimer.start();
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
    ui.titleBar->floatingNotePanel->updateUi(this);
}