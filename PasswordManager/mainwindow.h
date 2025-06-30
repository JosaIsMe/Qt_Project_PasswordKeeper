#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QSystemTrayIcon>
#include <QDir>
#include "encryptionhandler.h"
#include "fileencryptor.h"
#include "loginmanager.h"
#include "passwordgenerator.h"
#include "passwordstrengthchecker.h"
#include "desktoppet.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void switchPage(QWidget* wg);
    void login();
    void preLogin();
    void loginStatusShow(QString msg,qint64 t);
    void clear();
    QString createInputDialog(QWidget* parent, const QString& title, const QString& labelText, const QString& defaultBoxText = "");
    void createReadOnlyTextDialog(QWidget* parent, const QString& title, const QString& labelText, const QString& text);
    bool pushInfo(QString Pages, QString info);
    void showTopBar();
    void hideTopBar();
    void importPasswords(QString filePath);
    void exportPasswords(QString filePath);
    //void keyPressEvent();
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
private slots:
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void onShowMainWindow();

    void on_Login_PushButton_clicked();
    //void on_username_textChanged();
    void on_Login_RegisterCheckBox_checkStateChanged(const Qt::CheckState &arg1);

    void on_listWidget_doubleClicked(const QModelIndex &index);
    /*
    void on_Menu_Files_triggered();
    void on_Menu_Passwords_triggered();AA KWkbxy35rpTMdw2
    void on_Menu_Texts_triggered();
    */

    void on_ToFiles_clicked();

    void on_ToPasswordGenerators_clicked();

    void on_ToPasswords_clicked();

    void on_ToTexts_clicked();

    void on_PM_SearchButton_clicked();

    void on_PM_AddButton_clicked();

    void on_PM_UpdateButton_clicked();

    void on_PM_RemoveButton_clicked();

    void on_FE_EncryptionButton_clicked();

    void on_FE_DecryptionButton_clicked();

    void on_PG_GenerateButton_clicked();

    void on_PG_CheckBoxUpperCase_checkStateChanged(const Qt::CheckState &arg1);

    void on_PG_CheckBoxLowerCase_checkStateChanged(const Qt::CheckState &arg1);

    void on_PG_CheckBoxNumbers_checkStateChanged(const Qt::CheckState &arg1);

    void on_PG_CheckBoxSymbols_checkStateChanged(const Qt::CheckState &arg1);

    void on_TE_EncryptionButton_clicked();

    void on_TE_DecryptionButton_clicked();

    void on_Menu_ChangeVaultFilePath_triggered();

    void on_Menu_ChangePassword_triggered();

    void on_actionLog_Out_triggered();

    void on_actionGenerator_triggered();

    void on_actionPasswords_triggered();

    void on_actionTexts_triggered();

    void on_actionFiles_triggered();

    void on_actionChange_File_Path_triggered();

    void on_actionSwitch_to_table_assistant_triggered();

    void on_actionMinimize_to_Tray_triggered();

    void on_PM_SaveAsFileButton_clicked();

    void on_FE_ChooseDirectoryButton_clicked();

    void on_FE_ChooseFileButton_clicked();

    void on_FE_RandomIdentifierButton_clicked();


    void on_Login_UsernameEnterBox_returnPressed();

    void on_Login_PasswordEnterBox_returnPressed();

    void on_PG_ApplyButton_clicked();

    void on_PM_ReadFromFileButton_clicked();

private:
    struct LoginData{
        QString Password;
        QString Username;
        bool hasLoggedIn = 0;
        bool loginMode = 0;
        LoginManager *loginManager;
    } loginData;
    struct UserData{
        PasswordManager *passwordManager;
        FileEncryptor *fileEncryptor;
        QDir *defaultPath;
    } userData;
    struct PassGenData{
        bool Uppercase = 0;
        bool Lowercase = 0;
        bool Numbers = 0;
        bool Symbols = 0;
        PasswordGenerator *passwordGenerator;
    } passGenData;
    struct PassManagerData{
        QString queryContent;
        QString newUsername;
        QString newPassword;
        PasswordStrengthChecker passwordStrengthChecker;
    } passManagerData;
    struct FileEncryptorData{
        QString defaultFileOutputPath;
    } fileEncData;
    struct TextEncryptorData{
        QString text;
        EncryptionHandler * encryptionHandler;
    } textEncryptorData;

    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon;
    DesktopPet *desktopPet;
    void createTrayIcon();
    void closeEvent(QCloseEvent * event) override;

    //QStackedWidget *st;

public:

};
#endif // MAINWINDOW_H
