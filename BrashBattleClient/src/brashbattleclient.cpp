#include "brashbattleclient.h"

#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>
#include <QGridLayout>
#include <QDateTime>
#include <QHBoxLayout>
#include <QSpacerItem>

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
    connect( p_client, SIGNAL( connected() ), this, SLOT( onConnected() ) );
    connect( p_client, SIGNAL( disconnected() ), this, SLOT( onDisconnected() ) );

    QGridLayout * grd = new QGridLayout ();
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

    QGridLayout * colorLayout   = new QGridLayout();
    QHBoxLayout * mainLayout    = new QHBoxLayout( this );

    for ( int i = 0; i < 16; ++i )
    {
        Cell * cell = new Cell( 0, 0 );
        cell->setColor( i );
        colorLayout->addWidget( cell, (i % 8) + 1, i / 8, 1, 1 );
        connect( cell, SIGNAL( clicked( Cell * ) ), this, SLOT( setCurrentColor( Cell * ) ) );
    }

    p_currentColorCell = new Cell( 0, 0 );
    p_currentColorCell->setFixedSize( 48, 48 );
    colorLayout->addWidget( p_currentColorCell, 9, 0, 2, 2 );
    p_currentColorCell->setColor( WHITE );

    p_connectionState = new Cell( 0, 0 );
    p_connectionState->setFixedSize( 16, 16 );
    colorLayout->addWidget( p_connectionState, 10, 0, 1, 1 );
    p_connectionState->setColor( RED );

    colorLayout->setSpacing( 1 );
    colorLayout->setContentsMargins( 0, 0, 0, 0 );
    //colorLayout->addItem( new QSpacerItem( 30, 100 ), 10, 0 );

    mainLayout->addStretch( 1 );
    mainLayout->addLayout( colorLayout );
    mainLayout->addLayout( grd );

    m_currentColor = BLACK;
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

    out << (char)DATA << sender->getX() << sender->getY() << (char)m_currentColor; //sender->getColor();
    p_client->sendMessage( buffer );
}

void BrashBattleClient::setCurrentColor( Cell * sender )
{
    m_currentColor = sender->getColor();
    p_currentColorCell->setColor( sender->getColor() );
}

void BrashBattleClient::onConnected()
{
    p_connectionState->setColor( LIME );
}

void BrashBattleClient::onDisconnected()
{
    p_connectionState->setColor( RED );
}
