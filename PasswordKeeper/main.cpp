#include "mainwindow.h"

#include <QApplication>


enum windowstate{
    login,
    pwdenc,
    fileenc,

};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
