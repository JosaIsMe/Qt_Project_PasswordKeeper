#include "mainwindow.h"
#include "passwordmanager.h"
#include "qlineedit.h"
#include "ui_mainwindow.h"
#include "passwordstrengthchecker.h"
#include <QTimer>
#include <QRegularExpressionValidator>
#include <QStandardPaths>
#include <QDir>
#include <QLabel>
#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QFileDialog>
//#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(800,600);
    setWindowIcon(QIcon(":/icon/icon_mainwindow.png"));
    ui->setupUi(this);
    loginData.loginMode = true;
    //setCentralWidget(StackedWidget);
    ui->stackedWidget->setCurrentWidget(ui->PageLoginRegister);
    ui->Login_PlainTxtUsername->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Login_PlainTxtUsername->setReadOnly(true);
    ui->Login_PlainTxtPassword->setReadOnly(true);
    ui->Login_PlainTxtPassword->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Login_InfoBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Login_InfoBox->setReadOnly(true);
    ui->Login_PasswordEnterBox->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9A-Za-z_]*"),this));
    ui->debuggingWid->setVisible(false);
    //connect(ui->username,&QTextEdit::textChanged,this,&MainWindow::onEnterUserNameChanged);
    //connect(ui->pushButton,&);
    //connect(ui->Login_PushButton,&QAbstractButton::clicked,this,&MainWindow::on_Login_PushButton_clicked);
    //ui->menubar->
    //QHeaderView * header = ui->tableWidget->horizontalHeader();
    //header->setSectionResizeMode(QHeaderView::Stretch);
    ui->PM_PlainTextSite->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->PM_PlainTextPassword->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->PM_PlainTextPassword->setReadOnly(true);
    ui->PM_PlainTextSite->setReadOnly(true);
    ui->PM_PlainTextUsername->setReadOnly(true);
    ui->PM_PlainTextUsername->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //passManagerData.passwordStrengthChecker = new PasswordStrengthChecker();
    desktopPet = new DesktopPet(this);
    createTrayIcon();
    hideTopBar();
    QFile *styleFile;
    styleFile  = new QFile(":/style/style.qss", this);
    styleFile->open(QFile::ReadOnly);
    QString styleSheet = QString(styleFile->readAll());
    this->setStyleSheet(styleSheet);
    styleFile->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTopBar(){
    ui->Basic_SwitchPage->show();
    ui->menuBar->show();
}

void MainWindow::hideTopBar(){
    ui->Basic_SwitchPage->hide();
    ui->menuBar->hide();
}

QString MainWindow::createInputDialog(QWidget* parent, const QString& title, const QString& labelText, const QString& defaultBoxText) {
    QDialog dialog(parent);
    dialog.setWindowTitle(title);

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    QLabel* label = new QLabel(labelText, &dialog);
    layout->addWidget(label);

    QLineEdit* inputLine = new QLineEdit(&dialog);
    layout->addWidget(inputLine);

    QPushButton* button = new QPushButton("确定", &dialog);
    layout->addWidget(button);

    dialog.setModal(true);

    QObject::connect(button, &QPushButton::clicked, [&dialog] {
        dialog.accept();
    });
    inputLine->setText(defaultBoxText);
    if (dialog.exec() == QDialog::Accepted) {
        return inputLine->text();
    }

    return QString();
}

void MainWindow::createReadOnlyTextDialog(QWidget* parent, const QString& title, const QString& labelText, const QString& text) {
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

bool MainWindow::pushInfo(QString Page, QString info){
    if(Page == "PG"){
        ui->PG_Info->setPlainText("Info:" + info);
        return 1;
    }
    if(Page == "FE"){
        ui->FE_Info->setPlainText("Info" + info);
        return 1;
    }
    if(Page == "PM"){
        ui->PM_Info->setPlainText("Info" + info);
        return 1;
    }
    if(Page == "TE"){
        ui->TE_Info->setPlainText("Info" + info);
        return 1;
    }
    return 0;
}


void MainWindow::loginStatusShow(QString msg,qint64 t = 3000)
{
    ui->Login_InfoBox->setText("Status:" + msg);
    QTimer::singleShot(t,[=](){
        ui->Login_InfoBox->setText("Status:");
        ui->Login_PasswordEnterBox->setText("");
        ui->Login_UsernameEnterBox->setText("");
    });
}
void MainWindow::preLogin()
{
    qDebug() << "Button Clicked!";
    loginData.Username = ui->Login_UsernameEnterBox->text();
    loginData.Password = ui->Login_PasswordEnterBox->text();
    if(this->loginData.loginMode){
        this->loginData.loginManager = new LoginManager(loginData.Username);
        loginData.loginManager->login(loginData.Password);
        if(loginData.loginManager->isLoggedIn()){
            login();
        }
        else{
            loginStatusShow("Incorrect Password!");
            return;
        }
    }
    else{
        this->loginData.loginManager = new LoginManager(loginData.Username);
        if(loginData.loginManager->doesUserExist()){
            loginStatusShow("User Exists!");
            return;
        }
        else{
            loginData.loginManager->createUser(loginData.Password);
            loginStatusShow("Registering...");
        }
    }
}

/*void MainWindow::login()
{
    loginData.hasLoggedIn = true;
    userData.passwordManager = new PasswordManager(loginData.loginManager->getMasterKey(),loginData.loginManager->getVaultFilePath());
    userData.fileEncryptor = new FileEncryptor(*userData.passwordManager);
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    path += "/PasswordManagerApp/";
    path += loginData.Username;
    fileEncData.defaultFileOutputPath = path;
    textEncryptorData.encryptionHandler = new EncryptionHandler(loginData.loginManager->getMasterKey());
    this->ui->stackedWidget->setCurrentWidget(ui->PagePassManager);
    desktopPet->setUsername(loginData.Username);
    desktopPet->setPasswordFillCallback([this](){
        QString targetSite = QApplication::clipboard()->text();
        QString password = userData.passwordManager->getDecryptedPassword(targetSite);
        qDebug() << "2";
        trayIcon->showMessage("Encrypt result",
                              "Encryption Success!");
        QApplication::clipboard()->setText(password);

    });
    desktopPet->setFileEncryptCallback([this](QString filePath){
        QFileInfo fileInfo(filePath);
        QString dirPath = fileInfo.absolutePath();
        QString fileName = fileInfo.fileName();
        userData.fileEncryptor->encryptFile(filePath,fileEncData.defaultFileOutputPath + "/" + fileName + ".enc","file_drag:" + fileName);
        trayIcon->showMessage("Encrypt result",
                              "Encryption Success!");
    });
    showTopBar();
}*/

void MainWindow::login()
{
    loginData.hasLoggedIn = true;
    userData.passwordManager = new PasswordManager(loginData.loginManager->getMasterKey(),loginData.loginManager->getVaultFilePath());
    userData.fileEncryptor = new FileEncryptor(*userData.passwordManager);
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    path += "/PasswordManagerApp/";
    path += loginData.Username;
    fileEncData.defaultFileOutputPath = path;
    textEncryptorData.encryptionHandler = new EncryptionHandler(loginData.loginManager->getMasterKey());
    this->ui->stackedWidget->setCurrentWidget(ui->PagePassManager);
    desktopPet->setUsername(loginData.Username);

//if()

    // 已有的密码填充回调设置
    desktopPet->setPasswordFillCallback([this](){
        QString targetSite = QApplication::clipboard()->text();
        QString password = userData.passwordManager->getDecryptedPassword(targetSite);
        qDebug() << "2";
        trayIcon->showMessage("Encrypt result",
                              "Encryption Success!");
        QApplication::clipboard()->setText(password);

    });

    // 已有的文件加密回调设置
    desktopPet->setFileEncryptCallback([this](QString filePath){
        QFileInfo fileInfo(filePath);
        QString dirPath = fileInfo.absolutePath();
        QString fileName = fileInfo.fileName();
        userData.fileEncryptor->encryptFile(filePath,fileEncData.defaultFileOutputPath + "/" + fileName + ".enc","file_drag:" + fileName);
        trayIcon->showMessage("Encrypt result",
                              "Encryption Success!");
    });

    // --- 新增：设置文本加密和解密的回调 ---

    // 设置文本加密回调
    desktopPet->setTextEncryptCallback([this](const QString& text) -> QString {
        if (!textEncryptorData.encryptionHandler) return "";
        // 这个逻辑与 on_TE_EncryptionButton_clicked 中的逻辑一致
        QByteArray plainText_utf8 = text.toUtf8();
        QByteArray encrypted_bytes = textEncryptorData.encryptionHandler->encryptData(plainText_utf8);
        return encrypted_bytes.toBase64(); // 将二进制密文转为Base64字符串以便复制
    });

    // 设置文本解密回调
    desktopPet->setTextDecryptCallback([this](const QString& text) -> QString {
        if (!textEncryptorData.encryptionHandler) return "";
        // 这个逻辑与 on_TE_DecryptionButton_clicked 中的逻辑一致
        QByteArray encrypted_base64 = text.toUtf8();
        QByteArray encrypted_bytes = QByteArray::fromBase64(encrypted_base64);
        QByteArray decrypted_bytes = textEncryptorData.encryptionHandler->decryptData(encrypted_bytes);
        return QString::fromUtf8(decrypted_bytes); // 将解密后的二进制数据转回UTF-8字符串
    });

    showTopBar();
}

void MainWindow::importPasswords(QString filePath){
    if (filePath.isEmpty()) {
        pushInfo("PM", "导入操作已取消。");
        return;
    }

    // 3. 打开并读取JSON文件
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        pushInfo("PM", "无法打开文件: " + file.errorString());
        return;
    }

    // 4. 解析JSON数据
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        pushInfo("PM", "JSON解析错误: " + parseError.errorString());
        return;
    }

    if (!doc.isArray()) {
        pushInfo("PM", "JSON文件格式错误：根元素不是数组");
        return;
    }

    QJsonArray passwordsArray = doc.array();
    int importedCount = 0;
    int errorCount = 0;

    for (const QJsonValue& value : passwordsArray) {
        if (!value.isObject()) {
            errorCount++;
            continue;
        }

        QJsonObject passwordObject = value.toObject();

        if (!passwordObject.contains("site") ||
            !passwordObject.contains("user") ||
            !passwordObject.contains("password")) {
            errorCount++;
            continue;
        }
        QString site = passwordObject["site"].toString();
        QString username = passwordObject["user"].toString();
        QString password = passwordObject["password"].toString();


        if (userData.passwordManager->addEntry(site, username, password)) {
            importedCount++;
        } else if (userData.passwordManager->updateEntry(site, username, password)){
            importedCount++;
        } else {
            errorCount++;
        }
    }

    if (errorCount == 0) {
        pushInfo("PM", QString("成功导入 %1 个密码条目").arg(importedCount));
    } else {
        pushInfo("PM", QString("导入完成：%1 个成功，%2 个失败").arg(importedCount).arg(errorCount));
    }
}

void MainWindow::exportPasswords(QString filePath){
    if (filePath.isEmpty()) {
        pushInfo("PM", "导出操作已取消。");
        return;
    }

    QJsonArray passwordsArray;
    QList<QString> sites = userData.passwordManager->getAllSiteNames();

    for (const QString& site : sites) {
        QJsonObject passwordObject;

        QString sitename = site;
        QString username = userData.passwordManager->getEntryDetails(site).value("username").toString();
        QString password = userData.passwordManager->getDecryptedPassword(site);

        passwordObject.insert("site", sitename);
        passwordObject.insert("user", username);
        passwordObject.insert("password", password);
        passwordsArray.append(passwordObject);
    }

    QJsonDocument doc;
    doc.setArray(passwordsArray);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        pushInfo("PM", "无法打开文件进行写入: " + file.errorString());
        return;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    pushInfo("PM", "密码已成功导出到: " + filePath);
}

void MainWindow::switchPage(QWidget* wg)
{
    if(loginData.hasLoggedIn && wg != ui->stackedWidget->currentWidget()){
        ui->stackedWidget->setCurrentWidget(wg);
    }
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{

}

void MainWindow::on_ToFiles_clicked()
{
    switchPage(ui->PageFileEncryptor);
}
void MainWindow::on_ToPasswordGenerators_clicked()
{
    switchPage(ui->PagePassGenerator);
}
void MainWindow::on_ToPasswords_clicked()
{
    switchPage(ui->PagePassManager);
}
void MainWindow::on_ToTexts_clicked()
{
    switchPage(ui->PageTextEncryptor);
}

//void MainWindow








/*
 * 123

QString ChangeVaultPathDialog() {

    QString inputText;
    QDialog dialog;
    dialog.setWindowTitle("Vault Path:");
    dialog.resize(300, 100);
    QLineEdit *lineEdit = new QLineEdit(&dialog);
    QPushButton *button = new QPushButton("OK", &dialog);
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(lineEdit);
    layout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, [&]() {
        inputText = lineEdit->text();
        qDebug() << "Path Saved:" << inputText;
        dialog.accept();
    });
    dialog.exec();123L0BoPbDCYejiv8c
    return inputText;
}
*/

void MainWindow::on_Menu_ChangeVaultFilePath_triggered()
{
    //QString result = ChangeVaultPathDialog();
    //if (result != ""){}
}
QString ChangePasswordDialog() {

    QString inputText;
    QDialog dialog;
    dialog.setWindowTitle("New Password:");
    dialog.resize(300, 100);
    QLineEdit *lineEdit = new QLineEdit(&dialog);
    QPushButton *button = new QPushButton("OK", &dialog);
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(lineEdit);
    layout->addWidget(button);
    QObject::connect(button, &QPushButton::clicked, [&]() {
        inputText = lineEdit->text();
        qDebug() << "Password Saved:" << inputText;
        dialog.accept();
    });
    dialog.exec();
    return inputText;
}
void MainWindow::on_Menu_ChangePassword_triggered()
{
    QString newPassword = ChangePasswordDialog();

    if(newPassword != ""){
        loginData.loginManager->changeMasterPassword(loginData.Password,newPassword,*(userData.passwordManager));
    }
}

void MainWindow::clear(){
    if(loginData.loginManager != nullptr) delete loginData.loginManager;
    loginData.loginMode = true;
    loginData.Password = "";
    loginData.Username = "";
    loginData.hasLoggedIn = false;
    if(userData.fileEncryptor != nullptr) delete userData.fileEncryptor;
    if(userData.passwordManager != nullptr) delete userData.passwordManager;
    passManagerData.newPassword = "";
    passManagerData.newUsername = "";
    passManagerData.queryContent = "";
    if(passGenData.passwordGenerator != nullptr) delete passGenData.passwordGenerator;
    passGenData.Lowercase = false;
    passGenData.Numbers = false;
    passGenData.Symbols = false;
    passGenData.Uppercase = false;
    textEncryptorData.text = "";
    if(textEncryptorData.encryptionHandler != nullptr)delete textEncryptorData.encryptionHandler;
    //fileEncData.defaultFileOutputPath = "";
    hideTopBar();
}

void MainWindow::on_actionLog_Out_triggered()
{
    QApplication::quit();
    //if(loginData.hasLoggedIn){
        //clear();
        //ui->stackedWidget->setCurrentWidget(ui->PageLoginRegister);
    //}
}

void MainWindow::on_actionGenerator_triggered()
{
    createReadOnlyTextDialog(this,"Help:Generator","密码生成器帮助","密码生成器可以帮助您生成一个包含指定字符的随机密码，只需轻轻点击生成按钮。下方的四个复选框允许用户根据自己的需求改变密码可以选择的字符，而右下侧的长度框可以调节密码的长度。点击应用按钮可以自动把生成的密码填入密码管理系统的密码输入栏，只需要补充输入站点和用户名即可。");
}

void MainWindow::on_actionPasswords_triggered()
{
    createReadOnlyTextDialog(this,"Help:Passwords","密码管理界面帮助","密码管理界面可以帮助您安全地管理您的密码。左侧的密码搜索框允许用户搜索匹配的站点，只需要向搜索框输入站点的名称（可以是部分名称）并点击Search按钮即可实现。下方的栏目中会列出符合匹配的站点名称，用户名和密码。不输入任何文字直接按搜索会显示所有密码。\n显示密码后，密码单元格的背景颜色会提示您密码的强度，红色代表弱，绿色代表强，而黄色代表适中。建议您选用更强的代码以保证安全性。\n在右侧输入站点，用户名和密码，按下添加，更新和移除三个键即可添加，更改与删除存储的密码。\n我们还添加了导出功能。您的密码可以通过点击导出键以明文形式导出为json格式的文件，也可以将导出后的密码文件直接拖入框中（或者点击导入键）。信息栏会提示您导入结果。");
}

void MainWindow::on_actionTexts_triggered()
{
    createReadOnlyTextDialog(this,"Help:Texts","文本加密界面帮助","文本加密界面会使用独属于您的主密钥加密文本，其他人的密钥无法解密您的密钥加密后的文本。\n将待加密的文本输入左侧的文本框中，点击加密即可在右侧获得加密后的文本。同样，将加密后的文本输入右侧的文本框中，点击解密可以在左侧获得解密的文本。");
}

void MainWindow::on_actionFiles_triggered()
{
    createReadOnlyTextDialog(this,"Help:Files","文件加密页面帮助","文件加密页面会使用独属于您的主密钥加密用于加密文件的密钥。您需要向待处理文件路径输入待加密文件的路径，点击右侧的选择文件以选择待处理文件或者将待处理文件拖入画面，再向处理后文件路径框输入目标文件的路径或者自行创建输出文件（不存在这样的目标文件时会自动创建），以及向标识符一栏输入您为这个文件提供的内部名称（点击自动生成会把待处理文件的绝对路径作为标识符）。提供后内部名称和生成的密钥将隐式存于密码管理系统中。点击加密按钮会将待处理文件加密，生成加密后的文件。同样，在解密时，只需要以同样的方式把待处理文件和处理后文件提供给程序，并向标识符一栏输入原先加密时使用的内部名称，点击解密即可解密文件。");
}


void MainWindow::on_actionChange_File_Path_triggered()
{
    QString result = createInputDialog(this,"Change File Path","New Path:",fileEncData.defaultFileOutputPath);
    fileEncData.defaultFileOutputPath = result;
}


void MainWindow::on_actionSwitch_to_table_assistant_triggered()
{

    hide();
    desktopPet->showPet();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event){
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event){
    const QMimeData *mimeData = event->mimeData();
    QUrl Url;
    QString filePath;
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        Url = urlList[0];
        filePath = Url.toLocalFile();
        if(ui->stackedWidget->currentWidget() == ui->PagePassManager){
            importPasswords(filePath);
        } else if (ui->stackedWidget->currentWidget() == ui->PageFileEncryptor){
            ui->FE_InFilePathEnterBox->setText(filePath);
        }

    } else {
        event->ignore();
    }

}

void MainWindow::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icon/icon_tray.png"));

    QMenu *trayMenu = new QMenu(this);
    QAction *showAction = new QAction("显示主窗口", this);
    QAction *exitAction = new QAction("退出", this);

    trayMenu->addAction(showAction);
    trayMenu->addSeparator();
    trayMenu->addAction(exitAction);

    trayIcon->setContextMenu(trayMenu);

    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::onTrayIconActivated);
    connect(showAction, &QAction::triggered, this, &MainWindow::onShowMainWindow);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
}

void MainWindow::on_actionMinimize_to_Tray_triggered()
{
    this->hide();
    trayIcon->show();

    trayIcon->showMessage("密码管理器",
                          "程序已最小化到系统托盘",
                          QSystemTrayIcon::Information,
                          2000);
}

void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick) {
        onShowMainWindow();
    }
}

void MainWindow::onShowMainWindow()
{
    this->show();
    this->activateWindow();
    this->raise();
    trayIcon->hide();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        this->hide();
        event->ignore();
    } else {
        event->accept();
    }
}




//Slots:

//  FE:

void MainWindow::on_FE_ChooseDirectoryButton_clicked()
{
    QString savePath = QFileDialog::getSaveFileName(this,"选择目标文件夹",fileEncData.defaultFileOutputPath);
    ui->FE_OutFilePathEnterBox->setText(savePath);
}


void MainWindow::on_FE_ChooseFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"选择加密文件",fileEncData.defaultFileOutputPath);
    ui->FE_InFilePathEnterBox->setText(filePath);
}


void MainWindow::on_FE_RandomIdentifierButton_clicked()
{
    QString autoIdentifier = ui->FE_InFilePathEnterBox->text();
    ui->FE_IdentifierEnterBox->setText(autoIdentifier);
}

void MainWindow::on_FE_EncryptionButton_clicked()
{
    bool status;
    QString InputPath = ui->FE_InFilePathEnterBox->text();
    if(InputPath[1] != ':'){
        InputPath = fileEncData.defaultFileOutputPath + InputPath;
    }
    QString OutputPath = ui->FE_OutFilePathEnterBox->text();
    if(OutputPath[1] != ':'){
        OutputPath = fileEncData.defaultFileOutputPath + OutputPath;
    }
    if(ui->FE_InFilePathEnterBox->text() != "" && ui->FE_OutFilePathEnterBox->text() != "" && ui->FE_IdentifierEnterBox->text() != ""){
        status = userData.fileEncryptor->encryptFile(InputPath,OutputPath,"File:" + ui->FE_IdentifierEnterBox->text());
        if(status){
            pushInfo("FE","File Encrypted!");
            qDebug() << "File Encryption Succeed!";
        }
        else{
            pushInfo("FE","Fail to encrypt the file!");
        }
    }
}

void MainWindow::on_FE_DecryptionButton_clicked()
{
    bool status;
    QString InputPath = ui->FE_InFilePathEnterBox->text();
    if(InputPath[1] != ':'){
        InputPath = fileEncData.defaultFileOutputPath + "/" + InputPath;
    }
    QString OutputPath = ui->FE_OutFilePathEnterBox->text();
    if(OutputPath[1] != ':'){
        OutputPath = fileEncData.defaultFileOutputPath + "/" + OutputPath;
    }
    if(ui->FE_InFilePathEnterBox->text() != "" && ui->FE_OutFilePathEnterBox->text() != "" && ui->FE_IdentifierEnterBox->text() != ""){
        status = userData.fileEncryptor->decryptFile(InputPath,OutputPath,"File:" + ui->FE_IdentifierEnterBox->text());
        if(status){
            pushInfo("FE","File Decrypted!");
            qDebug() << "File Decryption Succeed!";
        }
        else{
            pushInfo("FE","Fail to decrypt the file!");
        }
    }
}

//  TE:

void MainWindow::on_TE_EncryptionButton_clicked()
{
    QString oriText = ui->TE_DecryptedText->toPlainText();
    QByteArray ba1 = oriText.toUtf8();
    QByteArray ba3 = textEncryptorData.encryptionHandler->encryptData(ba1);
    QString result = ba3.toBase64();
    ui->TE_EncryptedText->setPlainText(result);
}

void MainWindow::on_TE_DecryptionButton_clicked()
{
    QString oriText = ui->TE_EncryptedText->toPlainText();
    QByteArray ba1 = QByteArray::fromBase64(oriText.toUtf8());
    QByteArray ba3 = textEncryptorData.encryptionHandler->decryptData(ba1);
    QString result = QString::fromUtf8(ba3);
    if(result != ""){
        ui->TE_DecryptedText->setPlainText(result);
    }
    else{
        pushInfo("TE","Failed to decrypt!");
    }
}

//  PM:

void MainWindow::on_PM_SearchButton_clicked()
{
    int tableOffset = 0;
    bool hasResult = 0;
    ui->PM_SearchResults->clearContents();
    ui->PM_SearchResults->setRowCount(userData.passwordManager->getAllSiteNames().size());
    if(loginData.hasLoggedIn){
        QList<QString> sites = userData.passwordManager->getAllSiteNames();
        QString regstr = ui->PM_SearchTextBox->text();
        QRegularExpression reg(regstr);

        for(auto it = sites.begin(); it != sites.end(); it++){
            if (reg.match(*it).hasMatch()){
                hasResult = 1;
                QTableWidgetItem* siteItem = new QTableWidgetItem(*it);
                QTableWidgetItem* userItem = new QTableWidgetItem(
                    userData.passwordManager->getEntryDetails(*it).constFind("username")->value<QString>()
                    );
                QString passwd = userData.passwordManager->getDecryptedPassword(*it);
                QTableWidgetItem* passItem = new QTableWidgetItem(passwd);
                PasswordStrengthChecker::StrengthLevel strength =
                    passManagerData.passwordStrengthChecker.evaluateStrength(passwd);
                switch (strength) {
                case PasswordStrengthChecker::Weak:
                    passItem->setBackground(Qt::red);
                    break;
                case PasswordStrengthChecker::Medium:
                    passItem->setBackground(Qt::yellow);
                    break;
                case PasswordStrengthChecker::Strong:
                    passItem->setBackground(Qt::green);
                    break;
                }
                ui->PM_SearchResults->setItem(tableOffset, 0, siteItem);
                ui->PM_SearchResults->setItem(tableOffset, 1, userItem);
                ui->PM_SearchResults->setItem(tableOffset, 2, passItem);
                tableOffset++;
            }
        }
        ui->PM_SearchResults->setRowCount(tableOffset);
    }
    if(!hasResult){
        pushInfo("PM","No Result!");
    }
}

void MainWindow::on_PM_AddButton_clicked()
{
    bool status;
    if(ui->PM_NewSiteEnterBox->text() != "" && ui->PM_UsernameEnterBox->text() != "" && ui->PM_PasswordEnterBox->text() != ""){
        status = userData.passwordManager->addEntry(ui->PM_NewSiteEnterBox->text(),ui->PM_UsernameEnterBox->text(),ui->PM_PasswordEnterBox->text());
        if(status){
            pushInfo("PM","Password Added!");
            qDebug() << "Password Add Succeed!";
        }
        else{
            pushInfo("PM","Failed To Add Password.");
        }
    }
    else{
        pushInfo("PM","Site, Username and Password should be all filled.");
    }
}

void MainWindow::on_PM_UpdateButton_clicked()
{
    bool status;
    if(ui->PM_NewSiteEnterBox->text() != "" && ui->PM_UsernameEnterBox->text() != "" && ui->PM_PasswordEnterBox->text() != ""){
        status = userData.passwordManager->updateEntry(ui->PM_NewSiteEnterBox->text(),ui->PM_UsernameEnterBox->text(),ui->PM_PasswordEnterBox->text());
        if(status){
            pushInfo("PM","Password Updated!");
            qDebug() << "Password Update Succeed!";
        }
        else{
            pushInfo("PM","Failed To Update Password.");
        }
    }
    else{
        pushInfo("PM","Site, Username and Password should be all filled.");
    }
}

void MainWindow::on_PM_RemoveButton_clicked()
{
    bool status;
    if(ui->PM_NewSiteEnterBox->text() != "" && ui->PM_UsernameEnterBox->text() != "" && ui->PM_PasswordEnterBox->text() != ""){
        status = userData.passwordManager->removeEntry(ui->PM_NewSiteEnterBox->text());
        if(status){
            pushInfo("PM","Password Removed!");
            qDebug() << "Password Remove Succeed!";
        }
        else{
            pushInfo("PM","Failed To Remove Password.");
        }
    }
    else{
        pushInfo("PM","Site, Username and Password should be all filled.");
    }
}

void MainWindow::on_PM_SaveAsFileButton_clicked()
{
    // 1. 弹出“另存为”对话框，让用户选择保存位置和文件名
    QString defaultPath = fileEncData.defaultFileOutputPath + "/passwords_export.json";
    QString filePath = QFileDialog::getSaveFileName(this, "导出密码为JSON文件", defaultPath, "JSON Files (*.json);;All Files (*)");
    exportPasswords(filePath);
}

void MainWindow::on_PM_ReadFromFileButton_clicked()
{
    // 1. 弹出"打开"对话框，让用户选择要导入的JSON文件
    QString defaultPath = fileEncData.defaultFileOutputPath + "/";
    QString filePath = QFileDialog::getOpenFileName(this, "从JSON文件导入密码", defaultPath, "JSON Files (*.json);;All Files (*)");

    // 2. 检查用户是否取消了对话框


}

//  PG:

void MainWindow::on_PG_GenerateButton_clicked()
{
    if((passGenData.Uppercase || passGenData.Lowercase || passGenData.Numbers || passGenData.Symbols) && ui->PG_PasswordSize->value() >= 0){
        ui->PG_GeneratedPassword->setText(passGenData.passwordGenerator->generatePassword(ui->PG_PasswordSize->value(),
                                                                                          passGenData.Uppercase,
                                                                                          passGenData.Lowercase,
                                                                                          passGenData.Numbers,
                                                                                          passGenData.Symbols));
        pushInfo("PG","Password Generated!");
    }
    else if (ui->PG_PasswordSize->value() <= 0){
        pushInfo("PG","Length of password need to be a positive number.");
    }
    else{
        pushInfo("PG","Please select at least one of the character types.");
    }
}


void MainWindow::on_PG_CheckBoxUpperCase_checkStateChanged(const Qt::CheckState &arg1)
{
    passGenData.Uppercase = ui->PG_CheckBoxUpperCase->isChecked();
}


void MainWindow::on_PG_CheckBoxLowerCase_checkStateChanged(const Qt::CheckState &arg1)
{
    passGenData.Lowercase = ui->PG_CheckBoxLowerCase->isChecked();
}


void MainWindow::on_PG_CheckBoxNumbers_checkStateChanged(const Qt::CheckState &arg1)
{
    passGenData.Numbers = ui->PG_CheckBoxNumbers->isChecked();
}


void MainWindow::on_PG_CheckBoxSymbols_checkStateChanged(const Qt::CheckState &arg1)
{
    passGenData.Symbols = ui->PG_CheckBoxSymbols->isChecked();
}

void MainWindow::on_PG_ApplyButton_clicked()
{
    if(ui->PG_GeneratedPassword->toPlainText() != ""){
        ui->stackedWidget->setCurrentWidget(ui->PagePassManager);
        ui->PM_PasswordEnterBox->setText(ui->PG_GeneratedPassword->toPlainText());
    }
}

//  Login:

void MainWindow::on_Login_UsernameEnterBox_returnPressed()
{
    preLogin();
}

void MainWindow::on_Login_PasswordEnterBox_returnPressed()
{
    preLogin();
}

void MainWindow::on_Login_PushButton_clicked()
{
    preLogin();
}

void MainWindow::on_Login_RegisterCheckBox_checkStateChanged(const Qt::CheckState &arg1)
{
    qDebug() << "RegCheckBox checked";
    bool state = ui->Login_RegisterCheckBox->isChecked();
    if(state == true){
        this->loginData.loginMode = false;
        ui->Login_PushButton->setText("Register");
    }
    else{
        this->loginData.loginMode = true;
        ui->Login_PushButton->setText("Login");
    }
}








