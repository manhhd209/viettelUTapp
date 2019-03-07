#include "loginform.h"
#include "ui_loginform.h"
#include "jsonhandling.h"
#include "mainwindow.h"
#include <QTcpSocket>
#include <QMessageBox>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QInputDialog>

LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginForm),
    m_jsonHandling(new JsonHandling(this))
{
    ui->setupUi(this);
    //connect(m_jsonHandling, &JsonHandling::connected, this, &LoginForm::connectedToServer);
    //connect(ui->loginBtn, &QPushButton::clicked, this, &JsonHandling::connectToServer);
    connect(m_jsonHandling,&JsonHandling::loginresponse,this,&LoginForm::handleLoginResponse);
    connect(m_jsonHandling, &JsonHandling::error, this, &LoginForm::error);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_loginBtn_clicked()
{
    m_jsonHandling->connectToServer();
    LoginForm::login();

}

void LoginForm::handleLoginResponse(const QJsonObject &docObj)
{
    QJsonValue loginstt = docObj.value(QLatin1String("loginstt"));
    if (!(loginstt.isNull() || !loginstt.isString())&&
            (loginstt.toString().compare(QLatin1String("loginOk"), Qt::CaseInsensitive) == 0))
    {
        MainWindow *mw = new MainWindow();
        emit loggedIn(docObj);
        mw->show();
        this->hide();
    }else {
        QMessageBox::critical(this, tr("Error"), tr("Wrong login information"));
    }
}

void LoginForm::login()
{
    const QString &usrname = ui->usrnameLEdt->text();
    const QString &usrpwd = ui->pwdLEdt->text();
    if (usrname.isEmpty()||usrpwd.isEmpty())
        return; // We don't send empty messages
    // Create the JSON we want to send
    QJsonObject message;
    message["type"] = QStringLiteral("logininfo");
    message["usrname"] = usrname;
    message["usrpwd"] = usrpwd;
//    qDebug() << QJsonDocument(message).toJson();
    m_jsonHandling->sendJson(QJsonDocument(message).toJson());
}


void LoginForm::error(QAbstractSocket::SocketError socketError)
{
    // show a message to the user that informs of what kind of error occurred
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
    case QAbstractSocket::ProxyConnectionClosedError:
        return; // handled by disconnectedFromServer
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The host refused the connection"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The proxy refused the connection"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the proxy"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the server"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::critical(this, tr("Error"), tr("You don't have permissions to execute this operation"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::critical(this, tr("Error"), tr("Too many connections opened"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::warning(this, tr("Error"), tr("Operation timed out"));
        return;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy timed out"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::critical(this, tr("Error"), tr("Unable to reach the network"));
        break;
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::critical(this, tr("Error"), tr("An unknown error occured"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::critical(this, tr("Error"), tr("Operation not supported"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::critical(this, tr("Error"), tr("Your proxy requires authentication"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy comunication failed"));
        break;
    case QAbstractSocket::TemporaryError:
    case QAbstractSocket::OperationError:
        QMessageBox::warning(this, tr("Error"), tr("Operation failed, please try again"));
        return;
    default:
        Q_UNREACHABLE();
    }
}
