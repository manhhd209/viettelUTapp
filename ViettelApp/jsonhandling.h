#ifndef JSONHANDLING_H
#define JSONHANDLING_H

#include <QAbstractItemModel>
#include <QTcpSocket>
#include <QObject>

class JsonHandling : public QObject
{
    Q_OBJECT

public:
    explicit JsonHandling(QObject *parent = nullptr);
public slots:
    void connectToServer();
    void disconnectFromHost();
    void sendJson(QByteArray json);
private slots:
    void onReadyRead();
signals:
    void loginresponse(const QJsonObject &docObj);
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);
private:
    QTcpSocket *m_clientSocket;
    void jsonReceived(const QJsonObject &doc);

private:
};

#endif // JSONHANDLING_H
