#ifndef DESKTOPPET_H
#define DESKTOPPET_H

#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QPainter>
#include <QClipboard>
#include <QMessageBox>
#include <QTimer>
#include <QHBoxLayout>
#include <QFileInfo>
#include <QTextEdit>
#include <QPushButton>
#include <functional> // 用于 std::function

class DesktopPet : public QWidget
{
    Q_OBJECT
public:
    explicit DesktopPet(QWidget *parent = nullptr);
    void setUsername(const QString &username);

    void setPasswordFillCallback(std::function<void()> callback);
    void setFileEncryptCallback(std::function<void(const QString&)> callback);

    // 新增：声明用于设置文本加解密回调的函数
    void setTextEncryptCallback(std::function<QString(const QString&)> callback);
    void setTextDecryptCallback(std::function<QString(const QString&)> callback);

    void showPet();
    void hidePet();

    void createReadOnlyTextDialog(QWidget* parent, const QString& title, const QString& labelText, const QString& text);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
private slots:
    void onFillPassword();
    void onHelp();
    void onShowContextMenu();

    // 新增：声明用于处理菜单点击事件的槽函数
    void onQuickEncrypt();
    void onQuickDecrypt();

private:
    void updatePosition();
    void createContextMenu();
    void updateAppearance();

    QLabel *usernameLabel;
    QMenu *contextMenu;
    QAction *fillPasswordAction;
    QAction *helpAction;

    // 新增：为新的菜单项声明QAction指针
    QAction *quickEncryptAction;
    QAction *quickDecryptAction;

    QPoint dragPosition;
    bool isDragging;

    QString username;
    std::function<void()> passwordFillCallback;
    std::function<void(const QString&)> fileEncryptCallback;

    // 新增：声明用于存储回调函数的成员变量
    std::function<QString(const QString&)> textEncryptCallback;
    std::function<QString(const QString&)> textDecryptCallback;
};

#endif // DESKTOPPET_H
