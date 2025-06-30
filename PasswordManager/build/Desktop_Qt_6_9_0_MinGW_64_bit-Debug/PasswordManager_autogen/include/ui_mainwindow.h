/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *Menu_ChangePassword;
    QAction *actionLog_Out;
    QAction *actionGenerator;
    QAction *actionPasswords;
    QAction *actionTexts;
    QAction *actionFiles;
    QAction *actionChange_File_Path;
    QAction *actionSwitch_to_table_assistant;
    QAction *actionMinimize_to_Tray;
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *Basic_SwitchPage;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *ToPasswordGenerators;
    QPushButton *ToPasswords;
    QPushButton *ToTexts;
    QPushButton *ToFiles;
    QStackedWidget *stackedWidget;
    QWidget *PagePassManager;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QWidget *PasswordManager_MainArea;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QWidget *PM_Query;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_4;
    QWidget *PM_SearchBox;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout;
    QLineEdit *PM_SearchTextBox;
    QPushButton *PM_SearchButton;
    QTableWidget *PM_SearchResults;
    QWidget *PM_Modify;
    QLineEdit *PM_NewSiteEnterBox;
    QPlainTextEdit *PM_PlainTextSite;
    QPlainTextEdit *PM_PlainTextPassword;
    QLineEdit *PM_PasswordEnterBox;
    QPlainTextEdit *PM_PlainTextUsername;
    QLineEdit *PM_UsernameEnterBox;
    QPushButton *PM_AddButton;
    QPushButton *PM_UpdateButton;
    QPushButton *PM_RemoveButton;
    QTextEdit *PM_Info;
    QPushButton *PM_SaveAsFileButton;
    QWidget *PageTextEncryptor;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_4;
    QWidget *TE_DecryptedWidget;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout_7;
    QLineEdit *TE_PlainTextDecrypted;
    QPlainTextEdit *TE_DecryptedText;
    QWidget *TE_SwitchKey;
    QWidget *layoutWidget7;
    QVBoxLayout *verticalLayout_6;
    QPushButton *TE_EncryptionButton;
    QPlainTextEdit *TE_Info;
    QPushButton *TE_DecryptionButton;
    QWidget *TE_EncryptedWidget;
    QWidget *layoutWidget8;
    QVBoxLayout *verticalLayout_8;
    QLineEdit *TE_PlainTextEncrypted;
    QTextEdit *TE_EncryptedText;
    QWidget *PageFileEncryptor;
    QLineEdit *FE_InFilePathEnterBox;
    QPushButton *FE_EncryptionButton;
    QPushButton *FE_DecryptionButton;
    QPlainTextEdit *FE_PlainTextInFile;
    QPlainTextEdit *FE_PlainTextIdentifier;
    QLineEdit *FE_IdentifierEnterBox;
    QPlainTextEdit *FE_PlainTextOutputFile;
    QLineEdit *FE_OutFilePathEnterBox;
    QPlainTextEdit *FE_Info;
    QWidget *PageLoginRegister;
    QPlainTextEdit *Login_PlainTxtPassword;
    QPushButton *Login_PushButton;
    QCheckBox *Login_RegisterCheckBox;
    QPlainTextEdit *Login_PlainTxtUsername;
    QTextEdit *debuggingWid;
    QTextEdit *Login_InfoBox;
    QLineEdit *Login_UsernameEnterBox;
    QLineEdit *Login_PasswordEnterBox;
    QWidget *PageBasic;
    QWidget *layoutWidget9;
    QVBoxLayout *verticalLayout;
    QWidget *Basic_MainArea;
    QWidget *PagePassGenerator;
    QWidget *PG_Widget;
    QWidget *layoutWidget10;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *PG_GeneratedPassword;
    QPushButton *PG_GenerateButton;
    QWidget *PG_GenerateOptionCheckBox;
    QWidget *layoutWidget11;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *PG_CheckBoxUpperCase;
    QCheckBox *PG_CheckBoxLowerCase;
    QCheckBox *PG_CheckBoxNumbers;
    QCheckBox *PG_CheckBoxSymbols;
    QLineEdit *PG_PlainTextSize;
    QSpinBox *PG_PasswordSize;
    QPlainTextEdit *PG_PlainTextPasswordGenerated;
    QPlainTextEdit *PG_Info;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QMenu *menuHelp;
    QMenu *menuAssistant_Mode;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(792, 593);
        MainWindow->setMouseTracking(false);
        Menu_ChangePassword = new QAction(MainWindow);
        Menu_ChangePassword->setObjectName("Menu_ChangePassword");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::MailMessageNew));
        Menu_ChangePassword->setIcon(icon);
        actionLog_Out = new QAction(MainWindow);
        actionLog_Out->setObjectName("actionLog_Out");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::SystemLogOut));
        actionLog_Out->setIcon(icon1);
        actionGenerator = new QAction(MainWindow);
        actionGenerator->setObjectName("actionGenerator");
        actionPasswords = new QAction(MainWindow);
        actionPasswords->setObjectName("actionPasswords");
        actionTexts = new QAction(MainWindow);
        actionTexts->setObjectName("actionTexts");
        actionFiles = new QAction(MainWindow);
        actionFiles->setObjectName("actionFiles");
        actionChange_File_Path = new QAction(MainWindow);
        actionChange_File_Path->setObjectName("actionChange_File_Path");
        actionSwitch_to_table_assistant = new QAction(MainWindow);
        actionSwitch_to_table_assistant->setObjectName("actionSwitch_to_table_assistant");
        actionMinimize_to_Tray = new QAction(MainWindow);
        actionMinimize_to_Tray->setObjectName("actionMinimize_to_Tray");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("\n"
"background-image: url(:/image/background.jpg);\n"
"background-repeat: no-repeat;\n"
"background-position: center;"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(1, 1, 791, 551));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        Basic_SwitchPage = new QWidget(layoutWidget);
        Basic_SwitchPage->setObjectName("Basic_SwitchPage");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Basic_SwitchPage->sizePolicy().hasHeightForWidth());
        Basic_SwitchPage->setSizePolicy(sizePolicy);
        Basic_SwitchPage->setMaximumSize(QSize(16777215, 50));
        layoutWidget_5 = new QWidget(Basic_SwitchPage);
        layoutWidget_5->setObjectName("layoutWidget_5");
        layoutWidget_5->setGeometry(QRect(0, 0, 801, 21));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        ToPasswordGenerators = new QPushButton(layoutWidget_5);
        ToPasswordGenerators->setObjectName("ToPasswordGenerators");

        horizontalLayout_5->addWidget(ToPasswordGenerators);

        ToPasswords = new QPushButton(layoutWidget_5);
        ToPasswords->setObjectName("ToPasswords");

        horizontalLayout_5->addWidget(ToPasswords);

        ToTexts = new QPushButton(layoutWidget_5);
        ToTexts->setObjectName("ToTexts");

        horizontalLayout_5->addWidget(ToTexts);

        ToFiles = new QPushButton(layoutWidget_5);
        ToFiles->setObjectName("ToFiles");

        horizontalLayout_5->addWidget(ToFiles);


        verticalLayout_2->addWidget(Basic_SwitchPage);

        stackedWidget = new QStackedWidget(layoutWidget);
        stackedWidget->setObjectName("stackedWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(80);
        sizePolicy1.setVerticalStretch(61);
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        stackedWidget->setMaximumSize(QSize(16777215, 524));
        stackedWidget->setTabletTracking(false);
        stackedWidget->setAutoFillBackground(false);
        PagePassManager = new QWidget();
        PagePassManager->setObjectName("PagePassManager");
        layoutWidget1 = new QWidget(PagePassManager);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(0, 10, 801, 541));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        PasswordManager_MainArea = new QWidget(layoutWidget1);
        PasswordManager_MainArea->setObjectName("PasswordManager_MainArea");
        layoutWidget2 = new QWidget(PasswordManager_MainArea);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(1, 1, 791, 501));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        PM_Query = new QWidget(layoutWidget2);
        PM_Query->setObjectName("PM_Query");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(PM_Query->sizePolicy().hasHeightForWidth());
        PM_Query->setSizePolicy(sizePolicy2);
        layoutWidget3 = new QWidget(PM_Query);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(0, 0, 531, 501));
        verticalLayout_4 = new QVBoxLayout(layoutWidget3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        PM_SearchBox = new QWidget(layoutWidget3);
        PM_SearchBox->setObjectName("PM_SearchBox");
        PM_SearchBox->setMinimumSize(QSize(0, 20));
        layoutWidget4 = new QWidget(PM_SearchBox);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(0, 0, 531, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget4);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        PM_SearchTextBox = new QLineEdit(layoutWidget4);
        PM_SearchTextBox->setObjectName("PM_SearchTextBox");

        horizontalLayout->addWidget(PM_SearchTextBox);

        PM_SearchButton = new QPushButton(layoutWidget4);
        PM_SearchButton->setObjectName("PM_SearchButton");

        horizontalLayout->addWidget(PM_SearchButton);


        verticalLayout_4->addWidget(PM_SearchBox);

        PM_SearchResults = new QTableWidget(layoutWidget3);
        if (PM_SearchResults->columnCount() < 3)
            PM_SearchResults->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        PM_SearchResults->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        PM_SearchResults->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        PM_SearchResults->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (PM_SearchResults->rowCount() < 20)
            PM_SearchResults->setRowCount(20);
        PM_SearchResults->setObjectName("PM_SearchResults");
        PM_SearchResults->horizontalHeader()->setCascadingSectionResizes(false);
        PM_SearchResults->horizontalHeader()->setMinimumSectionSize(170);
        PM_SearchResults->horizontalHeader()->setDefaultSectionSize(170);
        PM_SearchResults->horizontalHeader()->setStretchLastSection(false);

        verticalLayout_4->addWidget(PM_SearchResults);


        horizontalLayout_3->addWidget(PM_Query);

        PM_Modify = new QWidget(layoutWidget2);
        PM_Modify->setObjectName("PM_Modify");
        PM_Modify->setMinimumSize(QSize(250, 0));
        PM_NewSiteEnterBox = new QLineEdit(PM_Modify);
        PM_NewSiteEnterBox->setObjectName("PM_NewSiteEnterBox");
        PM_NewSiteEnterBox->setGeometry(QRect(100, 60, 140, 20));
        PM_PlainTextSite = new QPlainTextEdit(PM_Modify);
        PM_PlainTextSite->setObjectName("PM_PlainTextSite");
        PM_PlainTextSite->setGeometry(QRect(0, 60, 80, 20));
        PM_PlainTextPassword = new QPlainTextEdit(PM_Modify);
        PM_PlainTextPassword->setObjectName("PM_PlainTextPassword");
        PM_PlainTextPassword->setGeometry(QRect(0, 120, 80, 20));
        PM_PasswordEnterBox = new QLineEdit(PM_Modify);
        PM_PasswordEnterBox->setObjectName("PM_PasswordEnterBox");
        PM_PasswordEnterBox->setGeometry(QRect(100, 120, 140, 20));
        PM_PlainTextUsername = new QPlainTextEdit(PM_Modify);
        PM_PlainTextUsername->setObjectName("PM_PlainTextUsername");
        PM_PlainTextUsername->setGeometry(QRect(0, 90, 80, 20));
        PM_UsernameEnterBox = new QLineEdit(PM_Modify);
        PM_UsernameEnterBox->setObjectName("PM_UsernameEnterBox");
        PM_UsernameEnterBox->setGeometry(QRect(100, 90, 140, 20));
        PM_AddButton = new QPushButton(PM_Modify);
        PM_AddButton->setObjectName("PM_AddButton");
        PM_AddButton->setGeometry(QRect(0, 160, 80, 18));
        PM_UpdateButton = new QPushButton(PM_Modify);
        PM_UpdateButton->setObjectName("PM_UpdateButton");
        PM_UpdateButton->setGeometry(QRect(80, 160, 80, 18));
        PM_RemoveButton = new QPushButton(PM_Modify);
        PM_RemoveButton->setObjectName("PM_RemoveButton");
        PM_RemoveButton->setGeometry(QRect(160, 160, 80, 18));
        PM_Info = new QTextEdit(PM_Modify);
        PM_Info->setObjectName("PM_Info");
        PM_Info->setGeometry(QRect(0, 200, 241, 91));
        PM_SaveAsFileButton = new QPushButton(PM_Modify);
        PM_SaveAsFileButton->setObjectName("PM_SaveAsFileButton");
        PM_SaveAsFileButton->setGeometry(QRect(0, 300, 241, 20));

        horizontalLayout_3->addWidget(PM_Modify);


        verticalLayout_3->addWidget(PasswordManager_MainArea);

        stackedWidget->addWidget(PagePassManager);
        PageTextEncryptor = new QWidget();
        PageTextEncryptor->setObjectName("PageTextEncryptor");
        layoutWidget5 = new QWidget(PageTextEncryptor);
        layoutWidget5->setObjectName("layoutWidget5");
        layoutWidget5->setGeometry(QRect(1, 0, 800, 511));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        TE_DecryptedWidget = new QWidget(layoutWidget5);
        TE_DecryptedWidget->setObjectName("TE_DecryptedWidget");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(TE_DecryptedWidget->sizePolicy().hasHeightForWidth());
        TE_DecryptedWidget->setSizePolicy(sizePolicy3);
        layoutWidget6 = new QWidget(TE_DecryptedWidget);
        layoutWidget6->setObjectName("layoutWidget6");
        layoutWidget6->setGeometry(QRect(0, -1, 371, 511));
        verticalLayout_7 = new QVBoxLayout(layoutWidget6);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        TE_PlainTextDecrypted = new QLineEdit(layoutWidget6);
        TE_PlainTextDecrypted->setObjectName("TE_PlainTextDecrypted");
        TE_PlainTextDecrypted->setReadOnly(true);

        verticalLayout_7->addWidget(TE_PlainTextDecrypted);

        TE_DecryptedText = new QPlainTextEdit(layoutWidget6);
        TE_DecryptedText->setObjectName("TE_DecryptedText");

        verticalLayout_7->addWidget(TE_DecryptedText);


        horizontalLayout_4->addWidget(TE_DecryptedWidget);

        TE_SwitchKey = new QWidget(layoutWidget5);
        TE_SwitchKey->setObjectName("TE_SwitchKey");
        TE_SwitchKey->setMinimumSize(QSize(58, 0));
        TE_SwitchKey->setMaximumSize(QSize(100, 16777215));
        layoutWidget7 = new QWidget(TE_SwitchKey);
        layoutWidget7->setObjectName("layoutWidget7");
        layoutWidget7->setGeometry(QRect(0, 0, 101, 511));
        verticalLayout_6 = new QVBoxLayout(layoutWidget7);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        TE_EncryptionButton = new QPushButton(layoutWidget7);
        TE_EncryptionButton->setObjectName("TE_EncryptionButton");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(TE_EncryptionButton->sizePolicy().hasHeightForWidth());
        TE_EncryptionButton->setSizePolicy(sizePolicy4);

        verticalLayout_6->addWidget(TE_EncryptionButton);

        TE_Info = new QPlainTextEdit(layoutWidget7);
        TE_Info->setObjectName("TE_Info");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(TE_Info->sizePolicy().hasHeightForWidth());
        TE_Info->setSizePolicy(sizePolicy5);
        TE_Info->setMaximumSize(QSize(100, 70));

        verticalLayout_6->addWidget(TE_Info);

        TE_DecryptionButton = new QPushButton(layoutWidget7);
        TE_DecryptionButton->setObjectName("TE_DecryptionButton");
        sizePolicy4.setHeightForWidth(TE_DecryptionButton->sizePolicy().hasHeightForWidth());
        TE_DecryptionButton->setSizePolicy(sizePolicy4);

        verticalLayout_6->addWidget(TE_DecryptionButton);


        horizontalLayout_4->addWidget(TE_SwitchKey);

        TE_EncryptedWidget = new QWidget(layoutWidget5);
        TE_EncryptedWidget->setObjectName("TE_EncryptedWidget");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(TE_EncryptedWidget->sizePolicy().hasHeightForWidth());
        TE_EncryptedWidget->setSizePolicy(sizePolicy6);
        TE_EncryptedWidget->setMinimumSize(QSize(100, 0));
        layoutWidget8 = new QWidget(TE_EncryptedWidget);
        layoutWidget8->setObjectName("layoutWidget8");
        layoutWidget8->setGeometry(QRect(0, 0, 331, 511));
        verticalLayout_8 = new QVBoxLayout(layoutWidget8);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        TE_PlainTextEncrypted = new QLineEdit(layoutWidget8);
        TE_PlainTextEncrypted->setObjectName("TE_PlainTextEncrypted");
        TE_PlainTextEncrypted->setReadOnly(true);

        verticalLayout_8->addWidget(TE_PlainTextEncrypted);

        TE_EncryptedText = new QTextEdit(layoutWidget8);
        TE_EncryptedText->setObjectName("TE_EncryptedText");

        verticalLayout_8->addWidget(TE_EncryptedText);


        horizontalLayout_4->addWidget(TE_EncryptedWidget);

        stackedWidget->addWidget(PageTextEncryptor);
        PageFileEncryptor = new QWidget();
        PageFileEncryptor->setObjectName("PageFileEncryptor");
        FE_InFilePathEnterBox = new QLineEdit(PageFileEncryptor);
        FE_InFilePathEnterBox->setObjectName("FE_InFilePathEnterBox");
        FE_InFilePathEnterBox->setGeometry(QRect(310, 170, 290, 20));
        FE_EncryptionButton = new QPushButton(PageFileEncryptor);
        FE_EncryptionButton->setObjectName("FE_EncryptionButton");
        FE_EncryptionButton->setGeometry(QRect(310, 290, 80, 18));
        FE_DecryptionButton = new QPushButton(PageFileEncryptor);
        FE_DecryptionButton->setObjectName("FE_DecryptionButton");
        FE_DecryptionButton->setGeometry(QRect(410, 290, 80, 18));
        FE_PlainTextInFile = new QPlainTextEdit(PageFileEncryptor);
        FE_PlainTextInFile->setObjectName("FE_PlainTextInFile");
        FE_PlainTextInFile->setGeometry(QRect(200, 170, 100, 20));
        FE_PlainTextInFile->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        FE_PlainTextIdentifier = new QPlainTextEdit(PageFileEncryptor);
        FE_PlainTextIdentifier->setObjectName("FE_PlainTextIdentifier");
        FE_PlainTextIdentifier->setGeometry(QRect(200, 230, 100, 20));
        FE_PlainTextIdentifier->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        FE_IdentifierEnterBox = new QLineEdit(PageFileEncryptor);
        FE_IdentifierEnterBox->setObjectName("FE_IdentifierEnterBox");
        FE_IdentifierEnterBox->setGeometry(QRect(310, 230, 290, 20));
        FE_PlainTextOutputFile = new QPlainTextEdit(PageFileEncryptor);
        FE_PlainTextOutputFile->setObjectName("FE_PlainTextOutputFile");
        FE_PlainTextOutputFile->setGeometry(QRect(200, 200, 100, 20));
        FE_PlainTextOutputFile->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        FE_OutFilePathEnterBox = new QLineEdit(PageFileEncryptor);
        FE_OutFilePathEnterBox->setObjectName("FE_OutFilePathEnterBox");
        FE_OutFilePathEnterBox->setGeometry(QRect(310, 200, 290, 20));
        FE_Info = new QPlainTextEdit(PageFileEncryptor);
        FE_Info->setObjectName("FE_Info");
        FE_Info->setGeometry(QRect(200, 260, 401, 20));
        FE_Info->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
        FE_Info->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        FE_Info->setReadOnly(true);
        stackedWidget->addWidget(PageFileEncryptor);
        PageLoginRegister = new QWidget();
        PageLoginRegister->setObjectName("PageLoginRegister");
        PageLoginRegister->setStyleSheet(QString::fromUtf8(""));
        Login_PlainTxtPassword = new QPlainTextEdit(PageLoginRegister);
        Login_PlainTxtPassword->setObjectName("Login_PlainTxtPassword");
        Login_PlainTxtPassword->setGeometry(QRect(305, 250, 75, 20));
        Login_PushButton = new QPushButton(PageLoginRegister);
        Login_PushButton->setObjectName("Login_PushButton");
        Login_PushButton->setGeometry(QRect(390, 280, 100, 20));
        Login_RegisterCheckBox = new QCheckBox(PageLoginRegister);
        Login_RegisterCheckBox->setObjectName("Login_RegisterCheckBox");
        Login_RegisterCheckBox->setGeometry(QRect(315, 280, 71, 18));
        Login_PlainTxtUsername = new QPlainTextEdit(PageLoginRegister);
        Login_PlainTxtUsername->setObjectName("Login_PlainTxtUsername");
        Login_PlainTxtUsername->setGeometry(QRect(305, 220, 75, 20));
        QSizePolicy sizePolicy7(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(Login_PlainTxtUsername->sizePolicy().hasHeightForWidth());
        Login_PlainTxtUsername->setSizePolicy(sizePolicy7);
        debuggingWid = new QTextEdit(PageLoginRegister);
        debuggingWid->setObjectName("debuggingWid");
        debuggingWid->setGeometry(QRect(140, 0, 291, 151));
        Login_InfoBox = new QTextEdit(PageLoginRegister);
        Login_InfoBox->setObjectName("Login_InfoBox");
        Login_InfoBox->setGeometry(QRect(320, 190, 160, 20));
        Login_UsernameEnterBox = new QLineEdit(PageLoginRegister);
        Login_UsernameEnterBox->setObjectName("Login_UsernameEnterBox");
        Login_UsernameEnterBox->setGeometry(QRect(390, 220, 100, 20));
        Login_PasswordEnterBox = new QLineEdit(PageLoginRegister);
        Login_PasswordEnterBox->setObjectName("Login_PasswordEnterBox");
        Login_PasswordEnterBox->setGeometry(QRect(390, 250, 100, 20));
        stackedWidget->addWidget(PageLoginRegister);
        PageBasic = new QWidget();
        PageBasic->setObjectName("PageBasic");
        layoutWidget9 = new QWidget(PageBasic);
        layoutWidget9->setObjectName("layoutWidget9");
        layoutWidget9->setGeometry(QRect(0, 0, 801, 551));
        verticalLayout = new QVBoxLayout(layoutWidget9);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Basic_MainArea = new QWidget(layoutWidget9);
        Basic_MainArea->setObjectName("Basic_MainArea");

        verticalLayout->addWidget(Basic_MainArea);

        stackedWidget->addWidget(PageBasic);
        PagePassGenerator = new QWidget();
        PagePassGenerator->setObjectName("PagePassGenerator");
        PG_Widget = new QWidget(PagePassGenerator);
        PG_Widget->setObjectName("PG_Widget");
        PG_Widget->setGeometry(QRect(250, 150, 300, 200));
        layoutWidget10 = new QWidget(PG_Widget);
        layoutWidget10->setObjectName("layoutWidget10");
        layoutWidget10->setGeometry(QRect(10, 0, 291, 191));
        verticalLayout_5 = new QVBoxLayout(layoutWidget10);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        PG_GeneratedPassword = new QTextEdit(layoutWidget10);
        PG_GeneratedPassword->setObjectName("PG_GeneratedPassword");

        verticalLayout_5->addWidget(PG_GeneratedPassword);

        PG_GenerateButton = new QPushButton(layoutWidget10);
        PG_GenerateButton->setObjectName("PG_GenerateButton");

        verticalLayout_5->addWidget(PG_GenerateButton);

        PG_GenerateOptionCheckBox = new QWidget(layoutWidget10);
        PG_GenerateOptionCheckBox->setObjectName("PG_GenerateOptionCheckBox");
        PG_GenerateOptionCheckBox->setMinimumSize(QSize(0, 20));
        layoutWidget11 = new QWidget(PG_GenerateOptionCheckBox);
        layoutWidget11->setObjectName("layoutWidget11");
        layoutWidget11->setGeometry(QRect(1, 0, 291, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        PG_CheckBoxUpperCase = new QCheckBox(layoutWidget11);
        PG_CheckBoxUpperCase->setObjectName("PG_CheckBoxUpperCase");

        horizontalLayout_2->addWidget(PG_CheckBoxUpperCase);

        PG_CheckBoxLowerCase = new QCheckBox(layoutWidget11);
        PG_CheckBoxLowerCase->setObjectName("PG_CheckBoxLowerCase");

        horizontalLayout_2->addWidget(PG_CheckBoxLowerCase);

        PG_CheckBoxNumbers = new QCheckBox(layoutWidget11);
        PG_CheckBoxNumbers->setObjectName("PG_CheckBoxNumbers");

        horizontalLayout_2->addWidget(PG_CheckBoxNumbers);

        PG_CheckBoxSymbols = new QCheckBox(layoutWidget11);
        PG_CheckBoxSymbols->setObjectName("PG_CheckBoxSymbols");

        horizontalLayout_2->addWidget(PG_CheckBoxSymbols);

        PG_PlainTextSize = new QLineEdit(layoutWidget11);
        PG_PlainTextSize->setObjectName("PG_PlainTextSize");
        PG_PlainTextSize->setMaximumSize(QSize(30, 16777215));
        PG_PlainTextSize->setReadOnly(true);

        horizontalLayout_2->addWidget(PG_PlainTextSize);

        PG_PasswordSize = new QSpinBox(layoutWidget11);
        PG_PasswordSize->setObjectName("PG_PasswordSize");
        PG_PasswordSize->setMinimumSize(QSize(60, 0));

        horizontalLayout_2->addWidget(PG_PasswordSize);


        verticalLayout_5->addWidget(PG_GenerateOptionCheckBox);

        PG_PlainTextPasswordGenerated = new QPlainTextEdit(PagePassGenerator);
        PG_PlainTextPasswordGenerated->setObjectName("PG_PlainTextPasswordGenerated");
        PG_PlainTextPasswordGenerated->setGeometry(QRect(150, 210, 104, 21));
        PG_PlainTextPasswordGenerated->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        PG_PlainTextPasswordGenerated->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        PG_PlainTextPasswordGenerated->setReadOnly(true);
        PG_Info = new QPlainTextEdit(PagePassGenerator);
        PG_Info->setObjectName("PG_Info");
        PG_Info->setGeometry(QRect(600, 200, 104, 64));
        PG_Info->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        PG_Info->setReadOnly(true);
        stackedWidget->addWidget(PagePassGenerator);

        verticalLayout_2->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 792, 17));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName("menuMenu");
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName("menuHelp");
        menuAssistant_Mode = new QMenu(menuBar);
        menuAssistant_Mode->setObjectName("menuAssistant_Mode");
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuMenu->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuBar->addAction(menuAssistant_Mode->menuAction());
        menuMenu->addAction(Menu_ChangePassword);
        menuMenu->addAction(actionLog_Out);
        menuMenu->addAction(actionChange_File_Path);
        menuMenu->addAction(actionMinimize_to_Tray);
        menuHelp->addAction(actionGenerator);
        menuHelp->addAction(actionPasswords);
        menuHelp->addAction(actionTexts);
        menuHelp->addAction(actionFiles);
        menuAssistant_Mode->addAction(actionSwitch_to_table_assistant);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PasswordManager", nullptr));
        Menu_ChangePassword->setText(QCoreApplication::translate("MainWindow", "Change Password", nullptr));
        actionLog_Out->setText(QCoreApplication::translate("MainWindow", "Log Out", nullptr));
        actionGenerator->setText(QCoreApplication::translate("MainWindow", "Generator", nullptr));
        actionPasswords->setText(QCoreApplication::translate("MainWindow", "Passwords", nullptr));
        actionTexts->setText(QCoreApplication::translate("MainWindow", "Texts", nullptr));
        actionFiles->setText(QCoreApplication::translate("MainWindow", "Files", nullptr));
        actionChange_File_Path->setText(QCoreApplication::translate("MainWindow", "Change File Path", nullptr));
        actionSwitch_to_table_assistant->setText(QCoreApplication::translate("MainWindow", "Switch to table assistant", nullptr));
        actionMinimize_to_Tray->setText(QCoreApplication::translate("MainWindow", "Minimize to Tray", nullptr));
        ToPasswordGenerators->setText(QCoreApplication::translate("MainWindow", "Password Generator", nullptr));
        ToPasswords->setText(QCoreApplication::translate("MainWindow", "Passwords", nullptr));
        ToTexts->setText(QCoreApplication::translate("MainWindow", "Texts", nullptr));
        ToFiles->setText(QCoreApplication::translate("MainWindow", "Files", nullptr));
        PM_SearchButton->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        QTableWidgetItem *___qtablewidgetitem = PM_SearchResults->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Site", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = PM_SearchResults->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = PM_SearchResults->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        PM_PlainTextSite->setPlainText(QCoreApplication::translate("MainWindow", "Site:", nullptr));
        PM_PlainTextPassword->setPlainText(QCoreApplication::translate("MainWindow", "Password\n"
"", nullptr));
        PM_PlainTextUsername->setPlainText(QCoreApplication::translate("MainWindow", "Username\n"
"", nullptr));
        PM_AddButton->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        PM_UpdateButton->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
        PM_RemoveButton->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        PM_Info->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Info:</p></body></html>", nullptr));
        PM_SaveAsFileButton->setText(QCoreApplication::translate("MainWindow", "Save as file", nullptr));
        TE_PlainTextDecrypted->setText(QCoreApplication::translate("MainWindow", "Decrypted Text:", nullptr));
        TE_EncryptionButton->setText(QCoreApplication::translate("MainWindow", "Encryption", nullptr));
        TE_Info->setPlainText(QCoreApplication::translate("MainWindow", "Info:", nullptr));
        TE_DecryptionButton->setText(QCoreApplication::translate("MainWindow", "Decryption", nullptr));
        TE_PlainTextEncrypted->setText(QCoreApplication::translate("MainWindow", "Encrypted Text:", nullptr));
        FE_InFilePathEnterBox->setText(QString());
        FE_EncryptionButton->setText(QCoreApplication::translate("MainWindow", "Encryption", nullptr));
        FE_DecryptionButton->setText(QCoreApplication::translate("MainWindow", "Decryption", nullptr));
        FE_PlainTextInFile->setPlainText(QCoreApplication::translate("MainWindow", "Input File Path:", nullptr));
        FE_PlainTextIdentifier->setPlainText(QCoreApplication::translate("MainWindow", "Identifier:", nullptr));
        FE_IdentifierEnterBox->setText(QString());
        FE_PlainTextOutputFile->setPlainText(QCoreApplication::translate("MainWindow", "Output File Path:", nullptr));
        FE_OutFilePathEnterBox->setText(QString());
        FE_Info->setPlainText(QCoreApplication::translate("MainWindow", "Info:", nullptr));
        Login_PlainTxtPassword->setPlainText(QCoreApplication::translate("MainWindow", "Password:\n"
"", nullptr));
        Login_PushButton->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        Login_RegisterCheckBox->setText(QCoreApplication::translate("MainWindow", "Register", nullptr));
        Login_PlainTxtUsername->setPlainText(QCoreApplication::translate("MainWindow", "Username:", nullptr));
        Login_InfoBox->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Status:</p></body></html>", nullptr));
        PG_GenerateButton->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        PG_CheckBoxUpperCase->setText(QCoreApplication::translate("MainWindow", "ABC", nullptr));
        PG_CheckBoxLowerCase->setText(QCoreApplication::translate("MainWindow", "abc", nullptr));
        PG_CheckBoxNumbers->setText(QCoreApplication::translate("MainWindow", "123", nullptr));
        PG_CheckBoxSymbols->setText(QCoreApplication::translate("MainWindow", "$&&%", nullptr));
        PG_PlainTextSize->setText(QCoreApplication::translate("MainWindow", "Size:", nullptr));
        PG_PlainTextPasswordGenerated->setPlainText(QCoreApplication::translate("MainWindow", "Password Generated:", nullptr));
        PG_Info->setPlainText(QCoreApplication::translate("MainWindow", "Info:", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("MainWindow", "Setting", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menuAssistant_Mode->setTitle(QCoreApplication::translate("MainWindow", "Assistant Mode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
