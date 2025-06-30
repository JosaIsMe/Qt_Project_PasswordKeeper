#include "desktoppet.h"
#include "qpushbutton.h"
#include <QKeySequence>
#include <QClipboard>

DesktopPet::DesktopPet(QWidget *parent)
    : QWidget(parent), isDragging(true)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(120, 40);
    setAcceptDrops(true);

    usernameLabel = new QLabel(this);
    usernameLabel->setAlignment(Qt::AlignCenter);
    usernameLabel->setStyleSheet(
        "QLabel {"
        "  background-color: rgba(50, 50, 100, 200);"
        "  color: white;"
        "  border-radius: 10px;"
        "  font-weight: bold;"
        "  padding: 5px;"
        "}"
        );
    usernameLabel->setGeometry(0,0,width(),height());
    createContextMenu();
    updatePosition();
}

void DesktopPet::updatePosition(){
    QRect screenGeo = QApplication::primaryScreen()->geometry();
    move(screenGeo.width() - width() - 20, 20);
}

void DesktopPet::setUsername(const QString &username){
    this->username = username;
    usernameLabel->setText(username);
    updateAppearance();
}

void DesktopPet::setPasswordFillCallback(std::function<void()> cb){
    passwordFillCallback = cb;
}

void DesktopPet::setFileEncryptCallback(std::function<void(const QString&)> cb){
    fileEncryptCallback = cb;
}

void DesktopPet::showPet(){
    updatePosition();
    show();
    raise();
    activateWindow();
}

void DesktopPet::hidePet(){
    hide();
}

void DesktopPet::createReadOnlyTextDialog(QWidget* parent, const QString& title, const QString& labelText, const QString& text) {
    QDialog dialog(parent);
    dialog.setWindowTitle(title);

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    QLabel* label = new QLabel(labelText, &dialog);
    layout->addWidget(label);

    QTextEdit* textEdit = new QTextEdit(&dialog);
    textEdit->setReadOnly(true);
    textEdit->setPlainText(text);
    layout->addWidget(textEdit);

    QPushButton* button = new QPushButton("确定", &dialog);
    layout->addWidget(button);

    dialog.setModal(true);

    QObject::connect(button, &QPushButton::clicked, [&dialog] {
        dialog.accept();
    });

    dialog.exec();
}


void DesktopPet::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QColor(30,30,70,150));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(),10,10);
}

void DesktopPet::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
        isDragging = true;
        setStyleSheet("background-color: rgba(40, 40, 90, 200);");
    }
}

void DesktopPet::mouseMoveEvent(QMouseEvent *event){
    if(isDragging && (event->buttons() & Qt::LeftButton)){
        move(event->globalPosition().toPoint()-dragPosition);
        event->accept();
    }
}

void DesktopPet::mouseReleaseEvent(QMouseEvent *event){
    if(isDragging && (event->buttons() & Qt::LeftButton)){
        isDragging = false;
        event->accept();
        setStyleSheet("");
    }
}

void DesktopPet::enterEvent(QEnterEvent *event){
    Q_UNUSED(event);
    QTimer::singleShot(300,this,[this](){
        if(underMouse()) {
            onShowContextMenu();
        }
    });
}

void DesktopPet::dragEnterEvent(QDragEnterEvent *event){
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void DesktopPet::dropEvent(QDropEvent *event){
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();

        for (const QUrl &url : urlList) {
            QString filePath = url.toLocalFile();

            if (!QFileInfo(filePath).isFile()) {
                qDebug() << "忽略目录:" << filePath;
                continue;
            }
            fileEncryptCallback(filePath);
            qDebug() << "已接收文件:" << filePath;
        }

        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}
//void DesktopPet::leaveEvent(QEvent *event){
//    Q_UNUSED(event);
//}

void DesktopPet::mouseDoubleClickEvent(QMouseEvent *event){
    Q_UNUSED(event);
    parentWidget()->show();
    hidePet();
}

void DesktopPet::onFillPassword(){
    if(passwordFillCallback){
        passwordFillCallback();
    }
    usernameLabel->setText("Password Copied!");
    QTimer::singleShot(2000,this,[this](){
        usernameLabel->setText(username);
    });
}

void DesktopPet::onHelp(){
    createReadOnlyTextDialog(this,QObject::tr("桌面助手帮助"),QObject::tr("如何使用桌面助手？"),QObject::tr("当你把鼠标悬浮在桌面助手上时，可以看到菜单项。\n\n将待加密（已加密）的文本复制到剪贴板上，再点击菜单项中的快速加密（解密）剪贴板，可以快速将剪贴板上的文本进行加密（解密）。加密（解密）后的文本将替换原有剪贴板上的内容。\n将即将访问的站点名称复制到剪贴板上，点击菜单项中的自动填充密码，可用对应站点的密码填充剪贴板。\n将文件拖动至剪贴板，文件会自动被加密，加密的文件会出现在默认路径下。"));
}

void DesktopPet::onShowContextMenu(){
    if (contextMenu) {
        contextMenu->exec(QCursor::pos());
    }
}

/*void DesktopPet::createContextMenu(){
    contextMenu = new QMenu(this);
    contextMenu->setStyleSheet(
        "QMenu {"
        "  background-color: #333366;"
        "  color: white;"
        "  border: 1px solid #555599;"
        "  border-radius: 5px;"
        "}"
        "QMenu::item {"
        "  padding: 5px 20px;"
        "}"
        "QMenu::item:selected {"
        "  background-color: #555599;"
        "}"
        );
    fillPasswordAction = new QAction("快速填充密码", this);
    connect(fillPasswordAction, &QAction::triggered, this, &DesktopPet::onFillPassword);


    //QWidgetAction *encryptAction = new QWidgetAction(this);
    //encryptAction->setDefaultWidget(encryptWidget);
    helpAction = new QAction("帮助",this);

    // 添加到菜单
    contextMenu->addAction(fillPasswordAction);
    contextMenu->addSeparator();
    contextMenu->addAction(helpAction);
    //contextMenu->addAction(encryptAction);
}*/

void DesktopPet::createContextMenu(){
    contextMenu = new QMenu(this);
    contextMenu->setStyleSheet(
        "QMenu {"
        "  background-color: #333366;"
        "  color: white;"
        "  border: 1px solid #555599;"
        "  border-radius: 5px;"
        "}"
        "QMenu::item {"
        "  padding: 5px 20px;"
        "}"
        "QMenu::item:selected {"
        "  background-color: #555599;"
        "}"
        );
    fillPasswordAction = new QAction("快速填充密码", this);
    connect(fillPasswordAction, &QAction::triggered, this, &DesktopPet::onFillPassword);

    quickEncryptAction = new QAction("快速加密剪贴板", this);
    quickEncryptAction->setShortcut(QKeySequence("Ctrl+Shift+E"));
    connect(quickEncryptAction, &QAction::triggered, this, &DesktopPet::onQuickEncrypt);

    quickDecryptAction = new QAction("快速解密剪贴板", this);
    quickDecryptAction->setShortcut(QKeySequence("Ctrl+Shift+D"));
    connect(quickDecryptAction, &QAction::triggered, this, &DesktopPet::onQuickDecrypt);

    helpAction = new QAction("帮助",this);
    connect(helpAction, &QAction::triggered, this, &DesktopPet::onHelp);

    contextMenu->addAction(fillPasswordAction);
    contextMenu->addSeparator();
    contextMenu->addAction(quickEncryptAction);
    contextMenu->addAction(quickDecryptAction);
    contextMenu->addSeparator();
    contextMenu->addAction(helpAction);
}

//void DesktopPet::on

void DesktopPet::updateAppearance(){
    int width = qMax(120, username.length() * 10 + 40);
    setFixedSize(width, 40);
    usernameLabel->setGeometry(0, 0, width, height());
    usernameLabel->setText(username);
}

//新增部分
void DesktopPet::setTextEncryptCallback(std::function<QString(const QString&)> cb){
    textEncryptCallback = cb;
}

void DesktopPet::setTextDecryptCallback(std::function<QString(const QString&)> cb){
    textDecryptCallback = cb;
}

void DesktopPet::onQuickEncrypt(){
    if (textEncryptCallback) {
        QString originalText = QApplication::clipboard()->text();
        if (originalText.isEmpty()){
            usernameLabel->setText("剪贴板为空!");
        } else {
            QString encryptedText = textEncryptCallback(originalText);
            QApplication::clipboard()->setText(encryptedText);
            usernameLabel->setText("已加密!");
        }
        // 这个视觉反馈逻辑与 onFillPassword 中的逻辑类似
        QTimer::singleShot(2000, this, [this](){
            usernameLabel->setText(username);
        });
    }
}

void DesktopPet::onQuickDecrypt(){
    if (textDecryptCallback) {
        QString originalText = QApplication::clipboard()->text();
        if (originalText.isEmpty()){
            usernameLabel->setText("剪贴板为空!");
        } else {
            QString decryptedText = textDecryptCallback(originalText);
            if(decryptedText.isEmpty()){
                // 解密失败（例如，密钥错误或数据损坏）通常会返回空字符串
                usernameLabel->setText("解密失败!");
            } else {
                QApplication::clipboard()->setText(decryptedText);
                usernameLabel->setText("已解密!");
            }
        }
        // 这个视觉反馈逻辑与 onFillPassword 中的逻辑类似
        QTimer::singleShot(2000, this, [this](){
            usernameLabel->setText(username);
        });
    }
}
