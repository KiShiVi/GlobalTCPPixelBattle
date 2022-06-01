#include "cell.h"

#include <QDebug>

Cell::Cell( const quint8 x, const quint8 y, QWidget * parent ) : QLabel( parent )
{
    m_xPosition = x;
    m_yPosition = y;
    m_color = 0;
    setFixedSize(24, 24);
    setStyleSheet( "QLabel{ border: 1px solid black; }" );
}

Cell::~Cell()
{
}

void Cell::setColor( const quint8 color )
{
    m_color = color;
    switch ( m_color )
    {
    case 0:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(255, 255, 255); }" );
        break;
    case 1:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(255, 0, 0);}" );
        break;
    case 2:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(0, 255, 0);}" );
        break;
    case 3:
        setStyleSheet( "QLabel{ border: 1px solid black; background: rgb(0, 0, 255);}" );
        break;
    default:
        qDebug() << "$$$ Incorrect color $$$";
        break;
    }
}

quint8 Cell::getColor()
{
    return m_color;
}

quint8 Cell::getX()
{
    return m_xPosition;
}

quint8 Cell::getY()
{
    return m_yPosition;
}

void Cell::mouseReleaseEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton )
        emit clicked( this );
}
