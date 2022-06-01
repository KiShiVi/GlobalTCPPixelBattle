#pragma once

#include <QObject>

class QTcpServer;
class QTcpSocket;

namespace TCPManager
{
    class TCPServer : public QObject
    {
        Q_OBJECT
    public:
        TCPServer( const quint16 port, QObject * parent = nullptr );
        ~TCPServer();

    private slots:
        void onNewConnection();
        void onReadyRead();
        void onDisconnected();

    private:
        QTcpServer            * p_server;
        QList<QTcpSocket *>     m_socketList;
    };
}
