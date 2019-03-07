#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QTcpSocket>

class JsonHandling;
namespace Ui {
class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

signals:
    void loggedIn(const QJsonObject &docObj);
private slots:
    void on_loginBtn_clicked();
    void error(QAbstractSocket::SocketError socketError);
    void login();
    void handleLoginResponse(const QJsonObject &docObj);
private:
    QTcpSocket *m_clientSocket;
    void jsonReceived(const QJsonObject &doc);

private:
    Ui::LoginForm *ui;
    JsonHandling *m_jsonHandling;
};

#endif // LOGINFORM_H
