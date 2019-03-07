#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "loginform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMessageBox msgBox;


    LoginForm lgifm;
    lgifm.show();

    return a.exec();
}
