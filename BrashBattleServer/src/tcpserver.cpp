#include "../cell.h"
#include "tcpserver.h"

#include <QByteArray>
#include <QDebug>
#include <QHostAddress>
#include <QTcpSocket>
#include <QTcpServer>

namespace TCPManager
{
    TCPServer::TCPServer( const quint16 port, QObject * parent )
        : QObject( parent )
    {
        p_server = new QTcpServer;

        if ( p_server->listen( QHostAddress::Any, port ) )
            qDebug() << "--- Linsting to Port ---";
        else
            qDebug() << "*** FAIL LISTING ***";

        connect( p_server, SIGNAL( newConnection() ), this, SLOT( onNewConnection() ) );
    }

    TCPServer::~TCPServer()
    {
        p_server->close();
        p_server->deleteLater();

        foreach ( QTcpSocket * socket, m_socketList )
        {
            socket->close();
            socket->deleteLater();
        }

        qDebug() << "--- Server closed the connection ---";
    }

    void TCPServer::sendEveryoneData( const QByteArray & data )
    {
        foreach( QTcpSocket * socket, m_socketList )
        {
            socket->write( data );
        }
    }

    void TCPServer::sendDataToHost( const QHostAddress & host, const QByteArray & data )
    {
        foreach( QTcpSocket * socket, m_socketList )
        {
            if ( socket->peerAddress().toIPv4Address() == host.toIPv4Address() )
            {
                socket->write( data );
            }
        }
    }

    void TCPServer::onNewConnection()
    {

        QTcpSocket * newSocket;
        newSocket = p_server->nextPendingConnection();
        m_socketList.append( newSocket );

        connect( newSocket, SIGNAL( readyRead() ), this, SLOT( onReadyRead() ) );
        connect( newSocket, SIGNAL( disconnected() ), this, SLOT( onDisconnected() ) );

        qDebug() << "--- Accept Connection ---" << newSocket->peerAddress() << newSocket->peerPort();
    }

    void TCPServer::onReadyRead()
    {
        qDebug() << "--- Read Message ---";

        QTcpSocket * senderSocket = ( QTcpSocket * )sender();

        QByteArray outArray;
        if( senderSocket->bytesAvailable() )
        {
            outArray = senderSocket->readAll();
        }

        QDataStream in( &outArray, QIODevice::ReadOnly );
        char type;
        in >> type;

        if ( !outArray.isEmpty() )
        {
            if ( type == (char)DATA )
                emit cellChanged( senderSocket->peerAddress(), &outArray );
        }

        qDebug() << outArray.data() << senderSocket->peerAddress() << senderSocket->peerPort();
    }

    void TCPServer::onDisconnected()
    {
        qDebug() << "--- Disconnection ---";
        QTcpSocket * socket = ( QTcpSocket * )sender();
        if ( !m_socketList.removeOne( socket ) )
            qDebug() << "--- Delete socket ERROR ---";
        socket->deleteLater();
    }
}

