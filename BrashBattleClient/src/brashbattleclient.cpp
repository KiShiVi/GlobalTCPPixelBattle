#include "brashbattleclient.h"

#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>
#include <QGridLayout>
#include <QDateTime>

#define SIZE 16

BrashBattleClient::BrashBattleClient( QWidget * parent )
    : QWidget( parent )
{
    p_client = new TCPManager::TCPClient( QHostAddress( HOST ), PORT );

    p_lcd = new QLCDNumber( 2 );
    p_lcd->setSegmentStyle( QLCDNumber::Flat );
    p_lcd->setMinimumHeight( 70 );

    connect( p_client, SIGNAL( newData( QByteArray & ) ), this, SLOT( onNewData( QByteArray & ) ) );
    connect( p_client, SIGNAL( newTimer( QByteArray & ) ), this, SLOT( onNewTimer( QByteArray & ) ) );

    QGridLayout * grd = new QGridLayout( this );
    grd->setSpacing( 0 );

    for ( int i = 0; i < SIZE; ++i )
    {
        cells.append( QList<Cell *>() );
        for ( int j = 0; j < SIZE; ++j )
        {
            Cell * cell = new Cell( i, j, this );
            connect( cell, SIGNAL( clicked( Cell * ) ), this, SLOT( onClicked( Cell * ) ) );
            cells[i].append( cell );
            grd->addWidget( cells[i][j], i, j, 1, 1 );
        }
    }

    grd->addWidget( p_lcd, SIZE, 0, 3, SIZE );
}

BrashBattleClient::~BrashBattleClient()
{
    delete p_client;
}

void BrashBattleClient::onNewData( QByteArray & data )
{
    QDataStream in( &data, QIODevice::ReadOnly );

    char type;
    char xPosition;
    char yPosition;
    char color;

    in >> type;

    for ( int i = 0; i < SIZE; ++i )
        for ( int j = 0; j < SIZE; ++j )
        {
            in >> xPosition >> yPosition >> color;
            cells[xPosition][yPosition]->setColor( color );
        }
}

void BrashBattleClient::onNewTimer( QByteArray & data )
{
    QDataStream in( &data, QIODevice::ReadOnly );

    char type;
    quint64 seconds;

    in >> type;
    in >> seconds;

    QString string;

    qDebug() << QDateTime::currentSecsSinceEpoch() - seconds << seconds;

    string = QString::number( QDateTime::currentSecsSinceEpoch() - seconds >= TIME_DELAY ? 0
                                             : ( TIME_DELAY - (QDateTime::currentSecsSinceEpoch() - seconds) ) );

    p_lcd->display( string );
}

void BrashBattleClient::onClicked( Cell * sender )
{
    QByteArray buffer;
    QDataStream out( &buffer, QIODevice::WriteOnly );

    //sender->setColor( 1 );

    out << (char)DATA << sender->getX() << sender->getY() << (char)1; //sender->getColor();
    p_client->sendMessage( buffer );
}
