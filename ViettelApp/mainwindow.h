#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginform.h"

class LoginForm;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LoginForm *m_loginFm;
private slots:
    void handleLoginResponsePms(const QJsonObject &docObj);
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
