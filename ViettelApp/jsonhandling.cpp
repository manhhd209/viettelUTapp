#include "jsonhandling.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

JsonHandling::JsonHandling(QObject *parent)
    : QObject(parent)
    , m_clientSocket(new QTcpSocket(this))
{
    // Forward the connected and disconnected signals
    connect(m_clientSocket, &QTcpSocket::connected, this, &JsonHandling::connected);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &JsonHandling::disconnected);
    // connect readyRead() to the slot that will take care of reading the data in
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &JsonHandling::onReadyRead);
    // Forward the error signal, QOverload is necessary as error() is overloaded, see the Qt docs
    connect(m_clientSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &JsonHandling::error);
}

void JsonHandling::disconnectFromHost()
{
     m_clientSocket->disconnectFromHost();
}

void JsonHandling::connectToServer()
{
    if (m_clientSocket->state() != QAbstractSocket::ConnectedState) {
        m_clientSocket->connectToHost("127.0.0.1", 7070);
    }
}
void JsonHandling::jsonReceived(const QJsonObject &docObj)
{
    // actions depend on the type of message
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return; // a message with no type was received so we just ignore it
    if (typeVal.toString().compare(QLatin1String("login"), Qt::CaseInsensitive) == 0) { //It's a login message
        emit loginresponse(docObj);
    } else if (typeVal.toString().compare(QLatin1String("getpermission"), Qt::CaseInsensitive) == 0) {

    }
}

void JsonHandling::sendJson(QByteArray json)
{
    m_clientSocket->write(json);
}

void JsonHandling::onReadyRead()
{
    // prepare a container to hold the UTF-8 encoded JSON we receive from the socket
    QByteArray jsonData;
    // create a QDataStream operating on the socket
    QDataStream socketStream(m_clientSocket);
    // set the version so that programs compiled with different versions of Qt can agree on how to serialise
    socketStream.setVersion(QDataStream::Qt_5_7);
    // start an infinite loop
    jsonData = m_clientSocket->readAll();
    QJsonParseError parseError;
    // we try to create a json document with the data we received
    const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error == QJsonParseError::NoError) {
        // if the data was indeed valid JSON
        if (jsonDoc.isObject()) // and is a JSON object
            jsonReceived(jsonDoc.object()); // parse the JSON
    }
}
