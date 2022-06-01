#include "brashbattleserver.h"

#include <QTimer>
#include <QByteArray>
#include <QDataStream>
#include <QGridLayout>
#include <QDebug>

#define SIZE 16

BrashBattleServer::BrashBattleServer( QWidget * parent )
    : QWidget( parent )
{
    p_server = new TCPManager::TCPServer( PORT );

    connect( p_server, SIGNAL( cellChanged( const QHostAddress &, QByteArray * ) ),
             this, SLOT( onCellChanged( const QHostAddress &, QByteArray * ) ) );

    QTimer * timer1 = new QTimer();
    QTimer * timer2 = new QTimer();

    connect( timer1, SIGNAL( timeout() ), this, SLOT( sendStates() ) );
    connect( timer2, SIGNAL( timeout() ), this, SLOT( sendTimers() ) );

    timer1->start( 500 );
    timer2->start( 900 );

    QGridLayout * grd = new QGridLayout( this );
    grd->setSpacing( 0 );

    for ( int i = 0; i < SIZE; ++i )
    {
        cells.append( QList<Cell *>() );
        for ( int j = 0; j < SIZE; ++j )
        {
            cells[i].append( new Cell( i, j, this ) );
            grd->addWidget( cells[i][j], i, j, 1, 1 );
        }
    }
}

BrashBattleServer::~BrashBattleServer()
{
}

void BrashBattleServer::sendTimers()
{
    //qDebug() << "--- SENDING TIMERS ---";

    foreach ( quint32 host, timeControl.keys() ) {
        qDebug() << "--- SENDING TIMER TO ---" << QHostAddress( host );
        QByteArray buffer;
        QDataStream out( &buffer, QIODevice::WriteOnly );
        out << (char)TIME;
        out << timeControl[host];

        p_server->sendDataToHost( QHostAddress( host ), buffer );
    }
}

void BrashBattleServer::sendStates()
{
    //qDebug() << "--- SENDING STATES ---";
    QByteArray buffer;
    QDataStream out( &buffer, QIODevice::WriteOnly );

    out << (char)DATA;

    for ( int i = 0; i < SIZE; ++i )
        for ( int j = 0; j < SIZE; ++j )
            out << cells[i][j]->getX() << cells[i][j]->getY() << cells[i][j]->getColor();


    p_server->sendEveryoneData( buffer );
}

void BrashBattleServer::onCellChanged( const QHostAddress & host, QByteArray * data )
{
    QDataStream in( data, QIODevice::ReadOnly );

    char type;
    char xPosition;
    char yPosition;
    char color;

    in >> type >> xPosition >> yPosition >> color;

    if ( cells[xPosition][yPosition]->getColor() == color )
        return;

    if ( timeControl.find( host.toIPv4Address() ) == timeControl.end() )
    {
        timeControl.insert( host.toIPv4Address(), QDateTime::currentSecsSinceEpoch() );
        cells[xPosition][yPosition]->setColor( color );
    }
    else
    {
        if ( QDateTime::currentSecsSinceEpoch() - timeControl[host.toIPv4Address()] > TIME_DELAY )
        {
                cells[xPosition][yPosition]->setColor( color );
                timeControl[host.toIPv4Address()] = QDateTime::currentSecsSinceEpoch();
        }
        else
            return;
    }
}

