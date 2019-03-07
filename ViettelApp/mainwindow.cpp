#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_loginFm(new LoginForm(this))
   
{
    ui->setupUi(this);
    connect(m_loginFm,&LoginForm::loggedIn,this,&MainWindow::handleLoginResponsePms);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleLoginResponsePms(const QJsonObject &docObj)
{
    ui->viewDBbtn->setEnabled(false);
    ui->changepmsBtn->setEnabled(false);
    ui->configBtn->setEnabled(false);
    ui->pmsXBtn->setEnabled(false);
    QJsonValue permission = docObj.value(QLatin1String("permission"));
    if (!permission.isNull()||permission.isArray())
    {
        QJsonArray pms = permission.toArray();
        if(pms.contains(1)){
            ui->viewDBbtn->setEnabled(true);
        }
        if(pms.contains(2)){
            ui->changepmsBtn->setEnabled(true);
        }
        if(pms.contains(3)){
            ui->configBtn->setEnabled(true);
        }
        if(pms.contains(4)){
            ui->pmsXBtn->setEnabled(true);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    QApplication::quit();
}
