#include "../cell.h"
#include "tcpclient.h"

#include <QByteArray>
#include <QDebug>
#include <QHostAddress>
#include <QTcpSocket>

namespace TCPManager
{
    TCPClient::TCPClient( const QHostAddress & host, const quint16 port, QObject * parent )
        : QObject( parent )
    {
        p_socket = new QTcpSocket( this );
        qDebug() << "--- Connect to Host ---";

        p_socket->connectToHost( host, port );

        connect( p_socket, SIGNAL( connected() ), this, SLOT( onConnected() ) );

        connect( p_socket, SIGNAL( readyRead() ), this, SLOT( onReadyRead() ) );

        connect( p_socket, SIGNAL( disconnected() ), this, SLOT( onDisconnected() ) );
    }

    TCPClient::~TCPClient()
    {
        p_socket->close();
        p_socket->deleteLater();
    }

    void TCPClient::sendMessage( const QByteArray & data )
    {

        qDebug() << "--- Sending Message ---";
        p_socket->write( data );
    }

    void TCPClient::onReadyRead()
    {
        qDebug() << "--- Read Message ---";

        QByteArray outArray;
        if( p_socket->bytesAvailable() )
        {
            outArray = p_socket->readAll();
        }


        QDataStream in( &outArray, QIODevice::ReadOnly );
        char type;
        in >> type;

        if ( !outArray.isEmpty() )
        {
            if ( type == (char)TIME )
                emit newTimer( outArray );
            else if ( type == (char)DATA )
                emit newData( outArray );
            else
                qDebug() << "wtf";
        }
    }

    void TCPClient::onDisconnected()
    {
        qDebug() << "--- Connection Ended ---";
        emit disconnected();
    }

    void TCPClient::onConnected()
    {
        qDebug() << "--- Successful connection ---";
        emit connected();
    }
}

